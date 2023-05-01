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
		spdlog::info("PersistentObjectAllocator: allocated {} bytes with alignment of {} bytes at {}. {} bytes allocated so far.", size, align, ToHex(allocated), (size_t)s_BufferPtr - (size_t)s_Buffer.data());
#endif
		return allocated;
	}

	static void Deallocate(void* instance)
	{
		// ignored, data is persistent
	}

	template <typename T>
	static void* AllocateArray(size_t count)
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

		s_BufferPtr = allocated + size * count;
#if _DEBUG
		spdlog::info("PersistentObjectAllocator: allocated an array of {} bytes in total with element alignment of {} bytes at {}. {} bytes allocated so far.", size, align, ToHex(allocated), (size_t)s_BufferPtr - (size_t)s_Buffer.data());
#endif

		return allocated;
	}

private:
	static constexpr size_t MaxSize = 10000000;
	inline static std::array<std::byte, MaxSize> s_Buffer;
	inline static std::byte* s_BufferPtr = s_Buffer.data();
};

//template <typename T>
//class PersistentObjectAllocatorStandardAdaptor
//{
//public:
//	using value_type = T;
//
//	template<class U>
//	constexpr PersistentObjectAllocatorStandardAdaptor(const PersistentObjectAllocatorStandardAdaptor<U>&) noexcept {}
//
//	PersistentObjectAllocatorStandardAdaptor() noexcept = default;
//
//	T* allocate(std::size_t n)
//	{
//		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
//			throw std::bad_array_new_length();
//
//		if (n == 0)
//			return nullptr;
//
//		if (n > 1)
//		{
//			return static_cast<T*>(PersistentObjectAllocator::AllocateArray<T>(n));
//		}
//
//		return static_cast<T*>(PersistentObjectAllocator::Allocate<T>());
//	}
//
//	void deallocate(T* p, std::size_t n) noexcept
//	{
//		PersistentObjectAllocator::Deallocate(p);
//	}
//};


heliumEnd
