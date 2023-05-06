#pragma once

#include "Helium/HeliumPrecompiled.h"

heliumBegin

union alignas(alignof(U64)) InstanceID
{
	U64 value;
	struct
	{
		U32 instance;
		U32 version;
	};

	constexpr InstanceID(U64 value) : value(value) {}
	constexpr InstanceID(U32 instance, U32 version) : instance(instance), version(version) {}
	constexpr Bool operator==(const InstanceID& other) const { return value == other.value; }
	constexpr Bool operator!=(const InstanceID& other) const { return value != other.value; }
	constexpr static U64 DefaultInstanceIDValue = std::numeric_limits<U64>::max();
};

constexpr InstanceID DefaultInstanceID = DefaultInstanceID;

heliumEnd
