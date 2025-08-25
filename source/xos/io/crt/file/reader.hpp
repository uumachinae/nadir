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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 3/30/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_CRT_FILE_READER_HPP
#define XOS_IO_CRT_FILE_READER_HPP

#include "xos/io/crt/file/opened.hpp"
#include "xos/io/reader.hpp"

namespace xos {
namespace io {
namespace crt {
namespace file {

/// class readert
template 
<class TImplements = io::reader, class TExtends = file::safe::openedt<TImplements> >
class exported readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef readert derives;

    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;

    typedef typename extends::mode_t mode_t;
    enum { mode_binary = extends::mode_binary, mode_text = extends::mode_text };

    typedef typename extends::attached_t attached_t;
    typedef typename extends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    /// constructor / destructor
    readert(attached_t attached, bool is_open): extends(attached, is_open) {
    }
    readert(attached_t attached): extends(attached) {
    }
    readert(const readert& copy): extends(copy) {
    }
    readert() {
    }
    virtual ~readert() {
        if (!(this->closed())) {
            LOGGER_IS_LOGGED_ERROR("...failed on this->closed() throw open_exception(close_failed)...");
            throw open_exception(close_failed);
        }
    }

    /// read...
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

    /// open...detached
    virtual attached_t open_safe_detached(const char* name, const sized_t* pattern, mode_t mode = mode_binary) const {
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
    virtual attached_t open_detached(const char* name, mode_t mode = mode_binary) const {
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
}; /// class readert

typedef readert<> reader;
typedef readert<io::char_reader> char_reader;

} /// namespace file
} /// namespace crt
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_CRT_FILE_READER_HPP 
