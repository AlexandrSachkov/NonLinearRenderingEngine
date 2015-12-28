#ifndef NL_SCHEDULER_H_
#define NL_SCHEDULER_H_

#include "NL_ExecutionDesc.h"
#include "NL_PContainer.h"
#include "tbb\concurrent_queue.h"
#include "tbb/task_scheduler_init.h"
#include "tbb\scalable_allocator.h"
#include "tbb/atomic.h"


namespace NLE 
{
	namespace Core 
	{
		class SysManager;
		class StateManager;
		class SysTask;
		class Clock;

		class Scheduler 
		{
		public:
			Scheduler();
			~Scheduler();

			bool initialize(uint_fast32_t numSysThreads);
			void release();

			void setNumThreads(uint_fast32_t numThreads);
			uint_fast32_t getNumThreads();
			void startSystem(
				ExecutionDesc& execDesc,
				uint_fast32_t sysId);
			void stopSystem(
				ExecutionDesc& execDesc,
				uint_fast32_t sysId);
			void signalFinished(uint_fast32_t sysId);
			void manageExecution(
				std::unique_ptr<SysManager> const& sysManager,
				std::unique_ptr<StateManager> const& stateManager);
			int_fast32_t getNumRunningTasks();

		private:
			tbb::task_scheduler_init* _taskSchedulerInit;		
			tbb::concurrent_queue<uint_fast32_t> _starting;
			tbb::concurrent_queue<uint_fast32_t> _finished;
		
			Data::PContainer<uint_fast32_t> _scheduledSystems;
			std::vector<uint_fast32_t, tbb::scalable_allocator<uint_fast32_t>> _syncSystemsToRun;
			uint_fast32_t _numThreads;
			bool _initialized;
			tbb::atomic<int_fast32_t> _numRunningTasks;
		};
	}
}

#endif