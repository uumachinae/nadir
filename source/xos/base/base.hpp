///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: base.hpp
///
/// Author: $author$
///   Date: 12/3/2019, 7/13/2021
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_BASE_HPP
#define XOS_BASE_BASE_HPP

#include "xos/base/platform.hpp"

namespace xos {

/// class implement
class exported implement {
public:
    typedef implement derives;

    /// constructor / destructor
    virtual ~implement() {
    }
}; /// class implement

/// class extend
class exported extend: virtual public implement {
public:
    typedef implement implements;
    typedef extend derives;

    /// constructor / destructor
    extend(const extend& copy) {
    }
    extend() {
    }
    virtual ~extend() {
    }
}; /// class extend

namespace base {

typedef xos::implement implement_base;
typedef xos::extend base;

} /// namespace base
} /// namespace xos

#endif /// ndef XOS_BASE_BASE_HPP
