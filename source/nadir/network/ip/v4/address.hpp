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
#ifndef _NADIR_NETWORK_IP_V4_ADDRESS_HPP
#define _NADIR_NETWORK_IP_V4_ADDRESS_HPP

#include "nadir/network/ip/address.hpp"

namespace nadir {
namespace network {
namespace ip {
namespace v4 {

typedef ip::addresst_implements addresst_implements;
typedef ip::address addresst_extends;
///////////////////////////////////////////////////////////////////////
///  Class: addresst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = addresst_implements, class TExtends = addresst_extends>

class _EXPORT_CLASS addresst: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Implements::family_t family_t;
    typedef typename Implements::version_t version_t;
    static const family_t family_unspec = Implements::family_unspec;
    static const version_t version_unspec = Implements::version_unspec;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    addresst() {}
    virtual ~addresst() {}

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual family_t family() const {
        return AF_INET;
    }
    virtual version_t version() const {
        return 4;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef addresst<> address;

} // namespace v4
} // namespace ip 
} // namespace network 
} // namespace nadir 

#endif // _NADIR_NETWORK_IP_V4_ADDRESS_HPP 
