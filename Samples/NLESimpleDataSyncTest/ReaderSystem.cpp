#include "ReaderSystem.h"
#include "SharedDataId.h"
#include "NLE\NLCore\NL_IEngine.h"

ReaderSystem::ReaderSystem(uint_fast32_t id) :
_id(id)
{

}

ReaderSystem::~ReaderSystem()
{

}

bool ReaderSystem::initialize(NLE::Core::IEngine& iEngine)
{
	_slave = &iEngine.getMSDistributor<double>(MS_CONTAINER).buildSlaveEndpoint(_id);
	_shared = &iEngine.getSDistributor<double>(S_CONTAINER).buildEndpoint(_id);

	return true;
}

void ReaderSystem::release()
{

}

uint_fast32_t ReaderSystem::getID()
{
	return _id;
}

std::function<void()> ReaderSystem::getExecutionProcedure()
{
	NLE::Core::Data::SlaveContainer<double>& slave = *_slave;
	NLE::Core::Data::SContainer<double>& shared = *_shared;

	return [this, &slave, &shared](){
		printf("Reader #%i\n", getID());
		printf("SContainer:\n");
		for (unsigned int i = 0; i < shared.size(); ++i)
		{
			printf("%f\n", shared[i]);
		}
		printf("\n");

		printf("MSContainer:\n");
		for (unsigned int i = 0; i < slave.size(); ++i)
		{
			printf("%f\n", slave[i]);
		}
		printf("\n");
	};
}

NLE::Core::ISystem* ReaderSystem::getInterface()
{
	return nullptr;
}