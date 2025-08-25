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
///   File: opened.hpp
///
/// Author: $author$
///   Date: 3/29/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_CRT_FILE_OPENED_HPP
#define XOS_IO_CRT_FILE_OPENED_HPP

#include "xos/io/crt/file/attached.hpp"
#include "xos/base/array.hpp"
#include "xos/base/string.hpp"

#define XOS_IO_CRT_FILE_MODE_BINARY "b"

#define XOS_IO_CRT_FILE_MODE_READ "r"
#define XOS_IO_CRT_FILE_MODE_READ_BINARY \
    XOS_IO_CRT_FILE_MODE_READ \
    XOS_IO_CRT_FILE_MODE_BINARY

#define XOS_IO_CRT_FILE_MODE_WRITE "w"
#define XOS_IO_CRT_FILE_MODE_WRITE_BINARY \
    XOS_IO_CRT_FILE_MODE_WRITE \
    XOS_IO_CRT_FILE_MODE_BINARY

#define XOS_IO_CRT_FILE_MODE_APPEND "a"
#define XOS_IO_CRT_FILE_MODE_APPEND_BINARY \
    XOS_IO_CRT_FILE_MODE_APPEND \
    XOS_IO_CRT_FILE_MODE_BINARY

namespace xos {
namespace io {
namespace crt {
namespace file {

/// class openedt
template 
<class TExtends = xos::openedt
 <attached_t, int, 0, file::attached::implement_t, file::attached::extend_t, file::attached>, 
 class TImplements = typename TExtends::implements>
class exported openedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef openedt derives;

    typedef int mode_t;
    enum { mode_none, mode_binary, mode_text };

    typedef typename TExtends::attached_t attached_t;
    typedef typename TExtends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    /// constructor / destructor
    openedt(attached_t detached, bool is_open): extends(detached, is_open) {
    }
    openedt(attached_t detached): extends(detached) {
    }
    openedt(const openedt& copy): extends(copy) {
    }
    openedt() {
    }
    virtual ~openedt() {
        if (!(this->closed())) {
            LOGGER_IS_LOGGED_ERROR("...failed on this->closed() throw open_exception(close_failed)...");
            throw open_exception(close_failed);
        }
    }

    /// open... /  close...
    virtual attached_t open_detached(const char* name, const char* mode) const {
        attached_t detached = (attached_t)unattached;
        if ((name) && (name[0]) && (mode) && (mode[0])) {
            LOGGER_IS_LOGGED_DEBUG("::fopen(name = " << name << ", mode = " << mode << ")...");
            if ((attached_t)unattached != (detached = ::fopen(name, mode))) {
                LOGGER_IS_LOGGED_DEBUG("...::fopen(name = " << name << ", mode = " << mode << ")");
            } else {
                LOGGER_IS_LOGGED_ERROR("......failed errno = " << errno << " on ::fopen(name = " << name << ", mode = " << mode << ")");
            }
        }
        return detached;
    }
    virtual bool close_detached(attached_t detached) const {
        if ((detached)) {
            int err = 0;
            LOGGER_IS_LOGGED_DEBUG("::fclose(detached = " << pointer_to_string(detached) << ")...");
            if (!(err = ::fclose(detached))) {
                LOGGER_IS_LOGGED_DEBUG("...::fclose(detached = " << pointer_to_string(detached) << ")");
                return true;
            } else {
                LOGGER_IS_LOGGED_ERROR("...failed errno = " << errno << " on ::fclose(detached = " << pointer_to_string(detached) << ")");
            }
        }
        return false;
    }

    /// ...mode...
    virtual const char* mode_read() const {
        return XOS_IO_CRT_FILE_MODE_READ;
    }
    virtual const char* mode_read_binary() const {
        return XOS_IO_CRT_FILE_MODE_READ_BINARY;
    }
    virtual const char* mode_write() const {
        return XOS_IO_CRT_FILE_MODE_WRITE;
    }
    virtual const char* mode_write_binary() const {
        return XOS_IO_CRT_FILE_MODE_WRITE_BINARY;
    }
    virtual const char* mode_append() const {
        return XOS_IO_CRT_FILE_MODE_APPEND;
    }
    virtual const char* mode_append_binary() const {
        return XOS_IO_CRT_FILE_MODE_APPEND_BINARY;
    }
    virtual mode_t binary_mode() const {
        return mode_binary;
    }
    virtual mode_t text_mode() const {
        return mode_text;
    }
}; /// class openedt
typedef openedt<> opened;

namespace safe {
/// class openedt
template 
<class TImplement, 
 class TExtends = file::opened, class TImplements = typename TExtends::implements>
class exported openedt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef openedt derives;

    typedef typename TImplement::what_t what_t;
    typedef typename TImplement::sized_t sized_t;

    typedef typename extends::mode_t mode_t;
    enum { mode_binary = extends::mode_binary, mode_text = extends::mode_text };

