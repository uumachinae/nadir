///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 11/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_WRAPPED_HPP
#define _NADIR_BASE_WRAPPED_HPP

#include "nadir/base/base.hpp"

namespace nadir {

typedef int wrapped_initalized_t;
enum { wrapped_initalized = 0 };
typedef implement_base wrappedt_implements;
typedef base wrappedt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: wrappedt
///////////////////////////////////////////////////////////////////////
template
<typename TWrapped,
 typename TInitialized = wrapped_initalized_t,
 TInitialized VInitialized = wrapped_initalized,
 class TImplements = wrappedt_implements, class TExtends = wrappedt_extends>

class _EXPORT_CLASS wrappedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TWrapped wrapped_t;
    typedef TInitialized initialized_t;
    enum { initialized = VInitialized };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    wrappedt(initialized_t initialized) {
        this->set(initialized);
    }
    wrappedt(const wrapped_t& copy) {
        this->copy(copy);
    }
    wrappedt(const wrappedt& copy) {
        this->copy(copy);
    }
    wrappedt() {
    }
    virtual ~wrappedt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wrappedt& copy(const wrappedt& copy) {
        memcpy(&wrapped_, &copy.wrapped_, sizeof(wrapped_t));
        return *this;
    }
    virtual wrappedt& copy(const wrapped_t& copy) {
        memcpy(&wrapped_, &copy, sizeof(wrapped_t));
        return *this;
    }
    virtual wrappedt& set(initialized_t initialized) {
        memset(&wrapped_, initialized, sizeof(wrapped_t));
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual wrappedt& operator = (const wrappedt& copy) {
        memcpy(&wrapped_, &copy.wrapped_, sizeof(wrapped_t));
        return *this;
    }
    virtual wrappedt& wrapper() const {
        return (wrappedt&)(*this);
    }
    virtual wrapped_t& wrapped() const {
        return (wrapped_t&)(wrapped_);
    }
    virtual operator wrapped_t& () const {
        return (wrapped_t&)(wrapped_);
    }
    virtual wrapped_t& operator >> (wrapped_t& to) const {
        memcpy(&to, &wrapped_, sizeof(wrapped_t));
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    wrapped_t wrapped_;
};

} // namespace nadir 

#endif // _NADIR_BASE_WRAPPED_HPP 
