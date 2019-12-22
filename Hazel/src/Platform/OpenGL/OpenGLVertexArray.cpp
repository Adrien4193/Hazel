#include "OpenGLVertexArray.h"

#include "glad/glad.h"

#include "OpenGLShader.h"

namespace Hazel
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &rendererId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &rendererId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(rendererId);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    const std::vector<std::shared_ptr<VertexBuffer>> &OpenGLVertexArray::GetVertexBuffers() const
    {
        return vertexBuffers;
    }

    const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const
    {
        return indexBuffer;
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer)
    {
        vertexBuffers.push_back(buffer);
        glBindVertexArray(rendererId);
        buffer->Bind();
        const auto &layout = buffer->GetLayout();
        for (size_t i = 0; i < layout.GetSize(); i++)
        {
            SetupVertexAttributes(layout, i);
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer)
    {
        indexBuffer = buffer;
        glBindVertexArray(rendererId);
        buffer->Bind();
    }

    void OpenGLVertexArray::SetupVertexAttributes(const BufferLayout &layout, size_t index)
    {
        const auto &element = layout.GetElement(index);
        glEnableVertexAttribArray((int)index);
        glVertexAttribPointer(
            (int)index,
            (int)element.GetComponentCount(),
            OpenGLShader::GetInternalType(element.GetType()),
            element.IsNormalized() ? GL_TRUE : GL_FALSE,
            (int)layout.GetStride(),
            (const void *)element.GetOffset());
    }
}