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
#ifndef _NADIR_NETWORK_SOCKETS_HPP
#define _NADIR_NETWORK_SOCKETS_HPP

#include "nadir/network/socket.hpp"
#include "nadir/base/startup.hpp"
#include "nadir/base/exists.hpp"

namespace nadir {
namespace network {

///////////////////////////////////////////////////////////////////////
///  Class: socketst_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS socketst_implements
: virtual public exists, virtual public startedup {
};

///////////////////////////////////////////////////////////////////////
///  Class: socketst
///////////////////////////////////////////////////////////////////////
template <class TImplements = socketst_implements>
class _EXPORT_CLASS socketst: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool startup() {
        return true;
    }
    virtual bool cleanup() {
        return true;
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static socketst*& the_instance() {
        static socketst* instance = 0;
        return instance;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef socketst<> sockets;

} // namespace network
} // namespace nadir 

#endif // _NADIR_NETWORK_SOCKETS_HPP 
