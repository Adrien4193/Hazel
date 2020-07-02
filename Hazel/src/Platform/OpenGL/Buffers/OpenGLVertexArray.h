#pragma once

#include "Hazel/Rendering/Buffers/VertexArray.h"

namespace Hazel
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		unsigned int id = 0;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override;
		virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer) override;

	private:
		void SetupVerticesAttributes(const BufferLayout &layout);
		void SetupVertexAttributes(size_t index, const BufferLayout &layout);
	};
}