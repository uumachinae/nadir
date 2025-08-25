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
///   Date: 8/14/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_HEX_WRITER_TO_EVENTS_HPP
#define XOS_IO_HEX_WRITER_TO_EVENTS_HPP

#include "xos/io/delegated/reader.hpp"
#include "xos/base/logger.hpp"

namespace xos {
namespace io {
namespace hex {

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
    virtual ssize_t on_hex_digit(uint8_t d, what_t* what, size_t size, bool is_upper_case = false) {
        ssize_t count = (ssize_t)size;
        char_t c = 0;
        if (0 < (c = hex_char(d, is_upper_case))) {
            count = on_hex_char(c, what, size);
        }
        return count;
    }
    virtual ssize_t on_end_hex_digit(size_t size) {
        ssize_t count = (ssize_t)size;
        char_t c = ((char_t)'0');
        count = on_end_hex_char(c, size);
        return count;
    }
    virtual ssize_t on_hex_char(char_t c, what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }
    virtual ssize_t on_end_hex_char(char_t c, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }

    /// ...hex...
    inline char_t hex_char(uint8_t d, bool is_upper_case = false) const {
        char_t c = (char_t)(0);
        if ((0 <= d) && (9 >= d)) {
            c = (char_t)(('0') + d);
        } else {
            if ((10 <= d) && (15 >= d)) {
                c = (char_t)(((is_upper_case)?('A'):('a')) + (d - 10));
            } else {
                LOGGER_LOG_ERROR("...unecpected invalid_hex_digit(" << unsigned_to_string(d).chars() << ")");
            }
        }
        return c;
    }
}; /// class writer_to_eventst
typedef writer_to_eventst<> writer_to_events;

} /// namespace hex
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_HEX_WRITER_TO_EVENTS_HPP
