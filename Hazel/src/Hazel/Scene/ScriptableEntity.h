#pragma once

#include "Entity.h"

namespace Hazel
{
	/// <summary>
	/// 可脚本化实体：所有本地脚本的父类
	/// </summary>
	class ScriptableEntity
	{
	private:
		friend class Scene;
		Entity m_Entity;	//脚本挂载的实体
	public:
		virtual ~ScriptableEntity() {}

		/// <summary>
		/// 返回T类型组件
		/// </summary>
		/// <typeparam name="T">组件类型</typeparam>
		/// <returns>组件</returns>
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		/// <summary>
		/// 实体创建时调用
		/// </summary>
		virtual void OnCreate() {}

		/// <summary>
		/// 实体创建后每帧调用
		/// </summary>
		/// <param name="ts">帧间隔</param>
		virtual void OnUpdate(Timestep ts) {}

		/// <summary>
		/// 实体销毁时调用
		/// </summary>
		virtual void OnDestroy() {}
	};
}