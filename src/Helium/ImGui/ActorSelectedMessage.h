#pragma once

#include "Helium/HeliumPrecompiled.h"

#include "Helium/Messaging/Messages.h"
#include "Helium/ObjectModel/Handle.h"

heliumBegin

class Actor;

struct ActorSelectedMessage
{
	MESSAGE(ActorSelectedMessage);

	Handle<Actor> Actor;
};

heliumEnd
