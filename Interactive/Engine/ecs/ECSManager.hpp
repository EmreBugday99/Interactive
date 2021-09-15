#pragma once
#include <map>
#include <vector>
#include "../reflection/ClassType.hpp"

class BaseSystem;

namespace Interactive
{
	namespace ECS
	{
		class ECSManager
		{
			typedef unsigned int entity;
			typedef unsigned int component;

		public:
			template<typename T>
			static unsigned int CreateComponent(std::vector<unsigned char>& memory, Reflection::ClassType<T>& classType)
			{
				const unsigned int index = memory.size();
				memory.resize(index + classType.ClassSize);
				T* newClass = new(&memory[index]) T(*classType.GetStaticClass());

				return index;
			}

			template<typename T>
			static void DeleteComponent() {}

		private:
			std::vector<std::tuple<entity, std::vector<component>>> Entities;
			std::vector<BaseSystem*> Systems;
		};
	}
}