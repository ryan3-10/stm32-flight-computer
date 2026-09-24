#ifndef INTERFACES_I_ALLOCATOR_H_
#define INTERFACES_I_ALLOCATOR_H_

#include <initializer_list>

template <typename T>
class IAllocator {
	T* allocate(std::size_t n) = 0;
	T* allocate(std::initializer_list<T> initList) = 0;
};


#endif /* INTERFACES_I_ALLOCATOR_H_ */
