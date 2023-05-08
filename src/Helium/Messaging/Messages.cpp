#include "Helium/HeliumPrecompiled.h"

#include "Messages.h"

heliumBegin

UnsafeHandle<MessagingBus> MessagingBus::GetInstance()
{
	return &s_Instance;
}

MessagingBus MessagingBus::s_Instance;

heliumEnd


