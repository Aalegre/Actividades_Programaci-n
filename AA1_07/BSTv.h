#pragma once
#include <vector>
#include <iostream>

template <typename T>
class BSTv {
	std::vector<T> data;

public:
	BSTv();
	~BSTv();


	T* Search(T value_);
	const bool Exist(T value_);
	void Insert(T value_);
};

template<typename T>
inline BSTv<T>::BSTv()
{

}

template<typename T>
inline BSTv<T>::~BSTv()
{
}

template<typename T>
inline T* BSTv<T>::Search(T value_)
{
	return NULL;
}

template<typename T>
inline const bool BSTv<T>::Exist(T value_)
{
	return false;
}

template<typename T>
inline void BSTv<T>::Insert(T value_)
{

}
