#pragma once

#include "Hazel/Rendering/Textures/TextureInfo.h"
#include "OpenGLStorageColorFormat.h"
#include "OpenGLTextureFiltering.h"
#include "OpenGLTextureWrapping.h"

#include "glad/glad.h"

namespace Hazel
{
	class OpenGLTextureBuilder
	{
	public:
		static inline uint32_t Build(const TextureInfo &info)
		{
			auto id = CreateTexture(info);
			SetupTextureParameters(id, info);
			return id;
		}

		OpenGLTextureBuilder() = delete;

	private:
		static inline uint32_t CreateTexture(const TextureInfo &info)
		{
			uint32_t id;
			glCreateTextures(GL_TEXTURE_2D, 1, &id);
			glTextureStorage2D(
				id,
				1,
				OpenGLStorageColorFormat::FromColorFormat(info.ColorFormat),
				static_cast<int>(info.Width),
				static_cast<int>(info.Height));
			return id;
		}

		static inline void SetupTextureParameters(uint32_t id, const TextureInfo &info)
		{
			glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, OpenGLTextureFiltering::FromTextureFiltering(info.MinFilter));
			glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, OpenGLTextureFiltering::FromTextureFiltering(info.MagFilter));
			glTextureParameteri(id, GL_TEXTURE_WRAP_S, OpenGLTextureWrapping::FromTextureWrapping(info.SWrap));
			glTextureParameteri(id, GL_TEXTURE_WRAP_T, OpenGLTextureWrapping::FromTextureWrapping(info.TWrap));
		}
	};
}