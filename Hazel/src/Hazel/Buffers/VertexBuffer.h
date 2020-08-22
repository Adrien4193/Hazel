#pragma once

#include "BufferLayout.h"

namespace Hazel
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual size_t GetSize() const = 0;
		virtual const BufferLayout &GetLayout() const = 0;
		virtual void SetData(const void *data, size_t size) = 0;
		virtual void SetLayout(const BufferLayout &layout) = 0;
	};
}