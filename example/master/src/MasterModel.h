/*
 * Master.h
 *
 *  Created on: 25.02.2017
 *      Author: kater
 */

#ifndef ACI_EXAMPLE_MASTER_H_
#define ACI_EXAMPLE_MASTER_H_

#include <iostream>
#include <cstdint>
#include <fstream>
#include <memory>

#include <dcp/model/pdu/DcpPduFactory.hpp>
#include <dcp/xml/DcpSlaveDescriptionReader.hpp>
#include <dcp/driver/ethernet/udp/UdpDriver.hpp>
#include <dcp/logic/DcpManagerMaster.hpp>
#include <dcp/log/OstreamLog.hpp>


/**
 * Note: This example is just for demonstration purpose of the API.
 * It uses very simple mechanisms and assumptions about the scenario to simulate,
 * which will not work out in a general master tool.
 */
class MasterModel {
public:
    MasterModel() : stdLog(std::cout) {
        driver = new UdpDriver(HOST, PORT);

        slaveDescription = readSlaveDescription("Example-Slave-Description.xml");

        slaveDescription2 = readSlaveDescription("Example-Slave-Description-2.xml"); //added (read slave description for second slave, running on BBB)

        manager = new DcpManagerMaster(driver->getDcpDriver());
        uint8_t *netInfo = new uint8_t[6];
        *((uint16_t *) netInfo) = *slaveDescription->TransportProtocols.UDP_IPv4->Control->port;
        *((uint32_t *) (netInfo + 2)) = asio::ip::address_v4::from_string(*slaveDescription->TransportProtocols.UDP_IPv4->Control->host).to_ulong();

        uint8_t *netInfo2 = new uint8_t[6]; //added
        *((uint16_t *) netInfo2) = *slaveDescription2->TransportProtocols.UDP_IPv4->Control->port; //added
        *((uint32_t *) (netInfo2 + 2)) = asio::ip::address_v4::from_string(*slaveDescription2->TransportProtocols.UDP_IPv4->Control->host).to_ulong(); //added
        
        driver->getDcpDriver().setSlaveNetworkInformation(1, netInfo);

        driver->getDcpDriver().setSlaveNetworkInformation(2, netInfo2); //added (store net info, first param is dcpId, needs to be diff for every slave)

        delete[] netInfo;
        delete[] netInfo2;
        manager->setAckReceivedListener<SYNC>(
                std::bind(&MasterModel::receiveAck, this, std::placeholders::_1, std::placeholders::_2));
        manager->setNAckReceivedListener<SYNC>(
                std::bind(&MasterModel::receiveNAck, this, std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3));
        manager->setStateChangedNotificationReceivedListener<SYNC>(
                std::bind(&MasterModel::receiveStateChangedNotification, this, std::placeholders::_1,
                          std::placeholders::_2));
        manager->addLogListener(std::bind(&OstreamLog::logOstream, stdLog, std::placeholders::_1));
        manager->setGenerateLogString(true);
    }

    ~MasterModel() {
        delete driver;
        delete manager;
    }

    void start() {
        std::thread b(&DcpManagerMaster::start, manager);
        std::chrono::seconds dura(1);
        std::this_thread::sleep_for(dura);
        //driver->getDcpDriver().connectToSlave(1);
        std::cout << "Register Slaves" << std::endl;
        manager->STC_register(1, DcpState::ALIVE, convertToUUID(slaveDescription->uuid), DcpOpMode::SRT, 1, 0);

        manager->STC_register(2, DcpState::ALIVE, convertToUUID(slaveDescription2->uuid), DcpOpMode::SRT, 1, 0); //added (register state change to slave, first param is dcpId)

        b.join();
    }

private:
    void initialize(uint8_t id) {
        std::cout << "Initialize Slave" << std::endl;
        manager->STC_initialize(id, DcpState::CONFIGURED);
        initRuns++;
    }

