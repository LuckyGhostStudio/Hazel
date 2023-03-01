#pragma once

namespace Hazel
{
	/// <summary>
	/// 纹理
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
		/// 绑定纹理
		/// </summary>
		/// <param name="slot">纹理槽位</param>
		virtual void Bind(uint32_t slot = 0) const = 0;

		/// <summary>
		/// 比较两个纹理是否相等
		/// </summary>
		/// <param name="other">另一个纹理</param>
		/// <returns>比较结果</returns>
		virtual bool operator==(const Texture& other) const = 0;
	};

	/// <summary>
	/// 2D纹理
	/// </summary>
	class Texture2D :public Texture
	{
	public:
		/// <summary>
		/// 创建2D纹理
		/// </summary>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		/// <returns>2D纹理</returns>
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);

		/// <summary>
		/// 创建2D纹理
		/// </summary>
		/// <param name="path">纹理路径</param>
		/// <returns>2D纹理</returns>
		static Ref<Texture2D> Create(const std::string& path);
	};
}