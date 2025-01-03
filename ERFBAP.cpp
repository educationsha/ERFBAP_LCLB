// ERFBAP Algorithm Implementation in NS-3 and OMNeT++
//Shahul Hameed Chettali

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/energy-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv4-routing-helper.h"

using namespace ns3;

void ERFBAPAlgorithm(NodeContainer nodes) {
    
    InternetStackHelper stack;
    stack.Install(nodes);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");

    
    NetDeviceContainer devices = p2p.Install(nodes);
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    while (true) { 

        for (auto event : DataTransmissionEvents) { 
            Ptr<Node> nextNode = DetermineNextNode(event); 

            if (RaceConditionDetected(common_nodes)) { 
                ImplementPriorityScheduling(); 
            } else {
                AllocateTimeSlots(event);
            }
            UpdateRoutingTable(); 
        }
    }
}


int main(int argc, char *argv[]) {
    NodeContainer nodes;
    nodes.Create(10);

    ERFBAPAlgorithm(nodes);

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}

