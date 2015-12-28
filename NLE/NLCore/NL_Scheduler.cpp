#include "NL_Scheduler.h"
#include "NL_SysManager.h"
#include "tbb/tbb.h"
#include "NL_System.h"
#include "NL_AsyncTask.h"
#include "NL_SyncTask.h"
#include "NL_StateManager.h"

#include <assert.h>

namespace NLE
{
	namespace Core
	{
		Scheduler::Scheduler() :
			_scheduledSystems(10),
			_initialized(false)
		{
			_numThreads = tbb::task_scheduler_init::default_num_threads();
			_numRunningTasks.fetch_and_store(0);
		}

		Scheduler::~Scheduler()
		{

		}

		bool Scheduler::initialize(uint_fast32_t numSysThreads)
		{
			assert(!_initialized);
			_numThreads -= numSysThreads + 1;
			_taskSchedulerInit = new tbb::task_scheduler_init(_numThreads);
			_initialized = true;	
			return true;
		}

		void Scheduler::release()
		{
			if (_taskSchedulerInit)
				delete _taskSchedulerInit;
			_initialized = false;
		}

		void Scheduler::setNumThreads(uint_fast32_t numThreads)
		{
			assert(!_initialized && numThreads > 0);
			_numThreads = numThreads;
		}

		uint_fast32_t Scheduler::getNumThreads()
		{
			return _numThreads;
		}

		int_fast32_t Scheduler::getNumRunningTasks()
		{
			return _numRunningTasks.load();
		}

		void Scheduler::signalFinished(uint_fast32_t sysId)
		{
			_finished.push(sysId);
			_numRunningTasks.fetch_and_decrement();
		}

		void Scheduler::startSystem(
			ExecutionDesc& execDesc,
			uint_fast32_t sysId)
		{
			if (execDesc.getExecution() != Execution::NONE)
			{
				execDesc.enable(true);
				_starting.push(sysId);
			}			
		}

		void Scheduler::stopSystem(
			ExecutionDesc& execDesc,
			uint_fast32_t sysId)
		{
			execDesc.enable(false);
		}

		void Scheduler::manageExecution(
			std::unique_ptr<SysManager> const& sysManager,
			std::unique_ptr<StateManager> const& stateManager)
		{
			stateManager->processRequests();

			uint_fast32_t sysId;
			ExecutionDesc* execDesc;

			if (!_finished.empty())
			{
				while (_finished.try_pop(sysId))
				{
					stateManager->distributeFrom(sysId);
					execDesc = &sysManager->getExecutionDesc(sysId);
					if (execDesc->getMethod() == Method::THREAD)
					{
						if (execDesc->enabled())
						{
							stateManager->distributeTo(sysId);
							auto& sysThread = sysManager->getSystemThread(sysId);
							sysThread->resume();
							_numRunningTasks.fetch_and_increment();
						}
						else
						{
							sysManager->getSystemThread(sysId)->stop();
						}
					}
					else
					{
						if (execDesc->enabled() && execDesc->getExecution() == Execution::RECURRING)
						{
							_scheduledSystems.add(sysId);
						}
					}
				}
			}

			if (!_starting.empty())
			{
				while (_starting.try_pop(sysId))
				{
					execDesc = &sysManager->getExecutionDesc(sysId);
					if (execDesc->getMethod() == Method::THREAD)
					{
						stateManager->distributeTo(sysId);
						auto& sysThread = sysManager->getSystemThread(sysId);
						sysThread->setProcedure(this, sysManager->getSystem(sysId)->getExecutionProcedure());
						sysThread->start();
						_numRunningTasks.fetch_and_increment();
					}
					else
					{
						_scheduledSystems.add(sysId);
					}				
				}
			}
	
			for (uint_fast32_t i = 0; i < _scheduledSystems.size(); ++i)
			{
				sysId = _scheduledSystems[i];
				execDesc = &sysManager->getExecutionDesc(sysId);

				if (execDesc->isTimeToStart())
				{
					stateManager->distributeTo(sysId);
					_numRunningTasks.fetch_and_increment();

					if (execDesc->getMode() == Mode::ASYNC)
					{
						execDesc->resetStartTime();
						
						std::function<void()> const& procedure = sysManager->getSystem(sysId)->getExecutionProcedure();
						AsyncTask* task = new (tbb::task::allocate_root())NLE::Core::AsyncTask(*this, sysId, procedure);
						switch (execDesc->getPriority())
						{
						case Priority::LOW:
							tbb::task::enqueue(*task, tbb::priority_low);
							break;
						case Priority::STANDARD:
							tbb::task::enqueue(*task, tbb::priority_normal);
							break;
						case Priority::HIGH:
							tbb::task::enqueue(*task, tbb::priority_high);
							break;
						default:
							//should never be reached
							assert(false);
						}
						
					} else {
						_syncSystemsToRun.push_back(sysId);
					}
				
					_scheduledSystems.itRemove(i);
				}
			}

			if (_syncSystemsToRun.size() > 0)
			{
				for (uint_fast32_t sysId : _syncSystemsToRun)
				{
					execDesc = &sysManager->getExecutionDesc(sysId);
					execDesc->resetStartTime();

					std::function<void()> const& procedure = sysManager->getSystem(sysId)->getExecutionProcedure();
					SyncTask task(*this, sysId, procedure);
					task.execute();
				}
				_syncSystemsToRun.clear();
			}
		}
	}
}