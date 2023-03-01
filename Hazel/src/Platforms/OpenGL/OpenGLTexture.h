#pragma once

#include "Hazel/Renderer/Texture.h"

#include <glad/glad.h>

namespace Hazel
{
	/// <summary>
	/// OpenGL 2D����
	/// </summary>
	class OpenGLTexture2D :public Texture2D
	{
	private:
		uint32_t m_RendererID;		//����id
		uint32_t m_Width;			//��
		uint32_t m_Height;			//��
		std::string m_Path;			//·��

		GLenum m_InternalFormat;	//�ڲ���ʽ���洢��ʽ��
		GLenum m_DataFormat;		//���ݸ�ʽ��������ʽ��
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const  override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		/// <summary>
		/// ������������
		/// </summary>
		/// <param name="data">���ݣ�������ɫֵ��</param>
		/// <param name="size">�����С���ֽڣ�</param>
		virtual void SetData(void* data, uint32_t size) override;

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="slot">�󶨲�λ</param>
		virtual void Bind(uint32_t slot = 0) const override;

		/// <summary>
		/// �Ƚ����������Ƿ����
		/// </summary>
		/// <param name="other">��һ������</param>
		/// <returns>�ȽϽ��</returns>
		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}
	};
}