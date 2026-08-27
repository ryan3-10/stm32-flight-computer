#ifndef INTERFACES_I_CONTEXT_H_
#define INTERFACES_I_CONTEXT_H_

class IContext {
public:
	virtual void sleep() = 0;
	virtual void awakeFromIsr() = 0;
};

#endif /* INTERFACES_I_CONTEXT_H_ */
