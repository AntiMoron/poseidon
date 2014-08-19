#ifndef POSEIDON_RAII_HPP_
#define POSEIDON_RAII_HPP_

namespace Poseidon {

/*
struct FileCloser {
	int operator()() const {
		return -1;
	}
	void operator()(int file) const {
		::close(file);
	}
};
*/

template<typename Handle, typename Closer>
class ScopedHandle {
private:
	Handle m_handle;

public:
	ScopedHandle() throw()
		: m_handle(Closer()())
	{
	}
	explicit ScopedHandle(Handle handle)
		: m_handle(handle)
	{
	}
	ScopedHandle &operator=(Handle handle) throw() {
		reset(handle);
		return *this;
	}
	~ScopedHandle() throw() {
		reset();
	}

private:
	ScopedHandle(const ScopedHandle &);
	void operator=(const ScopedHandle &);

public:
	Handle get() const throw() {
		return m_handle;
	}
	Handle release() throw() {
		const Handle ret = m_handle;
		m_handle = Closer()();
		return ret;
	}
	void reset(Handle handle = Closer()()) throw() {
		const Handle old = m_handle;
		m_handle = handle;
		if(old != Closer()()){
			Closer()(old);
		}
	}
	void swap(ScopedHandle &rhs) throw() {
		const Handle my = m_handle;
		m_handle = rhs.m_handle;
		rhs.m_handle = my;
	}
};

template<typename Handle, typename Closer>
void swap(ScopedHandle<Handle, Closer> &lhs,
	ScopedHandle<Handle, Closer> &rhs) throw()
{
	lhs.swap(rhs);
}

template<typename Handle, typename Closer>
bool operator==(const ScopedHandle<Handle, Closer> &lhs,
	const ScopedHandle<Handle, Closer> &rhs) throw()
{
	return lhs.get() == rhs.get();
}
template<typename Handle, typename Closer>
bool operator!=(const ScopedHandle<Handle, Closer> &lhs,
	const ScopedHandle<Handle, Closer> &rhs) throw()
{
	return lhs.get() != rhs.get();
}

template<typename Handle, typename Closer>
bool operator==(Handle lhs,
	const ScopedHandle<Handle, Closer> &rhs) throw()
{
	return lhs == rhs.get();
}
template<typename Handle, typename Closer>
bool operator!=(Handle lhs,
	const ScopedHandle<Handle, Closer> &rhs) throw()
{
	return lhs != rhs.get();
}

template<typename Handle, typename Closer>
bool operator==(const ScopedHandle<Handle, Closer> &lhs,
	Handle rhs) throw()
{
	return lhs.get() == rhs;
}
template<typename Handle, typename Closer>
bool operator!=(const ScopedHandle<Handle, Closer> &lhs,
	Handle rhs) throw()
{
	return lhs.get() != rhs;
}

}

#endif