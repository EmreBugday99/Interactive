// Developed and maintained by Emre Bugday
#pragma once
#include "Vector.hpp"

// Interactive Template Library
namespace ITL
{
	template<typename T>
	class SortedVector
	{
	private:
		Vector<T> m_sortedVector;

	public:
		SortedVector(bool allowSameElements = false) {}

		template<typename TValue>
		void Add(TValue value)
		{
			bool alreadyExists;
			unsigned int index = BinarySearchIndex(value, alreadyExists);
			m_sortedVector.Insert(index, value);
		}

		template<typename TValue>
		unsigned int BinarySearchIndex(TValue value, bool& alreadyExists)
		{
			unsigned int low = 0;
			unsigned int high = m_sortedVector.Elements();
			alreadyExists = true;

			while (low < high)
			{
				unsigned int mid = (low + high) / 2;

				if (value == m_sortedVector[mid])
					return mid;

				if (value < m_sortedVector[mid])
					high = mid;
				else
					low = mid + 1;
			}
			alreadyExists = false;
			return low;
		}

		void Print()
		{
			m_sortedVector.Print();
		}
	};
}