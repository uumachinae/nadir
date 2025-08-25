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
///   File: writer_to.hpp
///
/// Author: $author$
///   Date: 8/4/2022, 8/19/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_BASE64_WRITER_TO_HPP
#define XOS_IO_BASE64_WRITER_TO_HPP

#include "xos/io/base64/writer_to_events.hpp"

namespace xos {
namespace io {
namespace base64 {

/// class writer_tot
template 
<class TReader = xos::io::reader, 
 class TWriterEvents = xos::io::base64::writer_to_eventst<TReader>, 
 class TWriterExtend = xos::io::delegated::readert<TReader, TWriterEvents>, 
 class TExtends = TWriterExtend, class TImplements = TWriterEvents>

class exported writer_tot: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef writer_tot derives; 
    
    typedef char char_t;
    typedef TReader reader_t;
    typedef TWriterEvents writer_events_t;
    typedef typename extends::what_t what_t;
    typedef typename extends::sized_t sized_t;

    /// constructors / destructor
    writer_tot(writer_events_t& writer_events, reader_t& reader)
    : extends(reader), writer_events_(writer_events), shift_(2), carry_(0), digit_(0) {
    }
    writer_tot(reader_t& reader): extends(reader), writer_events_(*this), shift_(2), carry_(0), digit_(0) {
    }
    writer_tot(const writer_tot& copy): extends(copy), writer_events_(copy.writer_events_), shift_(2), carry_(0), digit_(0) {
    }
    virtual ~writer_tot() {
    }

    /// on...base64...
    virtual ssize_t on_base64_digit(uint8_t d, what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_base64_digit(d, what, size);
        }
        return count;
    }
    virtual ssize_t on_end_base64_digit(size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_end_base64_digit(size);
        }
        return count;
    }
    virtual ssize_t on_base64_char(char_t c, what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_base64_char(c, what, size);
        }
        return count;
    }
    virtual ssize_t on_end_base64_char(char_t c, size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_end_base64_char(c, size);
        }
        return count;
    }

    /// on_begin / on_end / on_read
    virtual ssize_t on_begin(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        uint8_t &shift = shift_, &carry = carry_;
        shift = 2; carry = 0;
        return count;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        uint8_t &shift = shift_, &carry = carry_, &digit = digit_;
        if (4 == (shift)) {
            digit = ((carry << 4)); /// 6 bits
            carry = 0;
            shift = 2;
            count = on_base64_digit(digit, what, 1);
            count += on_end_base64_digit(1);
            count += on_end_base64_digit(1);
        } else {
            if (6 == (shift)) {
                digit = ((carry << 2)); /// 6 bits
                carry = 0;
                shift = 2;
                count = on_base64_digit(digit, what, 1);
                count += on_end_base64_digit(1);
            }
        }
        return count;
    }
    virtual ssize_t on_read(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what)) && (0 < (size))) {
            uint8_t &shift = shift_, &carry = carry_, &digit = digit_, b = 0;
            do {
                what = ((what_t*)sized);
                b = ((uint8_t)(*sized++));
                if (2 == (shift)) {
                    digit = ((b) >> 2); /// 6 bits
                    carry = (((b) & 0x3)); /// 2 bits 
                    shift = 4;
                    count = on_base64_digit(digit, what, 1);
                } else {
                    if (4 == (shift)) {
                        digit = (((b) >> 4) | (carry << 4)); /// 6 bits
                        carry = ((((b) & 0xF))); /// 4 bits
                        shift = 6;
                        count = on_base64_digit(digit, what, 1);
                    } else {
                        if (6 == (shift)) {
                            digit = (((b) >> 6) | (carry << 2)); /// 6 bits
                            carry = ((b) & 0x3F); /// 6 bits
                            shift = 2;
                            count = on_base64_digit(digit, what, 1);
                            count += on_base64_digit(carry, what, 1);
                        } else {
                            LOGGER_LOG_ERROR("...unecpected invalid_shift(" << unsigned_to_string(shift).chars() << ")");
                        }
                    }
                }
            } while (0 < (--size));
        }
        return count;
    }

protected:
    writer_events_t& writer_events_;
    uint8_t shift_, carry_, digit_;
}; /// class writer_tot
typedef writer_tot<> writer_to;

} /// namespace base64
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_BASE64_WRITER_TO_HPP
