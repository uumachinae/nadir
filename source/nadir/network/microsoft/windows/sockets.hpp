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
///   File: sockets.hpp
///
/// Author: $author$
///   Date: 6/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_NETWORK_MICROSOFT_WINDOWS_SOCKETS_HPP
#define _NADIR_NETWORK_MICROSOFT_WINDOWS_SOCKETS_HPP

#include "nadir/network/microsoft/windows/socket.hpp"
#include "nadir/network/sockets.hpp"

#if defined(WINSOCK_2)
#define WINSOCK_VERSION_MAJOR 2
#define WINSOCK_VERSION_MINOR 2
#else // defined(WINSOCK_2)
#define WINSOCK_VERSION_MAJOR 1
#define WINSOCK_VERSION_MINOR 1
#endif // defined(WINSOCK_2)

namespace nadir {
namespace network {
namespace microsoft {
namespace windows {

typedef network::sockets socketst_implements;
typedef base socketst_extends;
///////////////////////////////////////////////////////////////////////
///  Class: socketst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = socketst_implements, class TExtends = socketst_extends>

class _EXPORT_CLASS socketst: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    socketst() {
        Implements*& instance = this->the_instance();
        if (!instance) {
            if (startup()) {
                instance = this;
            } else {
                const startup_exception e(startup_failed);
                LOG_ERROR("...throwing const startup_exception e(startup_failed)...");
                throw (e);
            }
        } else {
            const exist_exception e(already_exist_failed);
            LOG_ERROR("...throwing const exist_exception e(already_exist_failed)...");
            throw (e);
        }
    }
    virtual ~socketst() {
        Implements*& instance = this->the_instance();
        if (this == instance) {
            instance = 0;
            if (!cleanup()) {
                const startup_exception e(cleanup_failed);
                LOG_ERROR("...throwing const startup_exception e(cleanup_failed)...");
                throw (e);
            }
        } else {
            const exist_exception e(doesnt_exist_failed);
            LOG_ERROR("...throwing const exist_exception e(doesnt_exist_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool startup() {
        BYTE wsaVersionMajor = WINSOCK_VERSION_MAJOR,
             wsaVersionMinor = WINSOCK_VERSION_MINOR;
        WORD wsaVersion = MAKEWORD(wsaVersionMajor, wsaVersionMinor);
        WSADATA wsaData;
        memset(&wsaData, 0, sizeof(WSADATA));
        LOG_DEBUG("WSAStartup(wsaVersion = " << wsaVersion << ",...)...");
        if (SOCKET_ERROR != (WSAStartup(wsaVersion, &wsaData))) {
            LOG_DEBUG("...WSAStartup(wsaVersion = " << wsaVersion << ",...)");
            return true;
        } else {
            int error = WSAGetLastError();
            LOG_ERROR("...failed error = " << error << " on WSAStartup(wsaVersion = " << wsaVersion << ",...)");
        }
        return false;
    }
    virtual bool cleanup() {
        LOG_DEBUG("WSACleanup()...");
        if (SOCKET_ERROR != (WSACleanup())) {
            LOG_DEBUG("...WSACleanup()");
            return true;
        } else {
            int error = WSAGetLastError();
            LOG_ERROR("...failed error = " << error << " on WSACleanup()");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef socketst<> sockets;

} // namespace windows
} // namespace microsoft 
} // namespace network 
} // namespace nadir 

#endif // _NADIR_NETWORK_MICROSOFT_WINDOWS_SOCKETS_HPP 
