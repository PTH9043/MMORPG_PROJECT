#pragma once

namespace Core
{
	template<class Type>
	using VECTOR = std::vector<Type, USTLAllocator<Type>>;

	template<typename Type>
	using Deque = std::deque <Type, USTLAllocator<Type>>;

	template<class Type>
	using QUEUE = std::queue<Type, Deque<Type>>;

	template<class Type>
	using VECTOR = std::vector<Type, USTLAllocator<Type>>;

	template<class Type>
	using LIST = std::list<Type, USTLAllocator<Type>>;

	template<class Type, class Other, class Less = std::less<Type>>
	using MAP = std::map<Type, Other, Less, USTLAllocator<std::pair<const Type, Other>>>;

	template<class Type, class Other, class HASH = std::hash<Type>, class KEYEQ = std::equal_to<Type>>
	using UNORMAP = std::unordered_map<Type, Other, HASH, KEYEQ, USTLAllocator<std::pair<const Type, Other>>>;

	template<class Type, class HASH = std::hash<Type>, class KEYEQ = std::equal_to<Type>>
	using UNORSET = std::unordered_set<Type, HASH, KEYEQ, USTLAllocator<Type>>;

	template<class Type, class Pred = std::less<Type>>
	using SET = std::set<Type, Pred, USTLAllocator<Type>>;

	using BUFFER = VECTOR<byte>;
}