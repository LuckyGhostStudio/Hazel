#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
	/// <summary>
	/// 帧缓冲区规范
	/// </summary>
	struct FramebufferSpecification
	{
		uint32_t Width;		//帧缓冲区宽
		uint32_t Height;	//帧缓冲区高

		uint32_t Samples = 1;

		bool SwapChainTarget = false;	//是否要渲染到屏幕
	};

	/// <summary>
	/// 帧缓冲区
	/// </summary>
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		/// <summary>
		/// 返回颜色缓冲区ID
		/// </summary>
		/// <returns>颜色缓冲区ID</returns>
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		/// <summary>
		/// 重置帧缓冲区大小
		/// </summary>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// 创建帧缓冲区
		/// </summary>
		/// <param name="spec">帧缓冲区规范</param>
		/// <returns>帧缓冲区</returns>
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}