    typedef typename extends::attached_t attached_t;
    typedef typename extends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    /// constructor / destructor
    openedt(attached_t detached, bool is_open): extends(detached, is_open) {
    }
    openedt(attached_t detached): extends(detached) {
    }
    openedt(const openedt& copy): extends(copy) {
    }
    openedt() {
    }
    virtual ~openedt() {
    }

    /// open...
    virtual bool open(const char* name, mode_t mode = mode_binary) {
        if ((this->closed())) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = open_attached(name, mode))) {
                this->attach_opened(detached);
                return true;
            }
        }
        return false;
    }
    virtual attached_t open_attached(const char* name, mode_t mode = mode_binary) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = open_detached(name, mode))) {
            this->attach(detached);
        }
        return detached;
    }
    virtual bool open_read(const char* name, mode_t mode = mode_binary) {
        if ((this->closed())) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = open_read_attached(name, mode))) {
                this->attach_opened(detached);
                return true;
            }
        }
        return false;
    }
    virtual attached_t open_read_attached(const char* name, mode_t mode = mode_binary) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = open_read_detached(name, mode))) {
            this->attach(detached);
        }
        return detached;
    }
    virtual bool open_write(const char* name, mode_t mode = mode_binary) {
        if ((this->closed())) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = open_write_attached(name, mode))) {
                this->attach_opened(detached);
                return true;
            }
        }
        return false;
    }
    virtual attached_t open_write_attached(const char* name, mode_t mode = mode_binary) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = open_write_detached(name, mode))) {
            this->attach(detached);
        }
        return detached;
    }

    /// open_...safe...
    virtual bool open_safe(const char* name, const sized_t* pattern, mode_t mode = mode_binary) {
        if ((this->closed())) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = open_safe_attached(name, pattern, mode))) {
                this->attach_opened(detached);
                return true;
            }
        }
        return false;
    }
    virtual attached_t open_safe_attached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = open_safe_detached(name, pattern, mode))) {
            this->attach(detached);
        }
        return detached;
    }
    virtual bool open_read_safe(const char* name, const sized_t* pattern, mode_t mode = mode_binary) {
        if ((this->closed())) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = open_read_safe_attached(name, pattern, mode))) {
                this->attach_opened(detached);
                return true;
            }
        }
        return false;
    }
    virtual attached_t open_read_safe_attached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = open_read_safe_detached(name, pattern, mode))) {
            this->attach(detached);
        }
        return detached;
    }
    virtual bool open_write_safe(const char* name, const sized_t* pattern, mode_t mode = mode_binary) {
        if ((this->closed())) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = open_write_safe_attached(name, pattern, mode))) {
                this->attach_opened(detached);
                return true;
            }
        }
        return false;
    }
    virtual attached_t open_write_safe_attached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) {
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = open_write_safe_detached(name, pattern, mode))) {
            this->attach(detached);
        }
        return detached;
    }

    /// open..._safe...
    virtual attached_t open_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
        attached_t detached = 0;
        return detached;
    }
    virtual attached_t open_read_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
        attached_t detached = 0;
        return detached;
    }
    virtual attached_t open_write_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
        attached_t detached = 0;
        return detached;
    }
    virtual bool opened_safe_detached(attached_t detached, const sized_t* pattern) const {
        if ((detached) && (pattern) && (pattern[0])) {
            stringt<sized_t> match(pattern);
            size_t length = 0;
            bool safe = false;

            if (0 < (length = match.length())) {
                arrayt<sized_t> array(length);
                sized_t* sized = 0;
                size_t size = 0;

                if (((sized = array.elements())) && (length <= (size = array.size()))) {
                    ssize_t count = 0;

                    if (0 > (count = ::fread(sized, sizeof(sized_t), length, detached))) {
                        LOGGER_IS_LOGGED_ERROR("...failed errno = " << errno << " on ::fread(sized, " << sizeof(sized_t) << ", " << length << ", " << pointer_to_string(detached) << ")");
                    } else {
                        if (length > (count)) {
                            if (0 == (count)) {
                                safe = true;
                            }
                        } else {
                            stringt<sized_t> compare(sized, length);
                            
                            if (0 == (match.compare(compare))) {
                                safe = true;
                            }
                        }
                    }
                }
            }
            return safe;
        }
        return false;
    }

    /// open...
    virtual attached_t open_detached(const char* name, mode_t mode = mode_binary) const {
        attached_t detached = 0;
        return detached;
    }
    virtual attached_t open_read_detached(const char* name, mode_t mode = mode_binary) const {
        attached_t detached = 0;
        return detached;
    }
    virtual attached_t open_write_detached(const char* name, mode_t mode = mode_binary) const {
        attached_t detached = 0;
        return detached;
    }
}; /// class openedt
} /// namespace safe

} /// namespace file
} /// namespace crt
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_CRT_FILE_OPENED_HPP 
