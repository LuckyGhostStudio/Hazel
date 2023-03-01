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
			PushLayer(new EditorLayer());		//Ìí¼Ó±à¼­Æ÷²ã
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