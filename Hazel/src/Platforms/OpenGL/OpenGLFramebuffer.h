#pragma once

#include "Hazel/Renderer/Framebuffer.h"

namespace Hazel
{
	/// <summary>
	/// OpenGL֡������
	/// </summary>
	class OpenGLFramebuffer :public Framebuffer
	{
	public:
		/// <summary>
		/// OpenGL֡������
		/// </summary>
		/// <param name="spec">֡�������淶</param>
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		/// <summary>
		/// ������С��ʹ��Ч
		/// </summary>
		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;
		
		/// <summary>
		/// ������ɫ������ID
		/// </summary>
		/// <returns>��ɫ������ID</returns>
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID;						//֡������ID
		uint32_t m_ColorAttachment;					//��ɫ������
		uint32_t m_DepthAttachment;					//��Ȼ�����
		FramebufferSpecification m_Specification;	//֡�������淶
	};
}