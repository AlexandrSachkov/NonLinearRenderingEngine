#include "NL_ImguiEditorUiManager.h"
#include "NL_ThreadLocal.h"
#include "NL_EngineServices.h"
#include "NL_SharedData.h"
#include "NL_SystemServices.h"
#include "NL_InputEvents.h"
#include "NL_ImguiInputMap.h"

#include <assert.h>
#include <string>
#include <iostream>
#include <algorithm>

namespace NLE
{
	namespace UI
	{
		ImguiEditorUiManager::ImguiEditorUiManager(
			EngineServices& eServices,
			CONSOLE::IConsoleQueue& consoleQueue,
			IWindowManager& windowManager,
			GAME::IGameManager& gameManager,
			INPUT::IInputProcessor& inputProcessor,
			GRAPHICS::IRenderingEngine& renderingEngine,
			SCRIPT::IScriptingEngine& scriptingEngine)
			:
			_eServices(eServices),
			_consoleQueue(consoleQueue),
			_windowManager(windowManager),
			_gameManager(gameManager),
			_inputProcessor(inputProcessor),
			_renderingEngine(renderingEngine),
			_scriptingEngine(scriptingEngine),

			_showEditor(true),
			_showEditorSettings(false),

			_windowBgColor(0.0f, 0.0f, 0.0f, 0.392f),
			_textColor(0.0f, 1.0f, 1.0f, 1.0f),
			_borderColor(0.0f, 1.0f, 1.0f, 0.129f),
			_itemColor(0.0f, 0.0f, 0.0f, 0.392f),
			_itemHoverColor(0.0f, 0.675f, 0.820f, 0.263f),
			_itemActiveColor(0.0f, 0.384f, 0.620f, 0.690f),
			_selectionColor(0.290f, 0.290f, 0.290f, 0.690f)
		{
		}

		ImguiEditorUiManager::~ImguiEditorUiManager()
		{
		}

		bool ImguiEditorUiManager::initialize()
		{
			return true;
		}

		int ImguiEditorUiManager::getScancodeForKeyEvent(INPUT::Event event)
		{
			assert(event.eventType == INPUT::EVENT_KEY);
			ImGuiIO& io = ImGui::GetIO();

			auto key = INPUT::NLEtoImguiKey(event.eventData.keyEvent.key);
			if (key == -1)
				return event.eventData.keyEvent.scancode;

			if (io.KeyMap[key] == -1)
				io.KeyMap[key] = event.eventData.keyEvent.scancode;

			return io.KeyMap[key];
		}

		ImDrawData* ImguiEditorUiManager::getDrawData()
		{
			return ImGui::GetDrawData();
		}

		void ImguiEditorUiManager::queueKeyAndCharEvent(INPUT::Event event)
		{
			_keyAndCharEvents.push(event);
		}

		void ImguiEditorUiManager::update(SystemServices* sServices, double deltaT, Size2D screenSize)
		{
			NLE::TLS::PerformanceTimer::reference timer = NLE::TLS::performanceTimer.local();
			timer.deltaT();

			DATA::SharedData& data = _eServices.data->getData();
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2((float)screenSize.width, (float)screenSize.height);
			io.DeltaTime = (float)(deltaT * 0.000000001);

			//Need crossplatform implementation
			// Hide OS mouse cursor if ImGui is drawing it
			//SetCursor(io.MouseDrawCursor ? NULL : LoadCursor(NULL, IDC_ARROW));

			captureInput(sServices, deltaT, screenSize);
			ImGui::NewFrame();
			drawUI(sServices, screenSize);
			ImGui::Render();

			data.sysExecutionTimes.set(UI_MANAGER, timer.deltaT());
		}

		void ImguiEditorUiManager::captureInput(SystemServices* sServices, double deltaT, Size2D screenSize)
		{
			DATA::SharedData& data = _eServices.data->getData();
			ImGuiIO& io = ImGui::GetIO();

			io.MouseDown[0] = data.mouseButtonPressed.get()[INPUT::MOUSE_BUTTON_LEFT];
			io.MouseDown[1] = data.mouseButtonPressed.get()[INPUT::MOUSE_BUTTON_RIGHT];
			io.MouseDown[2] = data.mouseButtonPressed.get()[INPUT::MOUSE_BUTTON_MIDDLE];
			io.MouseWheel += (float)data.scrollOffset.get()[1];
			io.MousePos.x = (float)data.mouseCursorPosition.get()[0];
			io.MousePos.y = (float)data.mouseCursorPosition.get()[1];

			INPUT::Event event;
			while (_keyAndCharEvents.pop(event))
			{
				if (event.eventType == INPUT::EVENT_KEY)
				{
					int scancode = getScancodeForKeyEvent(event);
					io.KeysDown[scancode] = event.eventData.keyEvent.action == INPUT::ACTION_PRESS ? 1 : 0;
				}
				else
				{
					io.AddInputCharacter((unsigned short)event.eventData.charEvent.code);
				}
			}

			io.KeyCtrl = data.keyModsPressed.get()[INPUT::KEY_MOD_CONTROL];
			io.KeyShift = data.keyModsPressed.get()[INPUT::KEY_MOD_SHIFT];
			io.KeyAlt = data.keyModsPressed.get()[INPUT::KEY_MOD_ALT];
			io.KeySuper = data.keyModsPressed.get()[INPUT::KEY_MOD_SUPER];
		}

