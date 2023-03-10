#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
	/// <summary>
	/// ֡�����������ʽ
	/// </summary>
	enum class FramebufferTextureFormat
	{
		None = 0,
		RGBA8,				//��ɫ
		DEFPTH24STENCIL8,	//���ģ��

		Depth = DEFPTH24STENCIL8	//Ĭ��ֵ
	};

	/// <summary>
	/// ֡����������淶
	/// </summary>
	struct FramebufferTextureSpecification
	{
		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;	//�����ʽ

		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) :TextureFormat(format) {}
	};

	/// <summary>
	/// ֡�����������淶
	/// </summary>
	struct FramebufferAttachmentSpecification
	{
		std::vector<FramebufferTextureSpecification> Attachments;	//�����б�

		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) 
			:Attachments(attachments) {}
	};

	/// <summary>
	/// ֡�������淶
	/// </summary>
	struct FramebufferSpecification
	{
		uint32_t Width;		//֡��������
		uint32_t Height;	//֡��������
		FramebufferAttachmentSpecification Attachments;	//֡���������и����淶
		uint32_t Samples = 1;	//��������

		bool SwapChainTarget = false;	//�Ƿ�Ҫ��Ⱦ����Ļ
	};

	/// <summary>
	/// ֡������
	/// </summary>
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		/// <summary>
		/// ������ɫ������ID
		/// </summary>
		/// <param name="index">id�б�����</param>
		/// <returns>��ɫ������ID</returns>
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		/// <summary>
		/// ����֡��������С
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// ����֡������
		/// </summary>
		/// <param name="spec">֡�������淶</param>
		/// <returns>֡������</returns>
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}