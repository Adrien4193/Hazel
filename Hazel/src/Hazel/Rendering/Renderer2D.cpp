#include "Renderer2D.h"

#include "Hazel/Textures/TextureBuilder.h"

namespace Hazel
{
	BatchInfo Renderer2D::GetBatchInfo(const RendererInfo &rendererInfo)
	{
		BatchInfo batchInfo;
		batchInfo.MaxIndexCount = rendererInfo.MaxIndexCount;
		batchInfo.MaxVertexCount = rendererInfo.MaxVertexCount;
		batchInfo.MaxTextureSlotCount = rendererInfo.GraphicsContext->GetMaxTextureSlotCount();
		batchInfo.IndexFormat = rendererInfo.IndexFormat;
		return batchInfo;
	}

	Renderer2D::Renderer2D(const RendererInfo &info)
		: info(info),
		batch(*info.GraphicsContext, GetBatchInfo(info))
	{
		info.GraphicsContext->SetIndexFormat(info.IndexFormat);
		info.GraphicsContext->SetPrimitiveTopology(PrimitiveTopology::Triangles);
	}

	void Renderer2D::BeginScene(const OrthographicCamera &camera)
	{
		batch.SetViewProjectionMatrix(camera.GetViewProjectionMatrix());
		statistics.Reset();
	}

	void Renderer2D::Render(const DrawData &drawData)
	{
		if (!batch.Add(drawData))
		{
			EndScene();
			if (!batch.Add(drawData))
			{
				throw BatchException("The batch is too small for the object.");
			}
		}
	}

	void Renderer2D::EndScene()
	{
		batch.BindTextures();
		batch.BufferData();
		info.GraphicsContext->DrawIndexed(batch.GetIndexCount());
		statistics.DrawCallCount++;
		statistics.IndexCount += batch.GetIndexCount();
		statistics.VertexCount += batch.GetVertexCount();
		statistics.TextureCount = batch.GetTextureCount();
		batch.Clear();
	}
}