		void ImguiEditorUiManager::drawUI(SystemServices* sServices, Size2D screenSize)
		{
			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoTitleBar;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoScrollbar;
			window_flags |= ImGuiWindowFlags_NoCollapse;
			window_flags |= ImGuiWindowFlags_MenuBar;
			window_flags |= ImGuiWindowFlags_NoSavedSettings;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

			ImGui::SetNextWindowPos(ImVec2(0,0));
			ImGui::SetNextWindowSize(ImVec2((float)screenSize.width, (float)screenSize.height), ImGuiSetCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			applyColorScheme(true);
			ImGui::Begin("Engine UI Overlay Window", &_showEditor, window_flags);

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("New", NULL, nullptr);
					ImGui::MenuItem("Open", NULL, nullptr);
					ImGui::MenuItem("Save", NULL, nullptr);
					if (ImGui::MenuItem("Exit", NULL))
					{
						_gameManager.quitGame();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("View"))
				{
					ImGui::MenuItem("Editor", NULL, &_showEditorSettings);
					ImGui::MenuItem("Game", NULL, nullptr);
					ImGui::MenuItem("Scene", NULL, nullptr);
					ImGui::MenuItem("Object", NULL, nullptr);
					ImGui::EndMenu();
				}
				ImGui::SameLine(ImGui::GetWindowWidth() - 100);
				ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
				ImGui::EndMenuBar();
			}

			ImGui::End();
			restoreColorScheme();
			ImGui::PopStyleVar();
			
			if(_showEditorSettings)
				showEditorSettings(sServices, screenSize);
			
		}

		void ImguiEditorUiManager::showEditorSettings(SystemServices* sServices, Size2D screenSize)
		{
			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoSavedSettings;
			window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
			window_flags |= ImGuiWindowFlags_ShowBorders;

			ImGui::SetNextWindowPos(ImVec2((float)screenSize.width / 2, (float)screenSize.height / 2), ImGuiSetCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			applyColorScheme(false);
			ImGui::Begin("Editor Settings", &_showEditorSettings, window_flags);

			if (ImGui::CollapsingHeader("Color Scheme"))
			{
				ImGui::ColorEdit4("Window Background", (float*)&_windowBgColor);
				ImGui::ColorEdit4("Text", (float*)&_textColor);
				ImGui::ColorEdit4("Border", (float*)&_borderColor);
				ImGui::ColorEdit4("Item", (float*)&_itemColor);
				ImGui::ColorEdit4("Item Hover", (float*)&_itemHoverColor);
				ImGui::ColorEdit4("Item Active", (float*)&_itemActiveColor);
				ImGui::ColorEdit4("Selection", (float*)&_selectionColor);
			}

			ImGui::End();
			restoreColorScheme();
			ImGui::PopStyleVar();
		}

		void ImguiEditorUiManager::applyColorScheme(bool root)
		{
			if(root)
				ImGui::PushStyleColor(ImGuiCol_WindowBg, ImColor(0.0f, 0.0f, 0.0f, 0.0f));
			else
				ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowBgColor);

			ImGui::PushStyleColor(ImGuiCol_MenuBarBg, _windowBgColor);
			ImGui::PushStyleColor(ImGuiCol_Text, _textColor);
			ImGui::PushStyleColor(ImGuiCol_Border, _borderColor);
			ImGui::PushStyleColor(ImGuiCol_Button, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_Header, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_TitleBg, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_CloseButton, _itemColor);
			ImGui::PushStyleColor(ImGuiCol_CloseButtonHovered, _itemHoverColor);
			ImGui::PushStyleColor(ImGuiCol_CloseButtonActive, _itemActiveColor);
			ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, _selectionColor);
		}

		void ImguiEditorUiManager::restoreColorScheme()
		{
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		void ImguiEditorUiManager::show(bool show)
		{
			_showEditor = show;
		}
	}
}