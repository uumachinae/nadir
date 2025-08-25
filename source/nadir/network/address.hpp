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
///   File: address.hpp
///
/// Author: $author$
///   Date: 6/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_ADDRESS_HPP
#define _NADIR_NETWORK_ADDRESS_HPP

#include "nadir/base/base.hpp"
#include <sys/socket.h>
#include <netdb.h>

namespace nadir {
namespace network {

typedef int address_family_t;
typedef int address_version_t;
typedef implement_base addresst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: addresst
///////////////////////////////////////////////////////////////////////
template
<typename TFamily = address_family_t,
 typename TVersion = address_version_t,
 class TImplements = addresst_implements>

class _EXPORT_CLASS addresst: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TFamily family_t;
    typedef TVersion version_t;
    static const family_t family_unspec = AF_UNSPEC;
    static const version_t version_unspec = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual family_t family() const {
        return family_unspec;
    }
    virtual version_t version() const {
        return version_unspec;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef addresst<> address;

} // namespace network
} // namespace nadir 

#endif // _NADIR_NETWORK_ADDRESS_HPP 
        

