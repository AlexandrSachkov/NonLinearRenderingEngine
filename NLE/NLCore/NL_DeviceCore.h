#ifndef NL_DEVICE_CORE_H_
#define NL_DEVICE_CORE_H_

#include <memory>
#include <cstdint>
#include "NL_ExecutionDesc.h"

namespace NLE
{
	namespace Core
	{
		class Clock;
		class Scheduler;
		class System;
		class SysManager;
		class StateManager;
		class IEngine;

		class DeviceCore
		{
		public:
			static DeviceCore& instance()
			{
				if (!_deviceCore)
				{
					_deviceCore = new DeviceCore();
				}
				return *_deviceCore;
			};

			~DeviceCore();
			bool initialize();
			void release();

			void attachSystem(uint_fast32_t sysId, ExecutionDesc executionDesc, std::unique_ptr<System> system);

			template <typename T>
			void installMSContainer(uint_fast32_t id, uint_fast32_t initialSize, uint_fast32_t grainSize)
			{
				_stateManager->installMSContainer<T>(id, initialSize, grainSize);
			}

			template <typename T>
			void installSContainer(uint_fast32_t id, uint_fast32_t size, uint_fast32_t grainSize)
			{
				_stateManager->installSContainer<T>(id, size, grainSize);
			}

			void setClockPeriodNs(unsigned long long periodNs);
			void setNumThreads(uint_fast32_t numThreads);
			uint_fast32_t getNumHardwareThreads();
			void run();
			void stop();

		private:
			DeviceCore();
			DeviceCore(DeviceCore const&) = delete;
			void operator=(DeviceCore const&) = delete;

			static DeviceCore* _deviceCore;

			std::unique_ptr<Clock> _clock;
			std::unique_ptr<SysManager> _sysManager;
			std::unique_ptr<Scheduler> _scheduler;
			std::unique_ptr<StateManager> _stateManager;
			std::unique_ptr<IEngine> _iEngine;

			bool _initialized;
		};
	}
}

#endif