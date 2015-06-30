#include "NL_InputProcessor.h"
#include "NL_InputEvents.h"

#include <assert.h>

namespace NLE
{
	namespace INPUT
	{
		InputProcessor::InputProcessor() :
			_initialized(false)
		{

		}

		InputProcessor::~InputProcessor()
		{

		}

		bool InputProcessor::initialize(Core::IEngine& engine)
		{
			assert(!_initialized && _pollEvents);

			_procedure = [&](){
				_pollEvents();

				if (!_events.empty())
				{
					INPUT::Event event;
					while (_events.try_pop(event))
					{
						printf("Processing event...\n");
					}
				}
			};

			_initialized = true;
			return _initialized;
		}

		void InputProcessor::release()
		{

		}

		bool InputProcessor::initialized()
		{
			return _initialized;
		}

		std::function<void()> const& InputProcessor::getExecutionProcedure()
		{
			return _procedure;
		}

		Core::ISystem& InputProcessor::getInterface()
		{
			return *this;
		}

		void InputProcessor::attachPollEvents(std::function<void()> const& operation)
		{
			assert(!_initialized);
			_pollEvents = operation;
		}

		void InputProcessor::processEvent(INPUT::Event& event)
		{
			_events.push(event);
		}
	}
}