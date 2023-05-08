#pragma once

#include "Helium/HeliumPrecompiled.h"
#include "Helium/Utility/CRC32.h"
#include "Helium/ObjectModel/UnsafeHandle.h"

#include <type_traits>

heliumBegin

#define MESSAGE(messageName) \
using Self = messageName; \
static inline String Name = nameof(messageName); \
static inline CRC32 MessageID = CRC32_COMPUTE(nameof(messageName));

template <typename TReturn, typename... TArgs>
void* GetAddressOfFunction(std::function<TReturn(TArgs...)> func)
{
	return reinterpret_cast<void*>(func.template target<TReturn (TArgs...)>());
}

class MessagingBus final
{
public:
	MessagingBus() = default;

	static UnsafeHandle<MessagingBus> GetInstance();

	template <typename T>
	void Subscribe(std::function<void (const std::remove_cvref_t<T>&)> func)
	{
		auto it = m_Subscribers.find(T::MessageID);
		if (it == m_Subscribers.end())
		{
			m_Subscribers[T::MessageID] = std::vector<std::function<void (const void*)>>();
		}
		m_Subscribers[T::MessageID].push_back([func](const void* data)
		{
			func(*static_cast<const T*>(data));
		});
	}

	template <typename T>
	void Unsubscribe(std::function<void(const std::remove_cvref_t<T>&)> func)
	{
		auto it = m_Subscribers.find(T::MessageID);
		if (it != m_Subscribers.end())
		{
			auto& subscribers = it->second;
			for (auto it = subscribers.begin(); it != subscribers.end(); ++it)
			{
				const auto& subscriber = *it;
				if (GetAddressOfFunction(subscriber) == GetAddressOfFunction(func))
				{
					subscribers.erase(it);
					break;
				}
			}
		}
	}

	template <typename T>
	void Publish(const std::remove_cvref_t<T>& message)
	{
		auto it = m_Subscribers.find(T::MessageID);
		if (it != m_Subscribers.end())
		{
			auto& subscribers = it->second;
			for (auto& subscriber : subscribers)
			{
				subscriber(&message);
			}
		}
	}

private:
	std::unordered_map<CRC32, std::vector<std::function<void (const void*)>>> m_Subscribers;

private:
	static MessagingBus s_Instance;
};

#define MESSAGE_SUBSCRIBE(messageName, func) \
MessagingBus::GetInstance()->Subscribe<messageName>(func);

#define MESSAGE_UNSUBSCRIBE(messageName, func) \
MessagingBus::GetInstance()->Unsubscribe<messageName>(func);

#define MESSAGE_PUBLISH(messageName, message) \
MessagingBus::GetInstance()->Publish<messageName>(message);

#define MESSAGE_LISTENER(funcName) \
std::bind(&self::funcName, this, std::placeholders::_1)

heliumEnd
