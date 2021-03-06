#pragma once

#include <memory>

#include "Hazel/Rendering/Framebuffers/Framebuffer.h"
#include "Hazel/Rendering/Textures/OpenGL/OpenGLTexture.h"

namespace Hazel
{
	class OpenGLFramebuffer : public Framebuffer
	{
	private:
		uint32_t id;
		std::shared_ptr<OpenGLTexture> colorAttachment;
		std::shared_ptr<OpenGLTexture> depthAttachment;

	public:
		OpenGLFramebuffer(const FramebufferInfo &info);
		virtual ~OpenGLFramebuffer();

		uint32_t GetStatus() const;
		bool IsComplete() const;
		const std::string &GetStatusName() const;
		void SetColorAttachment(const std::shared_ptr<OpenGLTexture> &colorAttachment);
		void SetDepthAttachment(const std::shared_ptr<OpenGLTexture> &depthAttachment);
		void Bind() const;
		void Unbind() const;

		virtual Texture &GetColorAttachment() const override;
		virtual Texture &GetDepthAttachment() const override;

		uint32_t GetId() const
		{
			return id;
		}

	private:
		void Attach(int attachmentType, const std::shared_ptr<OpenGLTexture> &texture);
	};
}