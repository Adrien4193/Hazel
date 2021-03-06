#pragma once

#include "glad/glad.h"

#include "Hazel/Rendering/Mesh/DataType.h"

namespace Hazel
{
	class OpenGLDataType
	{
	public:
		static constexpr uint32_t GetDataType(DataType dataType)
		{
			switch (dataType)
			{
			case DataType::Float:
				return GL_FLOAT;
			case DataType::Int:
				return GL_INT;
			case DataType::Bool:
				return GL_BOOL;
			}
			return 0;
		}
	};
}