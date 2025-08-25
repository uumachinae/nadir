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
#ifndef _NADIR_NETWORK_IP_V4_ENDPOINT_HPP
#define _NADIR_NETWORK_IP_V4_ENDPOINT_HPP

#include "nadir/network/ip/endpoint.hpp"
#include "nadir/network/ip/v4/address.hpp"

namespace nadir {
namespace network {
namespace ip {
namespace v4 {

typedef struct sockaddr_in sockaddr_t;

typedef ip::endpointt_implements endpointt_implements;
typedef ip::endpointt<address> endpointt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: endpointt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = endpointt_implements,
 class TExtends = endpointt_extends>

class _EXPORT_CLASS endpointt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    endpointt(const char* host, sockport_t port) {
        if (!(this->attach(host, port))) {
            attach_exception e(attach_failed);
            LOG_ERROR("...throwing attach_exception e(attach_failed)...");
            throw (e);
        }
    }
    endpointt() {
    }
    virtual ~endpointt() {
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
    using Implements::attach;
    virtual sockaddr_attached_t attach
    (const sockaddr_attached_t socket_address, socklen_t socket_address_len, sockport_t port) {
        if ((socket_address) && (socket_address_len == (this->socket_address_len()))) {
            if (this->family() == (socket_address->sa_family)) {
                sockaddr_attached_t attached = 0;
                if ((attached = this->attach(port))) {
                    const sockaddr_t& sockaddr = (const sockaddr_t&)(*socket_address);
                    socket_address_.sin_addr.s_addr = sockaddr.sin_addr.s_addr;
                }
                return attached;
            }
        }
        return 0;
    }
    virtual sockaddr_attached_t attach(sockport_t port) {
        memset(&socket_address_, 0, this->socket_address_len_ = (this->socket_address_len()));
        socket_address_.sin_family = this->family();
        socket_address_.sin_addr.s_addr = INADDR_ANY;
        socket_address_.sin_port = htons(this->socket_address_port_ = port);
        return Extends::attach((sockaddr_attached_t)(&socket_address_));
    }
    virtual socklen_t socket_address_len() const {
        return ((socklen_t)sizeof(socket_address_));
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    sockaddr_t socket_address_;
};
typedef endpointt<> endpoint;

} // namespace v4
} // namespace ip 
} // namespace network 
} // namespace nadir 

#endif // _NADIR_NETWORK_IP_V4_ENDPOINT_HPP 
