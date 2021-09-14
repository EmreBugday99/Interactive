// Developed and maintained by Emre Bugday
#pragma once

#include <iostream>

// Interactive Template Library
namespace ITL
{
	template<typename T>
	class Vector
	{
	private:
		T* m_vector;
		/// <summary>
		/// Capacity of the vector
		/// </summary>
		unsigned int capacity;
		/// <summary>
		/// Amount of initialized elements in the vector
		/// </summary>
		unsigned int elementCount;
		/// <summary>
		/// Type size of the element
		/// </summary>
		unsigned int elementSize;

	public:
		/// <summary>
		/// How large should the vector expand it's capacity each time it requires expansion.
		/// </summary>
		unsigned int expansionSize;

	public:
		Vector(const unsigned int initialSize = 0)
			: m_vector(nullptr), capacity(0), elementCount(0), elementSize(0), expansionSize(5)
		{
			elementSize = sizeof(T);

			m_vector = new T[initialSize];
			capacity = initialSize;
		}
		~Vector() { delete[] m_vector; }

		/// <summary>
		/// Get the element in the specified index
		/// </summary>
		T& operator[] (const unsigned int index) { return m_vector[index]; }
		/// <summary>
		/// Return the first element
		/// </summary>
		T& First() const { return m_vector[0]; }
		/// <summary>
		/// Return the last element
		/// </summary>
		T& Last() const { return m_vector[elementCount - 1]; }

		/// <summary>
		/// Returns the amount of initialized elements in the vector
		/// </summary>
		unsigned int Elements() const { return elementCount; }

		/// <summary>
		/// Returns the capacity of the vector
		/// </summary>
		unsigned int Capacity() const { return capacity; }

		// TODO: REMOVE THIS LATER ON. THIS IS FOR DEBUGGING.
		void Print()
		{
			for (unsigned int i = 0; i < capacity; ++i)
			{
				std::cout << "[" << i << "] : " << m_vector[i] << std::endl;
			}
		}

		/// <summary>
		/// Increases the capacity of the vector with the specified amount.
		/// </summary>
		/// <param name="sizeToExpand">Expansion size</param>
		void IncreaseCapacity(const unsigned int sizeToExpand)
		{
			// Creating a new vector with the increased capacity.
			T* newVector = new T[capacity + sizeToExpand];

			// Copying the old vector into the new vector
			for (unsigned int i = 0; i < capacity; ++i)
			{
				newVector[i] = m_vector[i];
			}

			delete[] m_vector;
			m_vector = newVector;
			capacity = capacity + sizeToExpand;
		}

		/// <summary>
		/// Adds to the end of the vector.
		/// Expands the vector if out of space.
		/// </summary>
		template<typename TValue>
		void Add(TValue&& value)
		{
			if (elementCount == capacity)
				IncreaseCapacity(expansionSize);

			m_vector[elementCount] = value;
			elementCount++;
		}
		
		/// <summary>
		/// Inserts and element into the specified index and shifts the vector accordingly.
		/// Expands the vector if out of space.
		/// </summary>
		template<typename TValue>
		void Insert(const unsigned int index, TValue value)
		{
			if ((elementCount + 1) > capacity)
				IncreaseCapacity(expansionSize);

			for (unsigned int i = (elementCount); i > index; --i)
			{
				m_vector[i] = m_vector[i - 1];
			}

			m_vector[index] = value;
			elementCount++;
		}

		/// <summary>
		/// Removes the element specified in the index and shifts the vector accordingly.
		/// </summary>
		void Remove(const unsigned int index)
		{
			// We do not need to assign anything to the old indexes.
			// It's simply considered as garbage data at this point.

			if (index == elementCount)
			{
				elementCount--;
				return;
			}

			for (unsigned int i = index; i < elementCount; ++i)
			{
				m_vector[i] = m_vector[i + 1];
			}

			elementCount--;
		}
	};
}