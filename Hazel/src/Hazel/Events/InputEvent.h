#pragma once

#include "Event.h"

namespace Hazel
{
    class HAZEL_API InputEvent : public Event
    {
    public:
        constexpr InputEvent() = default;
    };
}