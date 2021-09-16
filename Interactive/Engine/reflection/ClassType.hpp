#pragma once

namespace Interactive
{
	typedef unsigned int typeId;

	inline static typeId TypesCount = 0;
	inline static typeId GetNewTypeId() { return TypesCount++; }

	template<typename T>
	struct ClassType
	{
		/// <summary>
		/// String literal representation of this ClassType's name
		/// </summary>
		inline static const char* ClassName = typeid(T).name();
		/// <summary>
		/// How much memory space does this ClassType consumes
		/// </summary>
		inline static constexpr size_t ClassSize = sizeof(T);
		/// <summary>
		/// TypeId of this specific ClassType
		/// </summary>
		inline static const unsigned int TypeId = GetNewTypeId();

		static unsigned int GetTypeId() { return TypeId; }

		static void AssignStaticClass(T staticClass) { StaticClass = staticClass; }
		static T GetStaticClass() { return StaticClass; }

	private:
		inline static T StaticClass;
	};
}