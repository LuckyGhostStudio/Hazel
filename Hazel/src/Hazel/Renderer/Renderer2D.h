#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "Hazel/Renderer/Camera.h"
#include "Hazel/Renderer/EditorCamera.h"
#include "Hazel/Scene/Components.h"

namespace Hazel
{
	class Renderer2D
	{
	public:
		/// <summary>
		/// 初始化渲染器
		/// </summary>
		static void Init();

		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);

		static void BeginScene(const EditorCamera& camera);
		
		/// <summary>
		/// 开始渲染场景：设置场景参数
		/// </summary>
		/// <param name="camera">相机</param>
		static void BeginScene(const OrthographicCamera& camera);


		/// <summary>
		/// 结束渲染场景
		/// </summary>
		static void EndScene();

		/// <summary>
		/// 刷新
		/// </summary>
		static void Flush();

		/// <summary>
		/// 绘制长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="color">颜色</param>
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		/// <summary>
		/// 绘制长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="color">颜色</param>
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		/// <summary>
		/// 绘制长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="texture">纹理</param>
		/// <param name="tilingFactor">纹理重复因子</param>
		/// <param name="tintColor">颜色</param>
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// 绘制长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="texture">纹理</param>
		/// <param name="tintColor">颜色</param>
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		
		/// <summary>
		/// 绘制长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="texture">子纹理</param>
		/// <param name="tilingFactor">纹理重复因子</param>
		/// <param name="tintColor">颜色</param>
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// 绘制长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="texture">子纹理</param>
		/// <param name="tintColor">颜色</param>
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

		/// <summary>
		/// 绘制旋转长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="rotation">旋转</param>
		/// <param name="color">颜色</param>
		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		/// <summary>
		/// 绘制旋转长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="rotation">旋转</param>
		/// <param name="color">颜色</param>
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		/// <summary>
		/// 绘制旋转长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="rotation">旋转</param>
		/// <param name="texture">纹理</param>
		/// <param name="tilingFactor">纹理重复因子</param>
		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// 绘制旋转长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="rotation">旋转</param>
		/// <param name="texture">纹理</param>
		/// <param name="tilingFactor">纹理重复因子</param>
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		/// <summary>
		/// 绘制旋转长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="rotation">旋转</param>
		/// <param name="texture">子纹理</param>
		/// <param name="tilingFactor">纹理重复因子</param>
		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// 绘制旋转长方形
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="size">大小</param>
		/// <param name="rotation">旋转</param>
		/// <param name="texture">子纹理</param>
		/// <param name="tilingFactor">纹理重复因子</param>
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);

		/// <summary>
		/// 统计数据
		/// </summary>
		struct Statistics
		{
			uint32_t DrawCalls = 0;	//绘制调用次数
			uint32_t QuadCount = 0;	//四边形个数

			/// <summary>
			/// 返回总顶点个数
			/// </summary>
			/// <returns></returns>
			uint32_t GetTotalVertexCount() { return QuadCount * 4; }

			/// <summary>
			/// 返回总索引个数
			/// </summary>
			/// <returns></returns>
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();

		/// <summary>
		/// 重置统计数据
		/// </summary>
		static void ResetStats();
	private:
		/// <summary>
		/// 开始新一批渲染
		/// </summary>
		static void FlushAndReset(); 
	};
}