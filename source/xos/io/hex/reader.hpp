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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 4/17/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_HEX_READER_HPP
#define XOS_IO_HEX_READER_HPP

#include "xos/io/delegated/reader.hpp"
#include "xos/base/logger.hpp"

namespace xos {
namespace io {
namespace hex {

/// class reader_eventst
template 
<class TReader = xos::io::char_reader, 
 class TReaderEvents = xos::io::delegated::reader_eventst<TReader>, class TImplements = TReaderEvents>
class exported reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements, implements;
    typedef reader_eventst Derives, derives; 
    
    typedef TReader reader_t;
    typedef typename reader_t::what_t what_t;
    typedef typename reader_t::sized_t sized_t;

    /// constructors / destructor
    virtual ~reader_eventst() {
    }

    /// on...
    virtual ssize_t on_begin(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        return size;
    }
    virtual ssize_t on_hex_char(what_t* what, size_t size) {
        sized_t* sized = 0;

        if ((sized = ((sized_t*)what))) {
            char c = ((char)(*sized));

            if ((c >= '0') && (c <= '9')) {
                return on_hex_digit((c - '0'), what, size);
            } else {
                if ((c >= 'a') && (c <= 'f')) {
                    return on_hex_digit(((c - 'a') + 10), what, size);
                } else {
                    if ((c >= 'A') && (c <= 'F')) {
                        return on_hex_digit(((c - 'A') + 10), what, size);
                    } else {
                    }
                }
            }
        }
        return size;
    }
    virtual ssize_t on_hex_digit(unsigned d, what_t* what, size_t size) {
        return size;
    }

}; /// class reader_eventst
typedef reader_eventst<> reader_events;

/// class readert
template 
<class TReader = xos::io::char_reader, 
 class TReaderEvents = xos::io::hex::reader_eventst<TReader>, 
 class TReaderExtend = xos::io::delegated::readert<TReader, TReaderEvents>, 
 class TExtends = TReaderExtend, class TImplements = TReaderEvents>

class exported readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements, implements;
    typedef TExtends Extends, extends;
    typedef readert Derives, derives; 
    
    typedef TReader reader_t;
    typedef TReaderEvents reader_events_t;
    typedef typename Extends::what_t what_t;
    typedef typename Extends::sized_t sized_t;

    /// constructors / destructor
    readert(const readert& copy): extends(copy), on_read_(0), reader_events_(copy.reader_events_) {
    }
    readert(reader_events_t& reader_events, reader_t& reader): extends(reader), on_read_(0), reader_events_(reader_events) {
    }
    readert(reader_t& reader): extends(reader), on_read_(0), reader_events_(*this) {
    }
    virtual ~readert() {
    }

    /// on...
    virtual ssize_t on_begin(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_begin(what, size);
        }
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_end(what, size);
        }
        return size;
    }
    virtual ssize_t on_hex_char(what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_hex_char(what, size);
        }
        return size;
    }
    virtual ssize_t on_hex_digit(unsigned d, what_t* what, size_t size) {
        if (&reader_events_ != this) {
            return reader_events_.on_hex_digit(d, what, size);
        }
        return size;
    }

    /// on_read...
    ssize_t (Derives::*on_read_)(what_t* what, size_t size);
    virtual ssize_t on_read(what_t* what, size_t size) {
        ssize_t count = size;
        if ((on_read_)) {
            (this->*on_read_)(what, size);
        } else {
            this->on_read_begin(what, size);
        }
        return count;
    }
    virtual ssize_t on_read_begin(what_t* what, size_t size) {
        ssize_t count = size;
        sized_t* sized = 0;
        char c = 0;
        if ((sized = ((sized_t*)what))) {
            if (is_hex_char(c = ((char)(*sized)))) {
                LOGGER_LOG_DEBUG("this->on_begin(what = " << char_to_string(c) << ")...");
                this->on_begin(what, size);
                this->on_hex_char(what, size);
                on_read_ = &Derives::on_read_hex;
            } else {
                if ((!is_nextln_char(c)) && (!is_ws_char(c))) {
                    LOGGER_LOG_DEBUG("this->on_end(what = " << char_to_string(c) << ")...");
                    this->on_end(what, size);
                    on_read_ = &Derives::on_read_begin;
                }
            }
        }
        return count;
    }
    virtual ssize_t on_read_nextln(what_t* what, size_t size) {
        ssize_t count = size;
        sized_t* sized = 0;
        char c = 0;
        if ((sized = ((sized_t*)what))) {
            if (is_hex_char(c = ((char)(*sized)))) {
                this->on_hex_char(what, size);
                on_read_ = &Derives::on_read_hex;
            } else {
                if ((!is_nextln_char(c)) && (!is_ws_char(c))) {
                    LOGGER_LOG_DEBUG("this->on_end(what = " << char_to_string(c) << ")...");
                    this->on_end(what, size);
                    on_read_ = &Derives::on_read_begin;
                }
            }
        }
        return count;
    }
    virtual ssize_t on_read_hex(what_t* what, size_t size) {
        ssize_t count = size;
        sized_t* sized = 0;
        char c = 0;
        if ((sized = ((sized_t*)what))) {
            if (is_hex_char(c = ((char)(*sized)))) {
                this->on_hex_char(what, size);
            } else {
                if ((!is_nextln_char(c))) {
                    LOGGER_LOG_DEBUG("this->on_end(what = " << char_to_string(c) << ")...");
                    this->on_end(what, size);
                    on_read_ = &Derives::on_read_begin;
                } else {
                    on_read_ = &Derives::on_read_nextln;
                }
            }
        }
        return count;
    }

    /// ...hex...
    inline unsigned hex_digit(char c) const {
        if ((c >= '0') && (c <= '9')) {
            return (c - '0');
        } else {
            if ((c >= 'a') && (c <= 'f')) {
                return (c - 'a') + 10;
            } else {
                if ((c >= 'A') && (c <= 'F')) {
                    return (c - 'A') + 10;
                } else {
                }
            }
        }
        return 0;
    }
    inline bool is_hex_char(char c) const {
        if (((c >= '0') && (c <= '9'))
            || ((c >= 'a') && (c <= 'f'))
            || ((c >= 'A') && (c <= 'F'))) {
            return true;
        }
        return false;
    }
    inline bool is_nextln_char(char c) const {
        switch (c) {
        case '\\':
            return true;
        }
        return false;
    }
    inline bool is_ws_char(char c) const {
        switch (c) {
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            return true;
        }
        return false;
    }

protected:
    reader_events_t& reader_events_;
}; /// class readert
typedef readert<> reader;

} /// namespace hex
} /// namespace io
} /// namespace xos

#endif /// XOS_IO_HEX_READER_HPP
