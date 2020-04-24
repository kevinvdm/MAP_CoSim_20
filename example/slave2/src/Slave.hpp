
#ifndef SLAVE_H_
#define SLAVE_H_

#define _GNU_SOURCE 1

#include <dcp/helper/Helper.hpp>
#include <dcp/log/OstreamLog.hpp>
#include <dcp/logic/DcpManagerSlave.hpp>
#include <dcp/model/pdu/DcpPduFactory.hpp>
#include <dcp/driver/ethernet/udp/UdpDriver.hpp>

#include <cstdint>
#include <cstdio>
#include <stdarg.h>
#include <thread>
#include <cmath>

#include "stdio.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include "libpruio/pruio.h"
#include "libpruio/pruio_pins.h"

//! The pin for CAP input.
#define P_IN P9_42


class Slave {
public:
    Slave() : stdLog(std::cout) {
        udpDriver = new UdpDriver(HOST, PORT);
        manager = new DcpManagerSlave(getSlaveDescription(), udpDriver->getDcpDriver());
        manager->setInitializeCallback<SYNC>(
                std::bind(&Slave::initialize, this));
        manager->setConfigureCallback<SYNC>(
                std::bind(&Slave::configure, this));
        manager->setSynchronizingStepCallback<SYNC>(
                std::bind(&Slave::doStep, this, std::placeholders::_1));
        manager->setSynchronizedStepCallback<SYNC>(
                std::bind(&Slave::doStep, this, std::placeholders::_1));
        manager->setRunningStepCallback<SYNC>(
                std::bind(&Slave::doStep, this, std::placeholders::_1));
        manager->setTimeResListener<SYNC>(std::bind(&Slave::setTimeRes, this,
                                                    std::placeholders::_1,
                                                    std::placeholders::_2));

        //Display log messages on console
        manager->addLogListener(
                std::bind(&OstreamLog::logOstream, stdLog, std::placeholders::_1));
        manager->setGenerateLogString(true);

    }

    ~Slave() {
        delete manager;
        delete udpDriver;
    }


    void configure() {
        simulationTime = 0;
        currentStep = 0;

        //returns pointer to input & output variables. param a_vr or y_vr points to value reference, defined in slave desc
        a = manager->getInput<float64_t *>(a_vr);
        y = manager->getOutput<float64_t *>(y_vr);
    }

    void initialize() {
        pruIo *Io = pruio_new(PRUIO_DEF_ACTIVE, 0x98, 0, 1); //! create new driver structure ------    FREE PINMUXING BY USING ENUM PRUIO_ACT_FREMUX

        if (Io->Errr) {
               printf("initialisation failed (%s)\n", Io->Errr);}

        if (pruio_cap_config(Io, P_IN, 2.)) { //         configure input pin
               printf("failed setting input @P_IN (%s)\n", Io->Errr);}

        //           pin config OK, transfer local settings to PRU and start
        if (pruio_config(Io, 1, 0x1FE, 0, 4)) {
                       printf("config failed (%s)\n", Io->Errr);}
        
        if (pruio_cap_Value(Io, P_IN, &f1, &d1)) { //    get current input
          printf("failed reading input @P_IN (%s)\n", Io->Errr);}

        printf("\r    Frequency: %10f , Duty: %10f     ", f1, d1); // info

        *y = std::sin(currentStep + *a);
    }

    void doStep(uint64_t steps) {
        //timediff is calculated using time resolution that is defined at config level
        float64_t timeDiff =
                ((double) numerator) / ((double) denominator) * ((double) steps);

        //calculate new value
        if (pruio_cap_Value(Io, P_IN, &f1, &d1)) { //    get current input
          printf("failed reading input @P_IN (%s)\n", Io->Errr);}
        *y = d1;  

        //log everything
        manager->Log(SIM_LOG, simulationTime, currentStep, *a, *y);
        //calculate new simulationtime based on time resolution
        simulationTime += timeDiff;
        currentStep += steps;
    }

    void setTimeRes(const uint32_t numerator, const uint32_t denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }

    void start() { manager->start(); }

