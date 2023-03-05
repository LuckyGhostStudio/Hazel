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
	};
}