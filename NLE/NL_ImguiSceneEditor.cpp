#include "NL_ImguiSceneEditor.h"
#include "NL_ThreadLocal.h"
#include "NL_Scene.h"
#include "NL_ScriptingContext.h"
#include "NL_ImguiScriptEditor.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiSceneEditor::ImguiSceneEditor() :
			_visible(false),
			_nameBuff(256)
		{
		}

		ImguiSceneEditor::~ImguiSceneEditor()
		{
		}

		bool& ImguiSceneEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiSceneEditor::draw(
			const CONSOLE::IConsoleQueueSP& consoleQueue,
			const GAME::IGameManagerSP& gameManager,
			Size2D screenSize,
			ImguiScriptEditor& scriptEditor
			)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Scene Editor", &_visible, windowFlags);

			_nameBuff.setText(gameManager->getCurrentScene().getName());

			ImGuiInputTextFlags flags = 0;
			flags |= ImGuiInputTextFlags_CallbackCompletion;
			flags |= ImGuiInputTextFlags_CallbackAlways;

			ImGui::InputText("Name", &_nameBuff[0], _nameBuff.getSize(), flags, [](ImGuiTextEditCallbackData* data) {
				std::string name(data->Buf);
				auto& gameManager = *static_cast<NLE::GAME::IGameManager*>(data->UserData);
				gameManager.getCurrentScene().setName(name);
				return 0;
			}, (void*)&gameManager);

			_scriptViewer.draw(
				consoleQueue,
				scriptEditor,
				[&]() ->SCRIPT::ScriptingContext& { return gameManager->getCurrentScene().getScriptingContext(); },
				[&]() { return gameManager->getCurrentScene().getName();
			});

			ImGui::End();
		}
	}
}