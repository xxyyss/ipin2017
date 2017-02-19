#include <cassert>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>

#include "RangingApplication.h"
#include "RangingHost.h"

using namespace omnetpp;
using namespace inet;
using namespace inet::physicallayer;
using namespace std;

namespace ipin2017
{

Define_Module(RangingApplication);

void
RangingApplication::initialize (int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // ...
    }
}

void
RangingApplication::sendMacPacket (const inet::MACAddress& destinationAddress,
                                   unique_ptr<RangingPacket> packet,
                                   const SimTime& delay)
{
    assert (packet);
    auto ranginghHst = check_and_cast<RangingHost*> (getParentModule ());
    auto controlInformation = unique_ptr<Ieee802Ctrl> {new Ieee802Ctrl};
    controlInformation->setSourceAddress (ranginghHst->getLocalAddress ());
    controlInformation->setDest (destinationAddress);
    packet->setControlInfo (controlInformation.release ());
    sendDelayed (packet.release (), delay, "out");
}

void
RangingApplication::scheduleSelfMessage (unique_ptr<cMessage> message,
                                         unsigned int delay,
                                         SimTimeUnit delay_unit)
{
    const auto timestamp = simTime () + SimTime {delay, delay_unit};
    scheduleAt (timestamp, message.release ());
}

int
RangingApplication::numInitStages () const
{
    return NUM_INIT_STAGES;
}

} //namespace ipin2017
