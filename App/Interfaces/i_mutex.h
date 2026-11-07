#ifndef INTERFACES_LOCK_H_
#define INTERFACES_LOCK_H_

class IMutex {
public:
	IMutex() = default;
	virtual ~IMutex() = default;

	virtual void lock() = 0;
	virtual void unlock() = 0;
};



#endif /* INTERFACES_LOCK_H_ */
