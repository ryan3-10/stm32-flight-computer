#ifndef UTILS_MEMORY_POOL_H_
#define UTILS_MEMORY_POOL_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <stdint.h>

constexpr uint8_t POOL_SIZE = 32;

template <typename T>
class MemoryPool {
public:
	T* allocate(size_t n) {
#ifdef DEBUG
		assert(m_index + n <= POOL_SIZE);
#endif
		auto returnVal = &m_pool[m_index];
		m_index += n;
		return returnVal;
	}

	T* allocate(std::initializer_list<T> initList) {
#ifdef DEBUG
		assert(m_index + initList.size() <= POOL_SIZE);
#endif

		auto returnVal = &m_pool[m_index];
		std::copy(initList.begin(), initList.end(), returnVal);
		m_index += initList.size();
		return returnVal;
	}

private:
	std::array<T, POOL_SIZE> m_pool{};
	size_t m_index = 0;
};

#endif /* UTILS_MEMORY_POOL_H_ */
