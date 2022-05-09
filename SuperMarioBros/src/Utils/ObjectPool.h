#pragma once

#include <unordered_map>

template <class T>
class ObjectPool
{
public:
	ObjectPool(int32_t poolSize);
	~ObjectPool();

	[[nodiscard]] T* const Get();
	void Return(const T* returnObject);

private:
	// First is the pooled object and Second is if the object was 
	std::unordered_map<T*, bool> pool;
};

template<class T>
inline ObjectPool<T>::ObjectPool(int32_t poolSize)
{
	pool.reserve(poolSize);

	for (int32_t i = 0; i < poolSize; i++)
	{
		pool.insert(std::pair<T*, bool>(new T(), false));
	}
}

template<class T>
inline ObjectPool<T>::~ObjectPool()
{
	for (auto& object : pool)
	{
		delete object.first;
	}
}

template<class T>
inline T* const ObjectPool<T>::Get()
{
	for (auto& object : pool)
	{
		if (!object.second)
		{
			object.second = true;
			return object.first;
		}
	}

	// Found no object to give, returning nullptr
	return nullptr;
}

template<class T>
inline void ObjectPool<T>::Return(const T* returnObject)
{
	for (auto& object : pool)
	{
		if (object.first == returnObject)
		{
			object.second = false;
		}
	}
}
