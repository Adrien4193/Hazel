#pragma once

#include "Event.h"

namespace Hazel
{
    class HAZEL_API ApplicationEvent : public Event
    {
    public:
        ApplicationEvent() = default;
    };
}