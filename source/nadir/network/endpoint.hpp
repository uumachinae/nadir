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
///   File: endpoint.hpp
///
/// Author: $author$
///   Date: 6/17/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_ENDPOINT_HPP
#define _NADIR_NETWORK_ENDPOINT_HPP

#include "nadir/base/attached.hpp"
#include "nadir/network/address.hpp"
#include "nadir/io/logger.hpp"

namespace nadir {
namespace network {

typedef int addrindex_t;
enum {
    first_addrindex = 0,
    last_addrindex = -1
};
typedef u_short sockport_t;
typedef struct sockaddr sockaddr_t;

typedef sockaddr_t* sockaddr_attached_t;
typedef int sockaddr_unattached_t;
enum { sockaddr_unattached = 0 };

typedef nadir::attachert
<sockaddr_attached_t, sockaddr_unattached_t,
 sockaddr_unattached, address> endpointt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: endpointt
///////////////////////////////////////////////////////////////////////
template <class TImplements = endpointt_implements>

class _EXPORT_CLASS endpointt: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::attach;
    virtual sockaddr_attached_t attach_first(const char_string& host, sockport_t port) {
        const char* chars = host.has_chars();
        if ((chars)) { return this->attach_first(chars, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach_last(const char_string& host, sockport_t port) {
        const char* chars = host.has_chars();
        if ((chars)) { return this->attach_last(chars, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach(const char_string& host, sockport_t port) {
        const char* chars = host.has_chars();
        if ((chars)) { return this->attach(chars, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach_first(const char* host, sockport_t port) {
        if ((host) && (host[0])) {
            return this->attach(host, first_addrindex, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach_last(const char* host, sockport_t port) {
        if ((host) && (host[0])) {
            return this->attach(host, last_addrindex, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach(const char* host, sockport_t port) {
        if ((host) && (host[0])) {
            return this->attach(host, first_addrindex, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach
    (const char_t* host, addrindex_t index, sockport_t port) {
        sockaddr_attached_t saddr = 0;
        struct addrinfo* addrs = 0;
        int err = 0;

        LOG_DEBUG("getaddrinfo(\"" << host << "\",...)...");
        if (!(err = getaddrinfo(host, 0, 0, &addrs))) {
            const address_family_t family = this->family();
            struct addrinfo* addr = 0;
            addrindex_t addr_i = 0;

            LOG_DEBUG("...getaddrinfo(\"" << host << "\",...) family = " << family);
            for (addr_i = 0, addr = addrs; addr; addr = addr->ai_next) {
                const address_family_t addrfamily = addr->ai_family;
                char addrhost[NI_MAXHOST];

                LOG_DEBUG("getnameinfo(...)... family = " << addrfamily);
                if (!(err = getnameinfo
                    (addr->ai_addr, addr->ai_addrlen, addrhost, sizeof(addrhost)-1, 0, 0, 0))) {

                    addrhost[sizeof(addrhost)-1] = 0;
                    LOG_DEBUG("...getnameinfo(..., addrhost = \"" << addrhost << "\",...)");
                    if (family == (addrfamily)) {
                        if ((addr_i == index) || ((last_addrindex == index) && !(addr->ai_next))) {
                            LOG_DEBUG("...found family " << family << " address[" << addr_i << "]");
                            saddr = this->attach(addr->ai_addr, addr->ai_addrlen, port);
                            break;
                        } else {
                            ++addr_i;
                        }
                    }
                } else {
                    LOG_ERROR("...failed " << this->last_error() << " on getnameinfo(...)");
                }
            }
            freeaddrinfo(addrs);
        } else {
            LOG_ERROR("...failed " << this->last_error() << " on getaddrinfo(\"" << host << "\",...)");
        }
        return saddr;
    }
    virtual sockaddr_attached_t attach
    (const sockaddr_attached_t socketAddress, socklen_t socketAddressLen, sockport_t port) {
        return 0;
    }
    virtual sockaddr_attached_t attach(sockport_t port) {
        return 0;
    }
    virtual sockaddr_attached_t attach(const char* path) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual sockaddr_attached_t socket_address(socklen_t& len) const {
        len = this->socket_address_len();
        return this->attached_to();
    }
    virtual sockaddr_attached_t socket_address() const {
        return this->attached_to();
    }
    virtual socklen_t socket_address_len() const {
        return 0;
    }
    virtual operator sockaddr_attached_t () const {
        return this->socket_address();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int last_error() const {
        return errno;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef endpointt<> endpoint;

typedef endpoint endpoint_extendt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: endpoint_extendt
///////////////////////////////////////////////////////////////////////
template
<class TAddress,
 class TImplements = endpoint_extendt_implements,
 class TExtends = nadir::attachedt
 <sockaddr_attached_t, sockaddr_unattached_t,
  sockaddr_unattached, endpoint_extendt_implements, TAddress> >

class _EXPORT_CLASS endpoint_extendt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    endpoint_extendt(const char* host, sockport_t port) {
        if (!(this->attach(host, port))) {
            attach_exception e(attach_failed);
            LOG_ERROR("...throwing attach_exception e(attach_failed)...");
            throw (e);
        }
    }
    endpoint_extendt() {
    }
    virtual ~endpoint_extendt() {
        if ((this->attached_to())) {
            if (!(this->detach())) {
                attach_exception e(detach_failed);
                LOG_ERROR("...throwing attach_exception e(detach_failed)...");
                throw (e);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace network
} // namespace nadir 

#endif // _NADIR_NETWORK_ENDPOINT_HPP 
