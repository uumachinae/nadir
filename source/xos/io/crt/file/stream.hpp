///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: stream.hpp
///
/// Author: $author$
///   Date: 7/16/2021
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_CRT_FILE_STREAM_HPP
#define XOS_IO_CRT_FILE_STREAM_HPP

#include "xos/io/stream.hpp"
#include "xos/io/crt/file/opened.hpp"

namespace xos {
namespace io {
namespace crt {
namespace file {

/// class streamt
template <class TImplements = io::stream, class TExtends = file::safe::openedt<TImplements> >
class exported streamt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef streamt derives; 
    
    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;

    typedef typename extends::attached_t attached_t;
    typedef typename extends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    typedef typename extends::mode_t mode_t;
    enum { mode_binary = extends::mode_binary, 
           mode_text = extends::mode_text };

    /// constructors / destructor
    streamt(attached_t attached, bool is_open): extends(attached, is_open) {
    }
    streamt(attached_t attached): extends(attached) {
    }
    streamt(const streamt& copy): extends(copy) {
    }
    streamt() {
    }
    virtual ~streamt() {
    }

    /// ...fill / read...
    virtual ssize_t fill() {
        ssize_t count = 0;
        attached_t detached = (attached_t)unattached;
        if (!((attached_t)unattached != (detached = this->attached_to()))) {
            count = -1;
        }
        return count;
    }    
    virtual ssize_t read(what_t* what, size_t size) {
        ssize_t count = 0;
        if ((what) && (size)) {
            attached_t detached = (attached_t)unattached;
            if ((attached_t)unattached != (detached = this->attached_to())) {
                if (0 >= (count = ::fread(what, sizeof(sized_t), size, detached))) {
                    if ((!::feof(detached)) || (::ferror(detached))) {
                        LOGGER_IS_LOGGED_ERROR("...failed " << count << " on ::fread(what, " << sizeof(sized_t) << ", " << size << ", " << pointer_to_string(detached) << ")");
                    }
                }
            }
        }
        return count;
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

    /// open_...safe...
    virtual attached_t open_write_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
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
    virtual attached_t open_read_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
        attached_t detached = 0;

        if ((name) && (name[0]) && (pattern) && (pattern[0])) {
            const char *read_mode = (mode != mode_binary)?(this->mode_read()):(this->mode_read_binary());

            if ((read_mode) && (read_mode[0])) {

                if ((!(detached = ::fopen(name, read_mode)))) {
                    LOGGER_IS_LOGGED_ERROR("...errno = " << errno << " on ::fopen(\"" << name << "\", \"" << read_mode << "\")");
                } else {
                    if (!(this->opened_safe_detached(detached, pattern))) {
                        this->close_detached(detached);
                        detached = 0;
                    }
                }
            }
        }
        return detached;
    }
    virtual attached_t open_read_detached(const char* name, mode_t mode = mode_binary) const {
        attached_t detached = 0;

        if ((name) && (name[0])) {
            const char *read_mode = (mode != mode_binary)?(this->mode_read()):(this->mode_read_binary());

            if ((read_mode) && (read_mode[0])) {

                if ((!(detached = ::fopen(name, read_mode)))) {
                    LOGGER_IS_LOGGED_ERROR("...errno = " << errno << " on ::fopen(\"" << name << "\", \"" << read_mode << "\")");
                } else {
                }
            }
        }
        return detached;
    }
}; /// class streamt
typedef streamt<> stream;

typedef streamt<io::streamt<io::char_writert<io::char_readert<io::seekert<io::char_sequence > > > > > char_stream;
typedef streamt<io::streamt<io::char_writert<io::char_readert<io::seekert<io::tchar_sequence > > > > > tchar_stream;
typedef streamt<io::streamt<io::char_writert<io::char_readert<io::seekert<io::wchar_sequence > > > > > wchar_stream;

} /// namespace file
} /// namespace crt
} /// namespace io
} /// namespace xos

#endif /// XOS_IO_CRT_FILE_STREAM_HPP
