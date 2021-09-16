#pragma once
#include <vector>
#include "../includes/EngineInclude.hpp"

namespace Interactive
{
	template<typename T>
	class ECSMemory
	{
		typedef void (*newMemoryFunc) ();
		typedef unsigned char byte;
		typedef unsigned int memoryIndex;

		inline static std::vector<byte> Memory;
		inline static std::vector<memoryIndex> AvailableMemorySlices;

	public:
		inline static newMemoryFunc NewMemoryFunction;

		/// <summary>
		/// Allocates new memory size of T and insert a new T into the allocated memory block.
		/// </summary>
		/// <returns>Starting index of the new T inside the memory buffer</returns>
		inline static memoryIndex Add()
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
		inline static T* FetchWithMemoryIndex(const memoryIndex index)
		{
			return (T*)&Memory[index];
		}

		/// <summary>
		/// Tries Fetch data with the data's slice index in memory.
		/// </summary>
		/// <param name="index">From which slice index T* would be fetched?</param>
		/// <returns>T* which starts on the specified slice</returns>
		inline static T* FetchWithSliceIndex(memoryIndex index)
		{
			return (T*)&Memory[index * sizeof(T)];
		}

		/// <summary>
		/// Get how many bytes are allocated in this memory
		/// </summary>
		/// <returns>Total size of this memory</returns>
		inline static memoryIndex GetMemorySize() { return Memory.size(); }

		inline static memoryIndex GetSliceCount() { return Memory.size() / sizeof(T); }

		inline static void Remove(const memoryIndex index)
		{
			Memory.erase(Memory.begin() + index, Memory.begin() + (index + sizeof(T)));
		}

		inline static void MarkSliceAvailable(const memoryIndex index)
		{
			AvailableMemorySlices.emplace_back(index);
		}
	};
}