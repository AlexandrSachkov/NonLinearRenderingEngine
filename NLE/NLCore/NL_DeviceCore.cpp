#include "NL_DeviceCore.h"

#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_StateManager.h"

#include <cassert>

namespace NLE 
{
	namespace Core 
	{
		DeviceCore *DeviceCore::_deviceCore = nullptr;

		DeviceCore::DeviceCore()
		{ 
			_clock = std::make_unique<Clock>();
			_sysManager = std::make_unique<SysManager>();
			_scheduler = std::make_unique<Scheduler>();
		}

		DeviceCore::~DeviceCore()
		{
			release();
		}

		bool DeviceCore::initialize()
		{
			if (!_clock->initialize())
				return false;
			if (!_scheduler->initialize())
				return false;
			if (!_sysManager->initialize(_scheduler))
				return false;
			assert(_stateManager);
			if (!_stateManager->initialize())
				return false;
			
			return true;
		}

		void DeviceCore::release()
		{	
			if (_stateManager)
				_stateManager->release();
			if (_sysManager)
				_sysManager->release();
			if (_scheduler)
				_scheduler->release();
			if (_clock)
				_clock->release();
		}

		void DeviceCore::attachSystem(std::unique_ptr<System> system)
		{
			_sysManager->attachSystem(std::move(system));
		}

		void DeviceCore::attachStateManager(std::unique_ptr<StateManager> stateManager)
		{
			_stateManager = std::move(stateManager);
		}

		void DeviceCore::drive()
		{
			std::unique_ptr<Scheduler>& scheduler = _scheduler;
			std::unique_ptr<SysManager>& sysMngr = _sysManager;
			std::unique_ptr<StateManager>& stateMngr = _stateManager;

			_clock->onTick([&scheduler, &sysMngr, &stateMngr](){
				stateMngr->distributeData();
				scheduler->executeSystems(sysMngr);
			});
		}
	}
}