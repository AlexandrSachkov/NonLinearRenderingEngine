#ifndef NL_UI_MANAGER_H_
#define NL_UI_MANAGER_H_

#include "NL_IUiManager.h"
#include "NLCore\NL_System.h"
#include "NL_IConsolePump.h"

#include "tbb\concurrent_queue.h"

namespace NLE
{
	namespace Core
	{
		class IEngine;
		class ISystem;
	}

	namespace UI
	{
		class UiManager : public Core::System, public IUiManager
		{
		public:
			UiManager();
			~UiManager();

			bool initialize(Core::IEngine& engine);
			void release();

			bool initialized();

			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			void bindScriptCallback(const char* name, int(*)(lua_State* state), bool async);
			void executeScript(const char* script, bool async);

		private:
			bool _initialized;
			std::function<void()> _procedure;
			void(*_printConsole)(CONSOLE::OUTPUT_TYPE, const char*);

			tbb::concurrent_queue<std::string> _scripts;
			tbb::concurrent_queue<std::pair<std::string, int(*)(lua_State* state)>> _callbacks;
		};
	}
}

#endif