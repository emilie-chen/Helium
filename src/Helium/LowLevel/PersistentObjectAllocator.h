#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Utility/Hex.h"

heliumBegin

class PersistentObjectAllocator final
{
public:
	template <typename T>
	static void* Allocate()
	{
		const size_t size = sizeof(T);
		const size_t align = alignof(T);
		if (s_BufferPtr + size > s_Buffer.data() + MaxSize)
		{
			assert(false);
			return nullptr;
		}
		std::byte* allocated = s_BufferPtr;
		// check alignment
		if (reinterpret_cast<size_t>(allocated) % align != 0)
		{
			allocated += align - (reinterpret_cast<size_t>(allocated) % align);
			assert(reinterpret_cast<size_t>(allocated) % align == 0);
		}

		s_BufferPtr = allocated + size;
#if _DEBUG
		spdlog::info("PersistentObjectAllocator: allocated {} bytes with alignment of {} bytes at {}. {} bytes allocated in total.", size, align, ToHex(allocated), (size_t)s_BufferPtr - (size_t)s_Buffer.data());
#endif
		return allocated;
	}

	static void Deallocate(void* instance)
	{
		// ignored, data is persistent
	}

private:
	static constexpr size_t MaxSize = 10000000;
	inline static std::array<std::byte, MaxSize> s_Buffer;
	inline static std::byte* s_BufferPtr = s_Buffer.data();
};

heliumEnd
