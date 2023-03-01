#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace Hazel 
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		//无API
				HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:	//OpenGL
				return CreateRef<OpenGLVertexArray>();	//创建顶点数组
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}