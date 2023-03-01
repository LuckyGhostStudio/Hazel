#include "hzpch.h"
#include "RenderCommand.h"


#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();	//µ±Ç°äÖÈ¾Æ÷API Îª OpenGLäÖÈ¾Æ÷API
}