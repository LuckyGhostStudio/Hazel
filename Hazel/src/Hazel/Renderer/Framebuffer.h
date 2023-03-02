#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
	/// <summary>
	/// ֡�������淶
	/// </summary>
	struct FramebufferSpecification
	{
		uint32_t Width;		//֡��������
		uint32_t Height;	//֡��������

		uint32_t Samples = 1;

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
		/// <returns>��ɫ������ID</returns>
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
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