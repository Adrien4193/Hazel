#pragma once

namespace Hazel
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        virtual void Bind(unsigned int slot = 0) const = 0;
    };
}