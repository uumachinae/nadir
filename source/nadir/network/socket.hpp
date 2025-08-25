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
///   File: socket.hpp
///
/// Author: $author$
///   Date: 6/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_SOCKET_HPP
#define _NADIR_NETWORK_SOCKET_HPP

#include "nadir/network/transport.hpp"
#include "nadir/network/endpoint.hpp"
#include "nadir/network/address.hpp"
#include "nadir/base/opened.hpp"
#include "nadir/base/attached.hpp"
#include <sys/socket.h>

namespace nadir {
namespace network {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int socket_sendflags_t;
typedef int socket_recvflags_t;
typedef int socket_optlevel_t;
typedef int socket_optname_t;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int socket_backlog_t;
enum {
    socket_backlog_none = 0,
    socket_backlog_default = SOMAXCONN
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int socket_linger_seconds_t;
enum {
    socket_linger_seconds_none = 0,
    socket_linger_seconds_default = 10
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int socket_shutdown_how_t;
enum {
    socket_shutdown_read = 0,
    socket_shutdown_write = 1,
    socket_shutdown_both = 2
};

typedef address_family_t socket_domain_t;
typedef transport_type_t socket_type_t;
typedef transport_protocol_t socket_protocol_t;

typedef address socket_address;
typedef transport socket_transport;
typedef endpoint socket_endpoint;

class _EXPORT_CLASS sockett_implemented;
typedef opener sockett_implements;
///////////////////////////////////////////////////////////////////////
///  Class: sockett
///////////////////////////////////////////////////////////////////////
template
<typename TDomain = socket_domain_t,
 typename TType = socket_type_t,
 typename TProtocol = socket_protocol_t,
 class TAddress = socket_address,
 class TTransport = socket_transport,
 class TEndpoint = socket_endpoint,
 class TImplements = sockett_implements>

class _EXPORT_CLASS sockett: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TDomain domain_t;
    typedef TType type_t;
    typedef TProtocol protocol_t;

    typedef TAddress address_t;
    typedef TTransport transport_t;
    typedef TEndpoint endpoint_t;

    typedef socket_linger_seconds_t linger_seconds_t;
    static const linger_seconds_t linger_seconds_default = socket_linger_seconds_default;

    typedef socket_shutdown_how_t shutdown_how_t;
    static const shutdown_how_t shutdown_read = socket_shutdown_read;
    static const shutdown_how_t shutdown_write = socket_shutdown_write;
    static const shutdown_how_t shutdown_both = socket_shutdown_both;

    typedef socket_backlog_t backlog_t;
    static const backlog_t backlog_default = socket_backlog_default;

    typedef socket_sendflags_t sendflags_t;
    typedef socket_recvflags_t recvflags_t;
    typedef socket_optlevel_t optlevel_t;
    typedef socket_optname_t optname_t;

