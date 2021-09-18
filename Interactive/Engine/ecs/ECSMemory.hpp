#pragma once
#include <iostream>
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
	typedef void (*EntityIdChangeUpdate) (const Entity2*, const unsigned int);

	//TODO: FIND A SEXIER NAME
	inline static std::vector<RemovalOperationEvent> removalObservers;
	inline static std::vector<EntityIdChangeUpdate> entityUpdateObservers;

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
			if (std::is_base_of_v<Component, T>)
			{
				Type = ECS_TYPE_COMPONENT;

				removalObservers.push_back(BeforeDataRemoveObserver);
				entityUpdateObservers.push_back(UpdateComponentAfterEntityUpdate);
			}
			else if (std::is_base_of_v<Entity2, T>)
			{
				Type = ECS_TYPE_ENTITY;
			}
			else
			{
				Type = ECS_TYPE_OTHER;
			}

			std::cout << "Memory Type: " << Type << std::endl;
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
			InformObservers(dataToBeRemoved);

			//					***Beginning Index***							***Ending Index***
			Memory.erase(Memory.begin() + (index * sizeof(T)), Memory.begin() + (index * sizeof(T)));
		}

		static void InformObservers(void* data)
		{
			if (removalObservers.empty() == false && !MemoryAlias.empty())
			{
				for (const RemovalOperationEvent observer : removalObservers)
				{
					observer(MemoryAlias, data);
				}
			}
		}

		static void BeforeDataRemoveObserver(const std::string& memoryAlias, void* data)
		{
			UpdateComponentBeforeEntityRemoval(memoryAlias, data);
			UpdateEntitiesOnRemoval(memoryAlias, data);
		}

		static void UpdateEntitiesOnRemoval(const std::string& memoryAlias, void* removedData)
		{
			// We make sure this method block only runs in Entity Virtual Memory
			if (memoryAlias == "Entity" && Type == ECS_TYPE_ENTITY)
			{
				const Entity2* removingEntity = (Entity2*)removedData;

				unsigned int newEntityId = 0;
				for (unsigned int i = 0; i < GetSliceCount(); i++)
				{
					Entity2* iteratedEntity = (Entity2*)FetchWithSliceIndex(i);

					if (iteratedEntity != removingEntity)
					{
						const unsigned int oldEntityId = iteratedEntity->EntityId;
						iteratedEntity->EntityId = newEntityId;
						newEntityId = (newEntityId + 1) * sizeof(T);

						for (const EntityIdChangeUpdate observer : entityUpdateObservers)
						{
							observer(iteratedEntity, oldEntityId);
						}
					}
				}
			}
		}

		static void UpdateComponentBeforeEntityRemoval(const std::string& memoryAlias, void* removedData)
		{
			std::cout << "I don't know what am I doing." << std::endl;

			if (memoryAlias == "Entity" && Type == ECS_TYPE_COMPONENT)
			{
				Entity2* entity = (Entity2*)removedData;

				unsigned int reverseIndex = 0;
				for (unsigned int componentIndex = GetSliceCount() - 1; componentIndex > 0; --componentIndex)
				{
					Component* component = (Component*)FetchWithSliceIndex(componentIndex);

					if (component->OwnerId == entity->EntityId)
						RemoveSlice(componentIndex);
					else
						component->ComponentId = reverseIndex++;
				}
			}
		}

		static void UpdateComponentAfterEntityUpdate(const Entity2* updatedEntity, const unsigned int oldEntityId)
		{
			for (unsigned int i = 0; i < GetSliceCount(); i++)
			{
				Component* component = (Component*)FetchWithSliceIndex(i);
				if (component->OwnerId == oldEntityId)
					component->OwnerId = updatedEntity->EntityId;
			}
		}
	};
}