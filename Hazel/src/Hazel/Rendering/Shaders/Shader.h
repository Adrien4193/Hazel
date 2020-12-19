#pragma once

#include "ShaderInfo.h"
#include "ShaderCompilationException.h"

namespace Hazel
{
	class Shader
	{
	private:
		std::string name;

	public:
		Shader(const std::string &name)
			: name(name)
		{
		}

		virtual ~Shader() = default;

		const std::string &GetName() const
		{
			return name;
		}
	};
}