    static const bool bind_as_reuseaddr_default = true;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const transport_t& transport) {
        domain_t domain = transport.domain();
        type_t type = transport.type();
        protocol_t protocol = transport.protocol();
        if ((this->open(domain, type, protocol))) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect(const endpoint_t& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->connect(addr, addrlen))) {
                return true;
            }
        }
        return false;
    }
    virtual bool bind(const endpoint_t& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->bind(addr, addrlen))) {
                return true;
            }
        }
        return false;
    }
    virtual bool listen(const endpoint_t& ep, backlog_t backlog) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->bind(addr, addrlen))) {
                if ((this->listen(backlog))) {
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool listen(const endpoint_t& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->bind(addr, addrlen))) {
                if ((this->listen())) {
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool accept(sockett& sock, const endpoint_t& ep) {
        sockett_implemented* implemented = 0;
        if ((implemented = sock.implemented())) {
            return accept(*implemented, ep);
        }
        return false;
    }
    virtual bool accept(sockett_implemented& sock, const endpoint_t& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->accept(sock, addr, addrlen))) {
                return true;
            }
        }
        return false;
    }
    virtual sockett_implemented* accept(const endpoint_t& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            sockett_implemented* sock = 0;
            if ((sock = this->accept(addr, addrlen))) {
                return sock;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(domain_t domain, type_t type, protocol_t protocol) {
        return false;
    }
    virtual bool close() {
        return false;
    }
    virtual bool shutdown() {
        return false;
    }
    virtual bool shutdown(shutdown_how_t how) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect(const sockaddr_t* addr, socklen_t addrlen) {
        return false;
    }
    virtual bool bind(const sockaddr_t* addr, socklen_t addrlen) {
        return false;
    }
    virtual bool accept(sockett_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) {
        return false;
    }
    virtual sockett_implemented* accept(sockaddr_t* addr, socklen_t& addrlen) {
        return 0;
    }
    virtual bool listen(backlog_t backlog) {
        return false;
    }
    virtual bool listen() {
        if ((this->listen(this->default_backlog()))) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t sendto
    (const void* buf, size_t len, sendflags_t flags, const endpoint_t& ep) {
        const sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            ssize_t count = this->sendto(buf, len, flags, addr, addrlen);
            return count;
        }
        return 0;
    }
    virtual ssize_t recvfrom
    (void* buf, size_t len, recvflags_t flags, const endpoint_t& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            ssize_t count = this->recvfrom(buf, len, flags, addr, &addrlen);
            return count;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t sendto
    (const void* buf, size_t len, sendflags_t flags,
     const sockaddr_t* addr, socklen_t addrlen) {
        return 0;
    }
    virtual ssize_t recvfrom
    (void* buf, size_t len, recvflags_t flags,
     sockaddr_t* addr, socklen_t* addrlen) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t send(const void* buf, size_t len, sendflags_t flags) {
        return 0;
    }
    virtual ssize_t recv(void* buf, size_t len, recvflags_t flags) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool get_family(address_family_t &family, sockaddr_t &addr) const {
        return false;
    }
    virtual bool get_name(sockaddr_t* addr, socklen_t &addrlen) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_reuseaddr_opt(bool on = true) {
        return false;
    }
    virtual bool set_noreuseaddr_opt(bool on = true) {
        return false;
    }
    virtual bool get_reuseaddr_opt(bool &on) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_delay_opt(bool on = true) {
        return false;
    }
    virtual bool set_nodelay_opt(bool on = true) {
        return false;
    }
    virtual bool get_delay_opt(bool &on) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_linger_opt
    (bool on = true, linger_seconds_t lingerSeconds = -1) {
        return false;
    }
    virtual bool set_dont_linger_opt
    (bool on = true, linger_seconds_t lingerSeconds = -1) {
        return false;
    }
    virtual bool get_linger_opt(bool &on, linger_seconds_t &lingerSeconds) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_opt
    (optlevel_t level, optname_t name, const void* value, socklen_t length) {
        return false;
    }
    virtual bool get_opt
    (optlevel_t level, optname_t name, void* value, socklen_t &length) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual backlog_t default_backlog() const {
        return backlog_default;
    }
    virtual linger_seconds_t default_linger_seconds() const {
        return linger_seconds_default;
    }
    virtual bool bind_as_reuseaddr() const {
        return bind_as_reuseaddr_default;
    }
    virtual sockett_implemented* implemented() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_close() {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef sockett<> socket;

typedef socket socket_extendt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: socket_extendt
///////////////////////////////////////////////////////////////////////
template
<typename TAttached,
 typename TUnattached = TAttached,
 TUnattached VUnattached = 0,
 class TImplements = socket_extendt_implements,
 class TExtends = nadir::openedt
 <TAttached, TUnattached, VUnattached, nadir::attachedt
  <TAttached, TUnattached, VUnattached, nadir::attachert
   <TAttached, TUnattached, VUnattached, TImplements> > > >

class _EXPORT_CLASS socket_extendt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename  Implements::domain_t domain_t;
    typedef typename  Implements::type_t type_t;
    typedef typename  Implements::protocol_t protocol_t;

    typedef typename  Implements::address_t address_t;
    typedef typename  Implements::transport_t transport_t;
    typedef typename  Implements::endpoint_t endpoint_t;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    socket_extendt() {
    }
    virtual ~socket_extendt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace network
} // namespace nadir 

#endif // _NADIR_NETWORK_SOCKET_HPP 
