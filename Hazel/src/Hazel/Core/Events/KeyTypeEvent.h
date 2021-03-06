#pragma once

#include "Event.h"

namespace Hazel
{
	class KeyTypeEvent : public Event
	{
	public:
		static constexpr EventType Type = EventType::KeyType;

	private:
		uint32_t key = 0;

	public:
		constexpr KeyTypeEvent(uint32_t key)
			: Event(Type, EventCategory::Input | EventCategory::Keyboard),
			key(key)
		{
		}

		constexpr uint32_t GetKey() const
		{
			return key;
		}

		virtual std::string ToString() const override
		{
			return (std::ostringstream() << GetName() << ": " << key).str();
		}
	};
}