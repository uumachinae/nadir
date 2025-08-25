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
#ifndef _NADIR_NETWORK_IP_ENDPOINT_HPP
#define _NADIR_NETWORK_IP_ENDPOINT_HPP

#include "nadir/network/endpoint.hpp"
#include "nadir/network/ip/address.hpp"

namespace nadir {
namespace network {
namespace ip {

typedef network::endpoint_extendt_implements endpointt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: endpointt
///////////////////////////////////////////////////////////////////////
template
<class TAddress,
 class TImplements = endpointt_implements,
 class TExtends = network::endpoint_extendt<TAddress> >

class _EXPORT_CLASS endpointt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    endpointt(const char* host, sockport_t port)
    : socket_address_port_(0), socket_address_len_(0) {
        if (!(this->attach(host, port))) {
            attach_exception e(attach_failed);
            LOG_ERROR("...throwing attach_exception e(attach_failed)...");
            throw (e);
        }
    }
    endpointt()
    : socket_address_port_(0), socket_address_len_(0) {
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
protected:
    sockport_t socket_address_port_;
    socklen_t socket_address_len_;
};

} // namespace ip
} // namespace network 
} // namespace nadir 

#endif // _NADIR_NETWORK_IP_ENDPOINT_HPP 
