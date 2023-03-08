#pragma once

#include <string>

namespace Hazel
{
	/// <summary>
	/// �ļ��Ի���
	/// </summary>
	class FileDialogs
	{
	public:
		/// <summary>
		/// ���ļ���ȡ���򷵻ؿ��ַ���
		/// </summary>
		/// <param name="filter">�ļ����������ļ�����</param>
		/// <returns>�ļ�·��</returns>
		static std::string OpenFile(const char* filter);

		/// <summary>
		/// �����ļ���ȡ���򷵻ؿ��ַ���
		/// </summary>
		/// <param name="filter">�ļ����������ļ�����</param>
		/// <returns>�ļ�·��</returns>
		static std::string SaveFile(const char* filter);
	};
}