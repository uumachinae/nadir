///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2022 $organization$
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
///   File: writer_to_events.hpp
///
/// Author: $author$
///   Date: 8/3/2022, 8/19/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_BASE64_WRITER_TO_EVENTS_HPP
#define XOS_IO_BASE64_WRITER_TO_EVENTS_HPP

#include "xos/io/delegated/reader.hpp"
#include "xos/base/logger.hpp"

namespace xos {
namespace io {
namespace base64 {

/// class writer_to_eventst
template 
<class TReader = xos::io::reader, 
 class TReaderEvents = xos::io::delegated::reader_eventst<TReader>, class TImplements = TReaderEvents>
class exported writer_to_eventst: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef writer_to_eventst derives; 
    
    typedef char char_t;
    typedef TReader reader_t;
    typedef typename reader_t::what_t what_t;
    typedef typename reader_t::sized_t sized_t;

    /// constructors / destructor
    virtual ~writer_to_eventst() {
    }

    /// on...
    virtual ssize_t on_begin(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }
    virtual ssize_t on_base64_digit(uint8_t d, what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        char_t c = 0;
        if (0 < (c = base64_char(d))) {
            count = on_base64_char(c, what, size);
        }
        return count;
    }
    virtual ssize_t on_end_base64_digit(size_t size) {
        ssize_t count = (ssize_t)size;
        char_t c = ((char_t)'=');
        count = on_end_base64_char(c, size);
        return count;
    }
    virtual ssize_t on_base64_char(char_t c, what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }
    virtual ssize_t on_end_base64_char(char_t c, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }

    /// ...base64...
    inline char_t base64_char(uint8_t d) const {
        char_t c = (char_t)(0);
        if ((0 <= d) && (25 >= d)) {
            c = (char_t)(('A') + d);
        } else {
            if ((26 <= d) && (51 >= d)) {
                c = (char_t)(('a') + (d - 26));
            } else {
                if ((52 <= d) && (61 >= d)) {
                    c = (char_t)(('0') + (d - 52));
                } else {
                    if ((62 == d)) {
                        c = (char_t)(('+'));
                    } else {
                        if ((63 == d)) {
                            c = (char_t)(('/'));
                        } else {
                            LOGGER_LOG_ERROR("...unecpected invalid_base64_digit(" << unsigned_to_string(d).chars() << ")");
                        }
                    }
                }
            }
        }
        return c;
    }
}; /// class writer_to_eventst

} /// namespace base64
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_BASE64_WRITER_TO_EVENTS_HPP
