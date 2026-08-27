#ifndef INTERFACES_I_QUEUE_H_
#define INTERFACES_I_QUEUE_H_

template <typename T>
class IQueue {
public:
	virtual void push(T) = 0;
	virtual T pop() = 0;
};



#endif /* INTERFACES_I_QUEUE_H_ */
