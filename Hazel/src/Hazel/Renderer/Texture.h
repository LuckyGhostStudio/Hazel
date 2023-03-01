#pragma once

namespace Hazel
{
	/// <summary>
	/// ����
	/// </summary>
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="slot">�����λ</param>
		virtual void Bind(uint32_t slot = 0) const = 0;

		/// <summary>
		/// �Ƚ����������Ƿ����
		/// </summary>
		/// <param name="other">��һ������</param>
		/// <returns>�ȽϽ��</returns>
		virtual bool operator==(const Texture& other) const = 0;
	};

	/// <summary>
	/// 2D����
	/// </summary>
	class Texture2D :public Texture
	{
	public:
		/// <summary>
		/// ����2D����
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		/// <returns>2D����</returns>
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);

		/// <summary>
		/// ����2D����
		/// </summary>
		/// <param name="path">����·��</param>
		/// <returns>2D����</returns>
		static Ref<Texture2D> Create(const std::string& path);
	};
}