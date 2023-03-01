#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :m_Width(width), m_Height(height)
	{
		HZ_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;	//内部格式
		m_DataFormat = GL_RGBA;			//数据格式

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);		//创建2D纹理
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);	//存储2D纹理 - - 内部格式 - -

		//设置纹理参数
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//缩小过滤器 线性插值
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//放大过滤器 最近滤波

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);		//x超过0-1 重复
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);		//y超过0-1 重复
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :m_Path(path)
	{
		HZ_PROFILE_FUNCTION();

		int width, height, channels;	//宽 高 通道数
		stbi_set_flip_vertically_on_load(1);	//垂直翻转
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);	//加载图片

		HZ_CORE_ASSERT(data, "Failed to load image!");	//加载失败

		m_Width = width;
		m_Height = height;
		
		GLenum internalFormat = 0, dataFormat = 0;	//内部格式（存储格式），数据格式

		if (channels == 4) {		//颜色通道4
			internalFormat = GL_RGBA8;	//每个通道8位
			dataFormat = GL_RGBA;
		}
		else if(channels == 3){		//颜色通道3
			internalFormat = GL_RGB8;	//每个通道8位
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		HZ_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");	//不支持此格式

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);	//创建2D纹理
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);	//存储2D纹理 - - 内部格式 - -

		//设置纹理参数
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//缩小过滤器 线性插值
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//放大过滤器 最近滤波

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);		//x超过0-1 重复
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);		//y超过0-1 重复

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);	//生成纹理到GPU

		stbi_image_free(data);	//释放data
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);	//删除纹理
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		HZ_PROFILE_FUNCTION();

		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;	//每个像素字节数
		HZ_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");	//纹理数据不完整

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);	//生成纹理到GPU
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		HZ_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);	//绑定纹理到 slot 槽位
	}
}