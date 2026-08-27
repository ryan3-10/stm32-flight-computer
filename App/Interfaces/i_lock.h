#ifndef INTERFACES_LOCK_H_
#define INTERFACES_LOCK_H_

class ILock {
public:
	ILock() = default;
	virtual ~ILock() = default;

	virtual void lock() = 0;
	virtual void unlock() = 0;
};



#endif /* INTERFACES_LOCK_H_ */
