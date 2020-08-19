#pragma once

#include "Texture2D.h"
#include "TextureCoordinates.h"

namespace Hazel
{
	class SubTexture2D
	{
	private:
		std::shared_ptr<Texture2D> texture;
		glm::vec2 shift{0.0f};
		Size scale;
		float aspectRatio = 0.0f;

	public:
		SubTexture2D() = default;

		inline SubTexture2D(const std::shared_ptr<Texture2D> &texture)
			: texture(texture)
		{
		}

		inline SubTexture2D(const std::shared_ptr<Texture2D> &texture, const TextureCoordinates &coordinates)
			: texture(texture)
		{
			SetCoordinates(coordinates);
		}

		inline void SetCoordinates(const TextureCoordinates &coordinates)
		{
			if (texture)
			{
				auto size = texture->GetSize();
				shift = coordinates.GetShift(size);
				scale = coordinates.GetScale(size);
				aspectRatio = coordinates.GetAspectRatio();
			}
			else
			{
				shift = glm::vec2(0.0f);
				scale = Size();
				aspectRatio = 1.0f;
			}
		}

		inline glm::vec2 MapCoordinates(const glm::vec2 &coordinates) const
		{
			if (!texture)
			{
				return glm::vec2(0.0f);
			}
			return {
				shift.x + coordinates.x * scale.Width,
				shift.y + coordinates.y * scale.Height
			};
		}

		constexpr float GetAspectRatio() const
		{
			return aspectRatio;
		}

		inline operator bool() const
		{
			return static_cast<bool>(texture);
		}

		constexpr operator const std::shared_ptr<Texture2D> &() const
		{
			return texture;
		}
	};
}