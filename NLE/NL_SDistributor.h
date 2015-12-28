#ifndef NL_S_DISTRIBUTOR_H_
#define NL_S_DISTRIBUTOR_H_

#include "NL_Distributor.h"
#include "NL_SContainer.h"

#include <cstdint>
#include <unordered_map>
#include <memory>
#include "tbb\scalable_allocator.h"

namespace NLE
{
	namespace Core
	{
		namespace Data
		{
			template<typename T>
			class SDistributor : public Distributor
			{
			public:
				SDistributor(uint_fast32_t dataSize, uint_fast32_t queueSize, uint_fast32_t grainSize);
				~SDistributor();

				SContainer<T>& buildEndpoint(uint_fast32_t sysId);
				void distributeFrom(uint_fast32_t sysId);
				void distributeTo(uint_fast32_t sysId);
				std::vector<uint_fast32_t>& getEndpoints();

			private:
				uint_fast32_t _queueSize;
				uint_fast32_t _grainSize;
				uint_fast32_t _updateCycle;

				std::vector<T, tbb::scalable_allocator<T>> _data;
				std::unordered_map<uint_fast32_t, SContainer<T>*> _containers;
				std::vector<uint_fast32_t> _endpoints;
			};
		}
	}
}

#include "NL_SDistributor.inl"

#endif