    void configuration(uint8_t id) {
        std::cout << "Configure Slaves" << std::endl;
        receivedAcks[id] = 0;

        if (id == 1){

        manager->CFG_scope(1, 1, DcpScope::Initialization_Run_NonRealTime);
        manager->CFG_scope(1, 2, DcpScope::Initialization_Run_NonRealTime);

        manager->CFG_input(1, 1, 0, slaveDescription->Variables.at(1).valueReference, DcpDataType::float64);
        
        manager->CFG_output(1, 2, 0, slaveDescription->Variables.at(0).valueReference);

        manager->CFG_steps(1, 1, 1);
        manager->CFG_steps(1, 2, 1);

        manager->CFG_time_res(1, slaveDescription->TimeRes.resolutions.front().numerator,
                                 slaveDescription->TimeRes.resolutions.front().denominator);

        manager->CFG_source_network_information_UDP(1, 1, asio::ip::address_v4::from_string(
                        *slaveDescription->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription->TransportProtocols.UDP_IPv4->Control->port);
        manager->CFG_target_network_information_UDP(1, 1,  asio::ip::address_v4::from_string(
                *slaveDescription2->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription2->TransportProtocols.UDP_IPv4->Control->port);

        manager->CFG_source_network_information_UDP(1, 2, asio::ip::address_v4::from_string(
                        *slaveDescription->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription->TransportProtocols.UDP_IPv4->Control->port);
        manager->CFG_target_network_information_UDP(1, 2,  asio::ip::address_v4::from_string(
                *slaveDescription2->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription2->TransportProtocols.UDP_IPv4->Control->port);
        numOfCmd[1] = 9;
        }
        else {

        manager->CFG_scope(2, 1, DcpScope::Initialization_Run_NonRealTime);
        manager->CFG_scope(2, 2, DcpScope::Initialization_Run_NonRealTime);

        manager->CFG_input(2, 2, 0, slaveDescription2->Variables.at(1).valueReference, DcpDataType::float64);

        manager->CFG_output(2, 1, 0, slaveDescription2->Variables.at(0).valueReference);

        manager->CFG_steps(2, 1, 1);
        manager->CFG_steps(2, 2, 1);

        manager->CFG_time_res(2, slaveDescription2->TimeRes.resolutions.front().numerator,
                                 slaveDescription2->TimeRes.resolutions.front().denominator);  

        manager->CFG_source_network_information_UDP(2, 1, asio::ip::address_v4::from_string(
                        *slaveDescription2->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription2->TransportProtocols.UDP_IPv4->Control->port);
        manager->CFG_target_network_information_UDP(2, 1,  asio::ip::address_v4::from_string(
                *slaveDescription->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription->TransportProtocols.UDP_IPv4->Control->port);
        
        manager->CFG_source_network_information_UDP(2, 2, asio::ip::address_v4::from_string(
                        *slaveDescription2->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription2->TransportProtocols.UDP_IPv4->Control->port);
        manager->CFG_target_network_information_UDP(2, 2,  asio::ip::address_v4::from_string(
                *slaveDescription->TransportProtocols.UDP_IPv4->Control->host).to_ulong(), *slaveDescription->TransportProtocols.UDP_IPv4->Control->port);
        numOfCmd[2] = 9;
        }
    }

    void configure(uint8_t id) {
        manager->STC_configure(id, DcpState::PREPARED);
    }

    void run(DcpState currentState, uint8_t id) {
        std::cout << "Run Simulation" << std::endl;
        std::time_t now = std::time(0);
        manager->STC_run(id, currentState, now + 2); //added state change to RUNNING. change is immediate but simulated time starts after 2 steps
    }

    void stop(uint8_t id) {
        std::chrono::seconds dura(secondsToSimulate + 2);
        std::this_thread::sleep_for(dura);
        std::cout << "Stop Simulation" << std::endl;

        manager->STC_stop(id, DcpState::RUNNING); //added state change to STOP when current state is RUNNING
    }

    void deregister(uint8_t id) {
        std::cout << "Deregister Slaves" << std::endl;

        manager->STC_deregister(id, DcpState::STOPPED); //added deregistering of slave when current state is STOPPED
    }

    void sendOutputs(uint8_t id) {
        std::cout << "Send Outputs" << std::endl;

        manager->STC_send_outputs(id, DcpState::INITIALIZED); //added state change to send_outputs (where slave sends initialization results) when state is INITIALIZED
    }

    void receiveAck(uint8_t sender, uint16_t pduSeqId) {
        receivedAcks[sender]++;
        if (receivedAcks[sender] == numOfCmd[sender]) {
            manager->STC_prepare(sender, DcpState::CONFIGURATION);
        }
    }

    void receiveNAck(uint8_t sender, uint16_t pduSeqId,
                     DcpError errorCode) {
        std::cerr << "Error in slave configuration." << std::endl;
        std::exit(1);
    }

    void receiveStateChangedNotification(uint8_t sender,
                                         DcpState state) {
        std::chrono::milliseconds dura(250);
        std::this_thread::sleep_for(dura);
        switch (state) {
            case DcpState::CONFIGURATION:
                configuration(sender);
                break;
            case DcpState::CONFIGURED:
                if (initRuns < maxInitRuns) {
                    initialize(sender);
                } else {
                    run(DcpState::CONFIGURED, sender);
                }
                break;
            case DcpState::SYNCHRONIZED:
                run(DcpState::SYNCHRONIZED, sender);
                break;

            case DcpState::PREPARED:
                configure(sender);
                break;

            case DcpState::INITIALIZED:
                sendOutputs(sender);
                break;

            case DcpState::RUNNING: {
                stop(sender);
                break;
            }
            case DcpState::STOPPED:
                deregister(sender);
                break;
            case DcpState::ALIVE:
                //simulation finished
                std::exit(0);
                break;
        }
    }

    void logAck(uint8_t sender, uint16_t pduSeqId, std::shared_ptr<std::vector<LogEntry>> entries);

    OstreamLog stdLog;

    uint8_t maxInitRuns = 2;
    uint8_t initRuns = 0;

    std::map<dcpId_t, DcpState> curState;

    UdpDriver *driver;
    const char *const HOST = "192.168.0.249"; //LINUX ADDRESS
    const uint16_t PORT = 8081;

    DcpManagerMaster *manager;

    uint64_t secondsToSimulate = 5;
    std::map<dcpId_t, uint8_t> numOfCmd;
    std::map<dcpId_t, uint64_t> receivedAcks;


    std::shared_ptr<SlaveDescription_t> slaveDescription;
    std::shared_ptr<SlaveDescription_t> slaveDescription2; //added


};

#endif /* ACI_EXAMPLE_MASTER_H_ */
