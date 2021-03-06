#ifndef POSEIDON_VIRTUAL_SHARED_FROM_THIS_HPP_
#define POSEIDON_VIRTUAL_SHARED_FROM_THIS_HPP_

#include <cassert>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_virtual_base_of.hpp>
#include <boost/static_assert.hpp>

namespace Poseidon {

class VirtualSharedFromThis
	: public boost::enable_shared_from_this<VirtualSharedFromThis>
{
public:
	// 定义在别处。参考源文件中的注释。
	virtual ~VirtualSharedFromThis() = 0;

public:
	template<typename DerivedT>
	boost::shared_ptr<const DerivedT> virtualSharedFromThis() const {
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_virtual_base_of<VirtualSharedFromThis, DerivedT>::value),
			"Please virtually derive from VirtualSharedFromThis.");

		return boost::dynamic_pointer_cast<const DerivedT>(shared_from_this());
	}
	template<typename DerivedT>
	boost::shared_ptr<DerivedT> virtualSharedFromThis(){
		BOOST_STATIC_ASSERT_MSG(
			(boost::is_virtual_base_of<VirtualSharedFromThis, DerivedT>::value),
			"Please virtually derive from VirtualSharedFromThis.");

		return boost::dynamic_pointer_cast<DerivedT>(shared_from_this());
	}

	template<typename DerivedT>
	boost::weak_ptr<const DerivedT> virtualWeakFromThis() const {
		return virtualSharedFromThis<const DerivedT>();
	}
	template<typename DerivedT>
	boost::weak_ptr<DerivedT> virtualWeakFromThis(){
		return virtualSharedFromThis<DerivedT>();
	}
};

}

#endif