    SlaveDescription_t getSlaveDescription(){
        SlaveDescription_t slaveDescription = make_SlaveDescription(1, 0, "dcpslave2", "b5279485-720d-4542-9f29-bee4d9a75ef9");
        slaveDescription.OpMode.SoftRealTime = make_SoftRealTime_ptr();
        Resolution_t resolution = make_Resolution();
        resolution.numerator = 1;
        resolution.denominator = 100;
        slaveDescription.TimeRes.resolutions.push_back(resolution);
        slaveDescription.TransportProtocols.UDP_IPv4 = make_UDP_ptr();
        slaveDescription.TransportProtocols.UDP_IPv4->Control =
                make_Control_ptr(HOST, 8082);
        ;
        slaveDescription.TransportProtocols.UDP_IPv4->DAT_input_output = make_DAT_ptr();
        slaveDescription.TransportProtocols.UDP_IPv4->DAT_input_output->availablePortRanges.push_back(
                make_AvailablePortRange(2048, 65535));
        slaveDescription.TransportProtocols.UDP_IPv4->DAT_parameter = make_DAT_ptr();
        slaveDescription.TransportProtocols.UDP_IPv4->DAT_parameter->availablePortRanges.push_back(
                make_AvailablePortRange(2048, 65535));
        slaveDescription.CapabilityFlags.canAcceptConfigPdus = true;
        slaveDescription.CapabilityFlags.canHandleReset = true;
        slaveDescription.CapabilityFlags.canHandleVariableSteps = true;
        slaveDescription.CapabilityFlags.canMonitorHeartbeat = false;
        slaveDescription.CapabilityFlags.canAcceptConfigPdus = true;
        slaveDescription.CapabilityFlags.canProvideLogOnRequest = true;
        slaveDescription.CapabilityFlags.canProvideLogOnNotification = true;

        std::shared_ptr<Output_t> caus_y = make_Output_ptr<float64_t>();
        slaveDescription.Variables.push_back(make_Variable_output("y", y_vr, caus_y));
        std::shared_ptr<CommonCausality_t> caus_a =
                make_CommonCausality_ptr<float64_t>();
        caus_a->Float64->start = std::make_shared<std::vector<float64_t>>();
        caus_a->Float64->start->push_back(10.0);
        slaveDescription.Variables.push_back(make_Variable_input("a", a_vr, caus_a));
        slaveDescription.Log = make_Log_ptr();
        slaveDescription.Log->categories.push_back(make_Category(1, "DCP_SLAVE"));
        slaveDescription.Log->templates.push_back(make_Template(
                1, 1, (uint8_t) DcpLogLevel::LVL_INFORMATION, "[Time = %float64]: Current step: %uint64 , Frequency: %float64 , Duty cycle: %float64"));

       return slaveDescription;
    }

private:
    DcpManagerSlave *manager;
    OstreamLog stdLog;

    UdpDriver* udpDriver;
    const char *const HOST = "192.168.7.2"; //BBB ADDR (SLAVE2)
    const int PORT = 8082; //SLAVE2 PORT. SLAVE1: PORT 8080

    uint32_t numerator;
    uint32_t denominator;

    double simulationTime;
    uint64_t currentStep;

    //To call LogTemplate object, followed by the values according to the defined placeholders in the log message has to be passed to the method.
    const LogTemplate SIM_LOG = LogTemplate(
            1, 1, DcpLogLevel::LVL_INFORMATION,
            "[Time = %float64]: Current step: %uint64 , Frequency: %float64 , Duty cycle: %float64",
            {DcpDataType::float64, DcpDataType::uint64, DcpDataType::float64, DcpDataType::float64});
     
    float_t
        f1 //                         Variable for calculated frequency.
      , d1; //                        Variable for calculated duty cycle.

    //value reference for a = 2 (see slave desc)
    float64_t *a;
    const uint32_t a_vr = 2;
    //value reference for y = 1 (see slave desc)
    float64_t *y;
    const uint32_t y_vr = 1;

};

#endif /* SLAVE_H_ */
