#ifndef SLAVE_H_
#define SLAVE_H_

#include <dcp/helper/Helper.hpp>
#include <dcp/log/OstreamLog.hpp>
#include <dcp/logic/DcpManagerSlave.hpp>
#include <dcp/model/pdu/DcpPduFactory.hpp>
#include <dcp/driver/ethernet/udp/UdpDriver.hpp>
#include <FMULoader.hpp>

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdio>
#include <stdarg.h>
#include <thread>
#include <cmath>
#include <time.h>
#include <chrono>


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
        v = manager->getInput<float64_t *>(v_vr);
        t = manager->getOutput<float64_t *>(t_vr);
    }

    void initialize() {
        *t = FmuLoader.getThrottle();
	myfile.open("output.csv", std::ofstream::out | std::ofstream::trunc);
    }

    void doStep(uint64_t steps) {
        //timediff is calculated using time resolution that is defined at config level
        float64_t timeDiff =
                ((double) numerator) / ((double) denominator) * ((double) steps);

        FmuLoader.doFmuStep(timeDiff, v);
        //calculate new value
        *t = FmuLoader.getThrottle();
	d = FmuLoader.getVdesired();
        //*t = 0.99;
        //log everything
        manager->Log(SIM_LOG, simulationTime, currentStep, *v, *t);
	if (*t < 0.1){
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        	auto duration = now.time_since_epoch();
        	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		myfile << simulationTime << "," << d << "," << *v << "," << *t << "," << millis << "\n";
        }
	else {
		myfile << simulationTime << "," << d << "," << *v << "," << *t << "\n";
	}
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
        SlaveDescription_t slaveDescription = make_SlaveDescription(1, 0, "dcpslave", "b5279485-720d-4542-9f29-bee4d9a75ef8");
        slaveDescription.OpMode.SoftRealTime = make_SoftRealTime_ptr();
        Resolution_t resolution = make_Resolution();
        resolution.numerator = 1;
        resolution.denominator = 100;
        slaveDescription.TimeRes.resolutions.push_back(resolution);
        slaveDescription.TransportProtocols.UDP_IPv4 = make_UDP_ptr();
        slaveDescription.TransportProtocols.UDP_IPv4->Control =
                make_Control_ptr(HOST, 8080);
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

        std::shared_ptr<CommonCausality_t> caus_v =
                make_CommonCausality_ptr<float64_t>();
        caus_v->Float64->start = std::make_shared<std::vector<float64_t>>();
        caus_v->Float64->start->push_back(10.0);
        slaveDescription.Variables.push_back(make_Variable_input("v", v_vr, caus_v));
        std::shared_ptr<Output_t> caus_t = make_Output_ptr<float64_t>();
        slaveDescription.Variables.push_back(make_Variable_output("t", t_vr, caus_t));
        slaveDescription.Log = make_Log_ptr();
        slaveDescription.Log->categories.push_back(make_Category(1, "DCP_SLAVE"));
        slaveDescription.Log->templates.push_back(make_Template(
                1, 1, (uint8_t) DcpLogLevel::LVL_INFORMATION, "[Time = %float64]: step: %uint64 Velocity (I): %float64 , Throttle (O): %float64"));
        slaveDescription.Log->templates.push_back(make_Template(
                2, 1, (uint8_t) DcpLogLevel::LVL_INFORMATION, "[Time = %float64]: step: %uint64 Velocity (I): %float64 , Throttle (O): %float64"));

       return slaveDescription;
    }

private:
    DcpManagerSlave *manager;
    OstreamLog stdLog;

    std::ofstream myfile;
	
    UdpDriver* udpDriver;
    const char *const HOST = "192.168.7.1"; //DEDICATED LINUX ADDR (SLAVE1)
    const int PORT = 8080; //SLAVE1 PORT. SLAVE2: PORT 8082

    FMULoader FmuLoader;

    uint32_t numerator;
    uint32_t denominator;

    double simulationTime;
    uint64_t currentStep;

    //To call LogTemplate object, followed by the values according to the defined placeholders in the log message has to be passed to the method.
    const LogTemplate SIM_LOG = LogTemplate(
            1, 1, DcpLogLevel::LVL_INFORMATION,
            "[Time = %float64]: step: %uint64 Velocity (I): %float64 , Throttle (O): %float64",
            {DcpDataType::float64, DcpDataType::uint64, DcpDataType::float64, DcpDataType::float64});
     
    //value reference for v = 1 (see slave desc)
    float64_t *v;
    const uint32_t v_vr = 1;
    //value reference for t = 2 (see slave desc)
    float64_t *t;
    const uint32_t t_vr = 2;
    float64_t d;

};

#endif /* SLAVE_H_ */
