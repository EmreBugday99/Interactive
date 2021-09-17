#pragma once
#include <string>
#include <vector>
#include "Component.hpp"
#include "../reflection/ClassType.hpp"
#include "ECSMacros.hpp"
#include "Entity.hpp"

namespace Interactive
{
	//TODO: FIND A SEXIER NAME
	typedef void (*RemovalOperationEvent) (const std::string&, void*);

	//TODO: FIND A SEXIER NAME
	inline static std::vector<RemovalOperationEvent> RemovalObservers;

	template<typename T>
	class ECSMemory
	{
		typedef void (*newMemoryFunc) ();
		typedef unsigned char byte;
		typedef unsigned int memoryIndex;
		typedef unsigned int sliceIndex;

		// A memory alias is a nickname you can give for specific sandbox memories.
		inline static std::string MemoryAlias;
		inline static unsigned int Type;

		inline static std::vector<byte> Memory;
		inline static std::vector<memoryIndex> AvailableMemorySlices;

	public:
		inline static newMemoryFunc NewMemoryFunction;

		static void InitializeMemory()
		{
			if (std::is_base_of_v<T, Component>)
			{
				RemovalObservers.push_back(OnDataRemoved);
				Type = ECS_TYPE_COMPONENT;
			}
			else if (std::is_base_of_v<T, Entity2>)
			{
				Type = ECS_TYPE_ENTITY;
			}
			else
			{
				Type = ECS_TYPE_OTHER;
			}
		}

		static void SetAlias(const std::string typeName) { MemoryAlias = typeName; }

		/// <summary>
		/// Allocates new memory size of T and insert a new T into the allocated memory block.
		/// </summary>
		/// <returns>Starting index of the new T inside the memory buffer</returns>
		static memoryIndex Add()
		{
			const unsigned int index = Memory.size();
			Memory.resize(index + ClassType<T>::ClassSize);
			T* newClass = new(&Memory[index]) T;

			if (NewMemoryFunction != nullptr)
				NewMemoryFunction();

			return index;
		}

		/// <summary>
		/// Fetches data from the specified memory index
		/// </summary>
		/// <param name="index">From which index T* would be fetched?</param>
		/// <returns>T* which starts on the specified index</returns>
		static T* FetchWithMemoryIndex(const memoryIndex index)
		{
			return (T*)&Memory[index];
		}

		/// <summary>
		/// Tries Fetch data with the data's slice index in memory.
		/// </summary>
		/// <param name="index">From which slice index T* would be fetched?</param>
		/// <returns>T* which starts on the specified slice</returns>
		static T* FetchWithSliceIndex(memoryIndex index)
		{
			return (T*)&Memory[index * sizeof(T)];
		}

		/// <summary>
		/// Get how many bytes are allocated in this memory
		/// </summary>
		/// <returns>Total size of this memory</returns>
		static memoryIndex GetMemorySize() { return Memory.size(); }

		static memoryIndex GetSliceCount() { return Memory.size() / sizeof(T); }

		static void Remove(const memoryIndex index)
		{
			void* dataToBeRemoved = FetchWithMemoryIndex(index);
			InformObservers(dataToBeRemoved);

			Memory.erase(Memory.begin() + index, Memory.begin() + (index + sizeof(T)));
		}

		static void RemoveSlice(const sliceIndex index)
		{
			void* dataToBeRemoved = FetchWithMemoryIndex(index);

			if (RemovalObservers.empty() == false && !MemoryAlias.empty)
			{
				for (const RemovalOperationEvent observer : RemovalObservers)
				{
					observer(MemoryAlias, dataToBeRemoved);
				}
			}
			//					***Beginning Index***							***Ending Index***
			Memory.erase(Memory.begin() + (index * sizeof(T)), Memory.begin() + (index * sizeof(T)));
		}

		static void MarkSliceAvailable(const memoryIndex index)
		{
			AvailableMemorySlices.emplace_back(index);
		}

		static void InformObservers(void* data)
		{
			if (RemovalObservers.empty() == false && !MemoryAlias.empty)
			{
				for (const RemovalOperationEvent observer : RemovalObservers)
				{
					observer(MemoryAlias, data);
				}
			}
		}

		static void OnDataRemoved(const std::string& memoryAlias, void* data)
		{
			if (memoryAlias == "Entity" && Type == ECS_TYPE_ENTITY)
			{
			}

			if (memoryAlias == "Entity" && Type == ECS_TYPE_COMPONENT)
			{
				Entity2* entity = (Entity2*)data;

				unsigned int reverseIndex = 0;
				for (unsigned int componentIndex = GetSliceCount(); componentIndex > 0; --componentIndex)
				{
					Component* component = FetchWithSliceIndex(componentIndex);

					if (component->OwnerId == entity->EntityId)
						RemoveSlice(componentIndex);
					else
						component->ComponentId = reverseIndex++;
				}
			}
		}
	};
}