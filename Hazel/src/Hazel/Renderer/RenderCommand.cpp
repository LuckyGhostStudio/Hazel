#include "hzpch.h"
#include "RenderCommand.h"


#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();	//��ǰ��Ⱦ��API Ϊ OpenGL��Ⱦ��API
}