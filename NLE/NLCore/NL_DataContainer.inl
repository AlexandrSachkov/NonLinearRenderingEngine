#ifdef NL_DATA_CONTAINER_H_

#include "NL_DataContainer.h"

namespace NLE
{
	namespace Core
	{
		template<typename T>
		DataContainer<T>::DataContainer(uint_fast8_t sysId, uint_fast8_t initSize) :
			_sysId(sysId),
			_dataPool(),
			_data(_dataPool),
			_updateQueue(),
			_distributor(nullptr)
		{
			_data.reserve(initSize);
		}

		template<typename T>
		DataContainer<T>::~DataContainer()
		{
		}

		template<typename T>
		void DataContainer<T>::remove(uint_fast8_t index)
		{
			uint_fast8_t size = _data.size();
			if (index >= size)
				return;

			uint_fast8_t lastOccupied = size - 1;
			if (index != lastOccupied)
			{
				_data[index] = _data[lastOccupied];
			}
			_data.pop_back();
		}

		template<typename T>
		void DataContainer<T>::applyUpdates()
		{
			DataPacket<T> packet;
			while (_updateQueue.try_pop(packet))
			{
				update(packet.getItemNumber(), packet.getData());
			}
		}

		template<typename T>
		inline void DataContainer<T>::bindDistributor(DataDistributor<T>* distributor)
		{
			_distributor = distributor;
		}

		template<typename T>
		inline void add(T data)
		{
			_data.push_back(data);
		}

		template<typename T>
		void DataContainer<T>::update(uint_fast8_t index, T data)
		{
			_data[index] = data;
			if (_distributor)
			{
				_distributor->queue(new DataPacket<T>(_sysId, index, data));
			}
		}

		template<typename T>
		inline T& DataContainer<T>::get(uint_fast8_t index)
		{
			return _data[index];
		}

		template<typename T>
		inline uint_fast8_t DataContainer<T>::size()
		{
			return _data.size();
		}

		template<typename T>
		inline void DataContainer<T>::queuePacket(DataPacket<T> packet)
		{
			_updateQueue.push(packet);
		}
	}
}

#endif