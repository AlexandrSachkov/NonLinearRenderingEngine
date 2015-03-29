#include "NL_DeviceCore.h"

#include "NL_Clock.h"
#include "NL_System.h"
#include "NL_SysManager.h"
#include "NL_Scheduler.h"
#include "NL_StateManager.h"

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
			_stateManager = std::make_unique<StateManager>();
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
			if (!_stateManager->initialize(_sysManager->getNumSystems()))
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

		void DeviceCore::attachSystem(System* system)
		{
			_sysManager->attachSystem(system);
		}

		void DeviceCore::drive()
		{
			std::unique_ptr<Scheduler>& scheduler = _scheduler;
			std::unique_ptr<SysManager>& sysMngr = _sysManager;
			std::unique_ptr<StateManager>& stateMngr = _stateManager;

			_clock->onTick([&scheduler, &sysMngr, &stateMngr](){
				scheduler->executeSystems(sysMngr, stateMngr);
			});
		}
	}
}