#ifndef POSEIDON_ATOMIC_HPP_
#define POSEIDON_ATOMIC_HPP_

namespace Poseidon {

template<typename T>
struct Identity_ {
	typedef T type;
};

template<typename T>
T atomicLoad(const volatile T &mem) throw() {
	volatile int barrier;
	__sync_lock_test_and_set(&barrier, 1);
	return mem;
}
template<typename T>
void atomicStore(volatile T &mem, typename Identity_<T>::type val) throw() {
	mem = val;
	volatile int barrier;
	__sync_lock_release(&barrier);
}

template<typename T>
T atomicAdd(volatile T &mem, typename Identity_<T>::type val) throw() {
	return __sync_add_and_fetch(&mem, val);
}
template<typename T>
T atomicSub(volatile T &mem, typename Identity_<T>::type val) throw() {
	return __sync_sub_and_fetch(&mem, val);
}

template<typename T>
T atomicCmpExchange(volatile T &mem, typename Identity_<T>::type cmp,
	typename Identity_<T>::type xchg) throw()
{
	return __sync_val_compare_and_swap(&mem, cmp, xchg);
}
template<typename T>
T atomicExchange(volatile T &mem, typename Identity_<T>::type xchg) throw() {
	T cmp = mem;
	for(;;){
		const T old = __sync_val_compare_and_swap(&mem, cmp, xchg);
		if(old == cmp){
			break;
		}
		cmp = old;
	}
	return cmp;
}

}

#endif
