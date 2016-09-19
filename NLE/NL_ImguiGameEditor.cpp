#include "NL_ImguiGameEditor.h"
#include "NL_ThreadLocal.h"
#include "NL_IGameManager.h"
#include "NL_Game.h"
#include "NL_ScriptingContext.h"

#include <imgui.h>

namespace NLE
{
	namespace UI
	{
		ImguiGameEditor::ImguiGameEditor() :
			_visible(false),
			_nameBuff(256),
			_selectedScript(0)
		{
		}

		ImguiGameEditor::~ImguiGameEditor()
		{
		}

		bool& ImguiGameEditor::getVisibility()
		{
			return _visible;
		}

		void ImguiGameEditor::draw(
			CONSOLE::IConsoleQueue& consoleQueue,
			GAME::IGameManager& gameManager,
			Size2D screenSize
			)
		{
			if (!_visible)
				return;

			ImGuiWindowFlags windowFlags = 0;
			windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_ShowBorders;
			windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Game Editor", &_visible, windowFlags);

			auto gameName = TLS::strConverter.local().to_bytes(gameManager.getGame().getName());
			_nameBuff.setText(gameName);

			ImGuiInputTextFlags flags = 0;
			flags |= ImGuiInputTextFlags_CallbackCompletion;
			flags |= ImGuiInputTextFlags_CallbackAlways;

			ImGui::InputText("Name", &_nameBuff[0], _nameBuff.getSize(), flags, [](ImGuiTextEditCallbackData* data) {
				std::string name(data->Buf);
				auto& gameManager = *static_cast<NLE::GAME::IGameManager*>(data->UserData);
				gameManager.getGame().setName(TLS::strConverter.local().from_bytes(name));
				return 0;
			}, (void*)&gameManager);

			if (ImGui::CollapsingHeader("Scripts"))
			{
				auto& scriptingContext = gameManager.getGame().getScriptingContext();
				auto scripts = scriptingContext.getScripts();
				std::vector<std::string> scriptNames(scripts.size());
				for (int i = 0; i < scripts.size(); ++i)
				{
					scriptNames[i] = TLS::strConverter.local().to_bytes(scripts[i].first);
				}

				if (ImGui::Button("Add")) {

				}
				ImGui::SameLine();
				if (ImGui::Button("Delete")) {
					std::wstring selectedScriptName = scripts[_selectedScript].first;
					if (selectedScriptName.compare(SCRIPT::ON_INIT) == 0
						|| selectedScriptName.compare(SCRIPT::ON_UPDATE) == 0
						|| selectedScriptName.compare(SCRIPT::ON_EXIT) == 0)
					{
						consoleQueue.push(CONSOLE::WARNING, selectedScriptName + L" is a system script and cannot be deleted.");
					}
					else
					{
						scriptingContext.removeScript(selectedScriptName);
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Edit")) {

				}




				ImGui::ListBox("", &_selectedScript, [](void* vec, int index, const char** out_text) {
					auto& vector = *static_cast<std::vector<std::string>*>(vec);
					if (index < 0 || index >= (int)vector.size())
						return false; 

					*out_text = vector[index].c_str();
					return true;
				}, static_cast<void*>(&scriptNames), (int)scripts.size());
			}

			ImGui::End();
		}
	}
}