#pragma once

#include "Hazel/Rendering/GraphicsContext/GraphicsContext.h"
#include "Hazel/Core/FileSystem/OpenFileException.h"
#include "TextureFormatHelper.h"
#include "Image.h"

namespace Hazel
{
	class TextureFactory
	{
	public:
		static std::shared_ptr<Texture> CreateTextureFromFile(GraphicsContext &graphicsContext, const std::string &filename)
		{
			Image image(filename);
			if (image.IsEmpty())
			{
				throw OpenFileException(filename);
			}
			TextureInfo info;
			info.Size = image.GetSize();
			info.Format = TextureFormatHelper::GetTextureFormat(image.GetChannelCount());
			auto texture = graphicsContext.CreateTexture(info);
			texture->BufferData(image.GetData());
			return texture;
		}

		static std::shared_ptr<Texture> CreateFlatTexture(GraphicsContext &graphicsContext, const glm::vec4 &color)
		{
			TextureInfo info;
			info.Size = {1.0f, 1.0f};
			info.Format = TextureFormat::Rgba8;
			auto texture = graphicsContext.CreateTexture(info);
			unsigned char data[4] = {
				static_cast<unsigned char>(255.0f * color.r),
				static_cast<unsigned char>(255.0f * color.g),
				static_cast<unsigned char>(255.0f * color.b),
				static_cast<unsigned char>(255.0f * color.a)
			};
			texture->BufferData(data);
			return texture;
		}
	};
}