///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: wrapped.hpp
///
/// Author: $author$
///   Date: 3/7/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_WRAPPED_HPP
#define XOS_BASE_WRAPPED_HPP

#include "xos/base/base.hpp"

namespace xos {

/// class wrappert
template 
<typename TWrapped = pointer_t, 
 class TExtends = extend, class TImplements = typename TExtends::implements>

class exported wrappert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef wrappert derives;

    typedef TWrapped wrapped_t;
    
    /// constructor / destructor
    wrappert(const wrappert& copy): extends(copy), wrapped_(copy.wrapped_) {
    }
    wrappert(wrapped_t& wrapped): wrapped_(wrapped) {
    }
    wrappert(): wrapped_(this_wrapped_) {
    }
    virtual ~wrappert() {
    }
    
    /// ...wrapped...
    virtual operator wrapped_t& () const {
        return (wrapped_t&)wrapped_;
    }
    virtual wrapped_t& wrapped() const {
        return (wrapped_t&)wrapped_;
    }

protected:
    wrapped_t this_wrapped_, &wrapped_;
}; /// class wrappert
typedef wrappert<> wrapper;

namespace base {
/// class wrappedt
template 
<typename TWrapped = pointer_t, 
 class TExtends = xos::wrappert<TWrapped>, class TImplements = typename TExtends::implements>

class exported wrappedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef wrappedt derives;

    typedef TWrapped wrapped_t;
    
    /// constructor / destructor
    wrappedt(const wrappedt& copy): extends(copy) {
    }
    wrappedt(wrapped_t& wrapped): extends(wrapped) {
    }
    wrappedt() {
    }
    virtual ~wrappedt() {
    }
    
}; /// class wrappedt
} /// namespace base

} /// namespace xos

#endif /// ndef XOS_BASE_WRAPPED_HPP 
