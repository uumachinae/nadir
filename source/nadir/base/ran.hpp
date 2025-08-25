///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: ran.hpp
///
/// Author: $author$
///   Date: 5/10/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_RAN_HPP
#define _NADIR_BASE_RAN_HPP

#include "nadir/base/base.hpp"

namespace nadir {

typedef implement_base rant_implements;
///////////////////////////////////////////////////////////////////////
///  Class: rant
///////////////////////////////////////////////////////////////////////
template <class TImplements = rant_implements>

class _EXPORT_CLASS rant: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void run() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef rant<> ran;

} // namespace nadir 

#endif // _NADIR_BASE_RAN_HPP 
