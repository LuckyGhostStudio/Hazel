#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel
{
	class HazelEditor :public Application
	{
	public:
		HazelEditor() :Application("Hazel Editor")
		{
			PushLayer(new EditorLayer());		//��ӱ༭����
		}

		~HazelEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	}
}