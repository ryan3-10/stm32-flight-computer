#ifndef UTILS_MEMORY_POOL_H_
#define UTILS_MEMORY_POOL_H_

#include "i_allocator.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <stdint.h>

template <typename T, std::size_t poolSize>
class MemoryPool : public IAllocator<T> {
public:
	T* allocate(size_t n) override {
#ifdef DEBUG
		assert(m_index + n <= poolSize);
#endif
		auto returnVal = &m_pool[m_index];
		m_index += n;
		return returnVal;
	}

	T* allocate(std::initializer_list<T> initList) override {
#ifdef DEBUG
		assert(m_index + initList.size() <= poolSize);
#endif

		auto returnVal = &m_pool[m_index];
		std::copy(initList.begin(), initList.end(), returnVal);
		m_index += initList.size();
		return returnVal;
	}

private:
	std::array<T, poolSize> m_pool{};
	size_t m_index = 0;
};

#endif /* UTILS_MEMORY_POOL_H_ */
