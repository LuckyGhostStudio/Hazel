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
		/// ����֡��������С
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		virtual void Resize(uint32_t width, uint32_t height) override;

		/// <summary>
		/// ��ȡ����
		/// </summary>
		/// <param name="attachmentIndex">��ɫ������id</param>
		/// <param name="x">x����</param>
		/// <param name="y">y����</param>
		/// <returns>�������ݣ������attachmentIndex��ɫ������������</returns>
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
		
		/// <summary>
		/// ���֡����������
		/// </summary>
		/// <param name="attachmentIndex">��ɫ������id</param>
		/// <param name="value">���ֵ</param>
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		/// <summary>
		/// ������ɫ������ID
		/// </summary>
		/// <param name="index">id�б�����</param>
		/// <returns>��ɫ������ID</returns>
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
		{
			HZ_CORE_ASSERT(index < m_ColorAttachments.size(), "index Խ�磡");
			return m_ColorAttachments[index]; 
		}
		
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;					//֡������ID
		FramebufferSpecification m_Specification;	//֡�������淶

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecs;					//��ɫ�������淶�б�
		FramebufferTextureSpecification m_DepthAttachmentSpec = FramebufferTextureFormat::None;	//��Ȼ������淶

		std::vector<uint32_t> m_ColorAttachments;	//��ɫ������ID�б�
		uint32_t m_DepthAttachment = 0;				//��Ȼ�����ID
	};
}