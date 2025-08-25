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
///   File: transport.hpp
///
/// Author: $author$
///   Date: 6/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_TRANSPORT_HPP
#define _NADIR_NETWORK_TRANSPORT_HPP

#include "nadir/base/base.hpp"
#include <sys/socket.h>

namespace nadir {
namespace network {

typedef int transport_domain_t;
typedef int transport_type_t;
typedef int transport_protocol_t;

typedef implement_base transportt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: transportt
///////////////////////////////////////////////////////////////////////
template
<typename TDomain = transport_domain_t,
 typename TType = transport_type_t,
 typename TProtocol = transport_protocol_t,
 class TImplements = transportt_implements>

class _EXPORT_CLASS transportt: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TDomain domain_t;
    typedef TType type_t;
    typedef TProtocol protocol_t;
    static const domain_t domain_unspec = PF_UNSPEC;
    static const type_t type_unspec = SOCK_RAW;
    static const protocol_t protocol_unspec = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual domain_t domain() const {
        return domain_unspec;
    }
    virtual type_t type() const {
        return type_unspec;
    }
    virtual protocol_t protocol() const {
        return protocol_unspec;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef transportt<> transport;

typedef transport transport_extendt_implements;
typedef base transport_extendt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: transport_extendt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = transport_extendt_implements,
 class TExtends = transport_extendt_extends>

class _EXPORT_CLASS transport_extendt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Implements::domain_t domain_t;
    typedef typename Implements::type_t type_t;
    typedef typename Implements::protocol_t protocol_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    transport_extendt() {
    }
    virtual ~transport_extendt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef transport_extendt<> transport_extend;

} // namespace network
} // namespace nadir 

#endif // _NADIR_NETWORK_TRANSPORT_HPP 
