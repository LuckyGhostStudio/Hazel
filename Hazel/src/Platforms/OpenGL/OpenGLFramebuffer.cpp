#include "hzpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Hazel
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) :m_Specification(spec)
	{
		Invalidate();
	}
	
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);		//删除帧缓冲区
		glDeleteTextures(1, &m_ColorAttachment);	//删除颜色缓冲区
		glDeleteTextures(1, &m_DepthAttachment);	//删除深度缓冲区
	}
	
	void OpenGLFramebuffer::Invalidate()
	{
		//帧缓冲区存在
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);		//删除帧缓冲区
			glDeleteTextures(1, &m_ColorAttachment);	//删除颜色缓冲区
			glDeleteTextures(1, &m_DepthAttachment);	//删除深度缓冲区
		}

		glCreateFramebuffers(1, &m_RendererID);				//创建帧缓冲区
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);	//绑定帧缓冲区

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);	//创建颜色缓冲区
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);		//绑定颜色缓冲区
		//纹理图像
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		//设置纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//缩小过滤器 线性插值
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//放大过滤器 线性插值
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);	//帧缓冲区颜色纹理

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);	//创建深度缓冲区
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);		//绑定深度缓冲区
		//深度缓冲区纹理存储 24位深度缓冲区 8位模板缓冲区
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);	//帧缓冲区深度纹理

		//检查帧缓冲区状态
		HZ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete！");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);	//解除绑定
	}
	
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);	//绑定帧缓冲区
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);	//设置视口大小
	}
	
	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);	//解除绑定
	}
	
	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}
}