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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 3/30/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_CRT_FILE_WRITER_HPP
#define XOS_IO_CRT_FILE_WRITER_HPP

#include "xos/io/crt/file/opened.hpp"
#include "xos/io/writer.hpp"

namespace xos {
namespace io {
namespace crt {
namespace file {

/// class writert
template 
<class TImplements = io::writer, class TExtends = file::safe::openedt<TImplements> >
class exported writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef writert derives;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;

    typedef typename extends::mode_t mode_t;
    enum { mode_binary = extends::mode_binary, mode_text = extends::mode_text };

    typedef typename extends::attached_t attached_t;
    typedef typename extends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    /// constructor / destructor
    writert(attached_t attached, bool is_open): extends(attached, is_open) {
    }
    writert(attached_t attached): extends(attached) {
    }
    writert(const writert& copy): extends(copy) {
    }
    writert() {
    }
    virtual ~writert() {
        if (!(this->closed())) {
            LOGGER_IS_LOGGED_ERROR("...failed on this->closed() throw open_exception(close_failed)...");
            throw open_exception(close_failed);
        }
    }

    /// write... / flush...
    virtual ssize_t write(const what_t* what, size_t size) {
        ssize_t count = 0;
        if ((what) && (size)) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = this->attached_to())) {
                if (size != (count = ::fwrite(what, sizeof(sized_t), size, detached))) {
                    LOGGER_IS_LOGGED_ERROR("..." << size << " != " << count << " on ::fwrite(what, " << sizeof(sized_t) << ", " << size << ", " << pointer_to_string(detached) << ")");
                }
            }
        }
        return count;
    }    
    virtual ssize_t flush() {
        ssize_t count = 0;
        attached_t detached = (attached_t)unattached;
        if ((attached_t)unattached != (detached = this->attached_to())) {
            int err = 0;
            if ((err = ::fflush(detached))) {
                LOGGER_IS_LOGGED_ERROR("...failed " << errno << " on ::fflush(" << pointer_to_string(detached) << ")");
                count = -1;
            }
        }
        return count;
    }    

    /// open_safe...
    virtual attached_t open_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
        attached_t detached = 0;

        if ((name) && (name[0]) && (pattern) && (pattern[0])) {
            const char *read_mode = (mode != mode_binary)?(this->mode_read()):(this->mode_read_binary());

            if ((read_mode) && (read_mode[0])) {
                bool safe = false;

                if ((safe = !(detached = ::fopen(name, read_mode)))) {
                    LOGGER_IS_LOGGED_DEBUG("...errno = " << errno << " on ::fopen(\"" << name << "\", \"" << read_mode << "\")");
                } else {
                    safe = this->opened_safe_detached(detached, pattern);
                    this->close_detached(detached);
                    detached = 0;
                }
                if ((safe)) {
                    const char *write_mode = (mode != mode_binary)?(this->mode_write()):(this->mode_write_binary());
                    
                    if ((write_mode) && (write_mode[0])) {
                        if (!(detached = ::fopen(name, write_mode))) {
                            LOGGER_IS_LOGGED_ERROR("...failed errno = " << errno << " on ::fopen(\"" << name << "\", \"" << write_mode << "\")");
                        }
                    }
                }
            }
        }
        return detached;
    }
}; /// class writert

typedef writert<> writer;
typedef writert<io::char_writer> char_writer;

} /// namespace file
} /// namespace crt
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_CRT_FILE_WRITER_HPP 
