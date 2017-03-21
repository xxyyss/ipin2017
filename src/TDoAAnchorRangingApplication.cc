#include <cassert>
#include <memory>
#include <algorithm>
#include <fstream>

#include <INETDefs.h>
#include <TDoAAnchorRangingApplication.h>
#include <MACAddress.h>
#include <IdealMacFrame_m.h>
#include <Ieee802Ctrl.h>

#include "RangingHost.h"
#include "Utilities.h"
#include "RangingHost.h"

using namespace inet;
using namespace inet::physicallayer;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(TDoAAnchorRangingApplication);

void
TDoAAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto& broadcastBeaconDelayParamater = par ("broadcastBeaconDelay");
        assert (broadcastBeaconDelayParamater.getType () == cPar::LONG);
        broadcastBeaconDelay = broadcastBeaconDelayParamater.longValue ();

        const auto& echoBeaconDelayParamater = par ("echoBeaconDelay");
        assert (echoBeaconDelayParamater.getType () == cPar::LONG);
        echoBeaconDelay = SimTime {echoBeaconDelayParamater.longValue (), SIMTIME_US};

        if (broadcastBeaconDelay > 0)
        {
            unique_ptr<TDoAAnchorSelfMessage> message {new TDoAAnchorSelfMessage {}};
            message->setEventType (BROADCAST_BEACON);
            scheduleSelfMessage (move (message), broadcastBeaconDelay, SIMTIME_MS);
        }
    }
}

void
TDoAAnchorRangingApplication::finish ()
{
    RangingApplication::finish ();
}

void
TDoAAnchorRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())
    {
        handleSelfMessage (check_and_cast<TDoAAnchorSelfMessage*> (message));
    }
    else
    {
        handlFrame (check_and_cast<BeaconFrame*> (message));
    }

    delete message;
}

void
TDoAAnchorRangingApplication::handlFrame (BeaconFrame* frame)
{
    sendBeaconFrame (echoBeaconDelay);
}

void
TDoAAnchorRangingApplication::handleSelfMessage (TDoAAnchorSelfMessage* selfMessage)
{
    sendBeaconFrame (0);
}

unsigned int
TDoAAnchorRangingApplication::getCurrentPacketSequenceNumber () const
{
    return packetSequenceNumberGenerator;
}

unsigned int
TDoAAnchorRangingApplication::getNextPacketSequenceNumber ()
{
    return ++packetSequenceNumberGenerator;
}

void
TDoAAnchorRangingApplication::sendBeaconFrame (const SimTime& delay)
{
    // Prepare & send beacon
    unique_ptr<BeaconFrame> frame {new BeaconFrame {}};

    frame->setBitLength (10);
    frame->setSequenceNumber (getNextPacketSequenceNumber ());

    sendFrame (MACAddress::BROADCAST_ADDRESS, unique_ptr<Frame> (frame.release ()), delay);
}

}; // namespace ipin2017