#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :m_Width(width), m_Height(height)
	{
		HZ_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;	//�ڲ���ʽ
		m_DataFormat = GL_RGBA;			//���ݸ�ʽ

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);		//����2D����
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);	//�洢2D���� - - �ڲ���ʽ - -

		//�����������
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//��С������ ���Բ�ֵ
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//�Ŵ������ ����˲�

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);		//x����0-1 �ظ�
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);		//y����0-1 �ظ�
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :m_Path(path)
	{
		HZ_PROFILE_FUNCTION();

		int width, height, channels;	//�� �� ͨ����
		stbi_set_flip_vertically_on_load(1);	//��ֱ��ת
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);	//����ͼƬ

		HZ_CORE_ASSERT(data, "Failed to load image!");	//����ʧ��

		m_Width = width;
		m_Height = height;
		
		GLenum internalFormat = 0, dataFormat = 0;	//�ڲ���ʽ���洢��ʽ�������ݸ�ʽ

		if (channels == 4) {		//��ɫͨ��4
			internalFormat = GL_RGBA8;	//ÿ��ͨ��8λ
			dataFormat = GL_RGBA;
		}
		else if(channels == 3){		//��ɫͨ��3
			internalFormat = GL_RGB8;	//ÿ��ͨ��8λ
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		HZ_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");	//��֧�ִ˸�ʽ

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);	//����2D����
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);	//�洢2D���� - - �ڲ���ʽ - -

		//�����������
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//��С������ ���Բ�ֵ
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//�Ŵ������ ����˲�

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);		//x����0-1 �ظ�
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);		//y����0-1 �ظ�

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);	//��������GPU

		stbi_image_free(data);	//�ͷ�data
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);	//ɾ������
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		HZ_PROFILE_FUNCTION();

		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;	//ÿ�������ֽ���
		HZ_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");	//�������ݲ�����

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);	//��������GPU
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		HZ_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);	//������ slot ��λ
	}
}