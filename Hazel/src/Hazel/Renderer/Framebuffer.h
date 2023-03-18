#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
	/// <summary>
	/// 帧缓冲区纹理格式
	/// </summary>
	enum class FramebufferTextureFormat
	{
		None = 0,

		RGBA8,				//颜色
		RED_INTEGER,

		DEFPTH24STENCIL8,	//深度模板

		Depth = DEFPTH24STENCIL8	//默认值
	};

	/// <summary>
	/// 帧缓冲区纹理规范
	/// </summary>
	struct FramebufferTextureSpecification
	{
		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;	//纹理格式

		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) :TextureFormat(format) {}
	};

	/// <summary>
	/// 帧缓冲区附件规范
	/// </summary>
	struct FramebufferAttachmentSpecification
	{
		std::vector<FramebufferTextureSpecification> Attachments;	//附件列表

		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) 
			:Attachments(attachments) {}
	};

	/// <summary>
	/// 帧缓冲区规范
	/// </summary>
	struct FramebufferSpecification
	{
		uint32_t Width;		//帧缓冲区宽
		uint32_t Height;	//帧缓冲区高
		FramebufferAttachmentSpecification Attachments;	//帧缓冲区所有附件规范
		uint32_t Samples = 1;	//采样数量

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
		/// <param name="index">id列表索引</param>
		/// <returns>颜色缓冲区ID</returns>
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		/// <summary>
		/// 重置帧缓冲区大小
		/// </summary>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// 读取像素
		/// </summary>
		/// <param name="attachmentIndex">颜色缓冲区id</param>
		/// <param name="x">x坐标</param>
		/// <param name="y">y坐标</param>
		/// <returns>像素数据：输出到attachmentIndex颜色缓冲区的数据</returns>
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		/// <summary>
		/// 清除帧缓冲区附件
		/// </summary>
		/// <param name="attachmentIndex">颜色缓冲区id</param>
		/// <param name="value">清除值</param>
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

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