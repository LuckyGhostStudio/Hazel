#pragma once

#include "Hazel/Renderer/Texture.h"

#include <glad/glad.h>

namespace Hazel
{
	/// <summary>
	/// OpenGL 2D纹理
	/// </summary>
	class OpenGLTexture2D :public Texture2D
	{
	private:
		uint32_t m_RendererID;		//纹理id
		uint32_t m_Width;			//宽
		uint32_t m_Height;			//高
		std::string m_Path;			//路径

		GLenum m_InternalFormat;	//内部格式（存储格式）
		GLenum m_DataFormat;		//数据格式（采样格式）
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const  override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		/// <summary>
		/// 设置纹理数据
		/// </summary>
		/// <param name="data">数据（纹理颜色值）</param>
		/// <param name="size">纹理大小（字节）</param>
		virtual void SetData(void* data, uint32_t size) override;

		/// <summary>
		/// 绑定纹理
		/// </summary>
		/// <param name="slot">绑定槽位</param>
		virtual void Bind(uint32_t slot = 0) const override;

		/// <summary>
		/// 比较两个纹理是否相等
		/// </summary>
		/// <param name="other">另一个纹理</param>
		/// <returns>比较结果</returns>
		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}
	};
}