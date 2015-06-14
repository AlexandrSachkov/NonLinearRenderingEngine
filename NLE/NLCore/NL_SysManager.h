#ifndef NL_SYS_MANAGER_H_
#define NL_SYS_MANAGER_H_

#include <memory>
#include <unordered_map>
#include "NL_ExecutionDesc.h"

namespace NLE 
{
	namespace Core 
	{
		class System;
		class Scheduler;
		class UObject;
		class StateManager;
		class SysRuntimeControl;

		class SysManager 
		{
		public:
			SysManager();
			~SysManager();

			bool initialize(
				std::unique_ptr<Scheduler> const& scheduler,
				std::unique_ptr<StateManager> const& stateManager,
				std::unique_ptr<SysRuntimeControl> const& sysRuntimeControl);
			void release();

			uint_fast8_t getNumSystems();
			ExecutionDesc& getExecutionDesc(uint_fast8_t sysId);

			std::unique_ptr<System> const& getSystem(uint_fast8_t sysId) const;
			void attachSystem(ExecutionDesc execDesc, std::unique_ptr<System> system);
		private:
			std::unordered_map<uint_fast8_t, std::unique_ptr<System>> _systems;
			std::unordered_map<uint_fast8_t, ExecutionDesc> _executionDesc;
			uint_fast8_t _numSystems;
		};
	}
}

#endif