#pragma once

#include "glad/glad.h"

namespace Hazel
{
	class OpenGLInfo
	{
	public:
		static size_t GetMaxUniformBufferBindingCount()
		{
			int bindingCount;
			glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &bindingCount);
			return bindingCount;
		}

		static size_t GetMaxTextureSlotCount()
		{
			int slotCount;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slotCount);
			return slotCount;
		}
	};
}