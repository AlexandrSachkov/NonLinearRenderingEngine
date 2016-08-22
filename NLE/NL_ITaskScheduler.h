#ifndef NL_I_TASK_SCHEDULER_H_
#define NL_I_TASK_SCHEDULER_H_

#include "tbb/task.h"
#include <functional>

namespace NLE
{
	namespace TASK
	{
		enum TaskPriority
		{
			STANDARD = tbb::priority_normal,
			HIGH = tbb::priority_high,
			LOW = tbb::priority_low
		};

		class ITaskScheduler_EService
		{
		public:
			virtual void queueProcedure(std::function<void()> procedure, TaskPriority priority) = 0;
			virtual unsigned int getNumThreads() = 0;
		};

		class ITaskScheduler : public ITaskScheduler_EService
		{
		public:
			virtual void dispatchTasks() = 0;
			virtual void notifyOfCompletion() = 0;
			virtual void waitOnTasks() = 0;
		};
	}
}

#endif