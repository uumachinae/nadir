///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: attached.hpp
///
/// Author: $author$
///   Date: 3/29/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_CRT_FILE_ATTACHED_HPP
#define XOS_IO_CRT_FILE_ATTACHED_HPP

#include "xos/base/logged.hpp"
#include "xos/base/attached.hpp"
#include "xos/base/opened.hpp"
#include "xos/base/logger.hpp"

namespace xos {
namespace io {
namespace crt {
namespace file {

typedef FILE* attached_t;

/// class attachedt
template 
<class TImplement = xos::loggedt<opener>, class TExtend = xos::extended::loggedt<TImplement>,
 class TExtends = xos::attachedt<attached_t, int, 0, TImplement, TExtend>,
 class TImplements = typename TExtends::implements>
class exported attachedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef attachedt derives;

    typedef TImplement implement_t;
    typedef TExtend extend_t;
    typedef typename TExtends::attached_t attached_t;
    typedef typename TExtends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    /// constructor / destructor
    attachedt(attached_t detached): extends(detached) {
    }
    attachedt(const attachedt& copy): extends(copy) {
    }
    attachedt() {
    }
    virtual ~attachedt() {
    }

    /// ...mode_is_binary...
    virtual bool set_mode_is_binary(bool mode_is_binary = true) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = this->attached_to())) {
            return set_mode_is_binary_detached(detached, mode_is_binary);
        }
        return false;
    }
    virtual bool set_mode_is_binary_detached(attached_t detached, bool mode_is_binary = true) const {
        if ((attached_t)unattached != (detached)) {
#if defined(WINDOWS)
            int fd = 0;
            if (0 <= (fd = _fileno(detached))) {
                int err = 0, mode = (mode_is_binary)?(_O_BINARY):(_O_TEXT);
                if (0 > (err = ::_setmode(fd, mode))) {
                    LOGGER_IS_LOGGED_ERROR("...failed errno = " << errno << " on ::_setmode(fd = " << fd << ", mode = " << mode << ")");
                } else {
                    return true;
                }
            }
#else // defined(WINDOWS)
            return mode_is_binary;
#endif // defined(WINDOWS)
        }
        return false;
    }
}; /// class attachedt
typedef attachedt<> attached;

} /// namespace file
} /// namespace crt
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_CRT_FILE_ATTACHED_HPP 
