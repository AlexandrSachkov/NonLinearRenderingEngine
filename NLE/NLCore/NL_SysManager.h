#ifndef NL_SYS_MANAGER_H_
#define NL_SYS_MANAGER_H_

#include <memory>
#include <unordered_map>

namespace NLE 
{
	namespace Core 
	{
		class System;
		class Scheduler;
		class UObject;
		class SysManager 
		{
		public:
			SysManager();
			~SysManager();

			bool initialize(std::unique_ptr<Scheduler> const& scheduler);
			void release();

			uint_fast8_t getNumSystems();

			std::unique_ptr<System> const& getSystemById(uint_fast8_t sysId) const;
			void attachSystem(System* system);
		private:
			std::unordered_map<uint_fast8_t, std::unique_ptr<System>> _systems;
			uint_fast8_t _numSystems;
		};
	}
}

#endif