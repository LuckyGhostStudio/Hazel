#pragma once

#include "Hazel/Renderer/Framebuffer.h"

namespace Hazel
{
	/// <summary>
	/// OpenGL帧缓冲区
	/// </summary>
	class OpenGLFramebuffer :public Framebuffer
	{
	public:
		/// <summary>
		/// OpenGL帧缓冲区
		/// </summary>
		/// <param name="spec">帧缓冲区规范</param>
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		/// <summary>
		/// 调整大小：使无效
		/// </summary>
		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		/// <summary>
		/// 重置帧缓冲区大小
		/// </summary>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		virtual void Resize(uint32_t width, uint32_t height) override;
		
		/// <summary>
		/// 返回颜色缓冲区ID
		/// </summary>
		/// <returns>颜色缓冲区ID</returns>
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;					//帧缓冲区ID
		uint32_t m_ColorAttachment = 0;				//颜色缓冲区
		uint32_t m_DepthAttachment = 0;				//深度缓冲区
		FramebufferSpecification m_Specification;	//帧缓冲区规范
	};
}