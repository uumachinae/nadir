///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: pointed.hpp
///
/// Author: $author$
///   Date: 11/7/2021
///////////////////////////////////////////////////////////////////////
#ifndef XOS_BASE_POINTED_HPP
#define XOS_BASE_POINTED_HPP

#include "xos/base/base.hpp"

namespace xos {

/// class pointedt
template <class TExtends = extend, class TImplements = implement>
class exported pointedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef pointedt derives; 
    
    /// constructors / destructor
    pointedt(const pointedt& copy): extends(copy) {
    }
    pointedt() {
    }
    virtual ~pointedt() {
    }
}; /// class pointedt
typedef pointedt<> pointed;

} /// namespace xos

#endif /// XOS_BASE_POINTED_HPP
