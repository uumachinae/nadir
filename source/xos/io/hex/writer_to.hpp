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
///   Date: 8/14/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_HEX_WRITER_TO_HPP
#define XOS_IO_HEX_WRITER_TO_HPP

#include "xos/io/hex/writer_to_events.hpp"

namespace xos {
namespace io {
namespace hex {

/// class writer_tot
template 
<class TReader = xos::io::reader, 
 class TWriterEvents = xos::io::hex::writer_to_eventst<TReader>, 
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
    : extends(reader), writer_events_(writer_events) {
    }
    writer_tot(reader_t& reader)
    : extends(reader), writer_events_(*this) {
    }
    writer_tot(const writer_tot& copy)
    : extends(copy), writer_events_(copy.writer_events_) {
    }
    virtual ~writer_tot() {
    }

    /// on...hex...
    virtual ssize_t on_hex_digit(uint8_t d, what_t* what, size_t size, bool is_upper_case = false) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_hex_digit(d, what, size, is_upper_case);
        }
        return count;
    }
    virtual ssize_t on_end_hex_digit(size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_end_hex_digit(size);
        }
        return count;
    }
    virtual ssize_t on_hex_char(char_t c, what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_hex_char(c, what, size);
        }
        return count;
    }
    virtual ssize_t on_end_hex_char(char_t c, size_t size) {
        ssize_t count = (ssize_t)size;
        if (&writer_events_ != this) {
            return writer_events_.on_end_hex_char(c, size);
        }
        return count;
    }

    /// on_begin / on_end / on_read
    virtual ssize_t on_begin(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        return count;
    }
    virtual ssize_t on_read(what_t* what, size_t size) {
        ssize_t count = (ssize_t)size;
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what)) && (0 < (size))) {
            uint8_t msn = 0, lsn = 0, b = 0;
            do {
                what = ((what_t*)sized);
                b = ((uint8_t)(*sized++));
                msn = ((b) >> 4); /// 4 bits
                lsn = (((b) & 0xF)); /// 4 bits 
                count = on_hex_digit(msn, what, 1);
                count += on_hex_digit(lsn, what, 1);
            } while (0 < (--size));
        }
        return count;
    }

protected:
    writer_events_t& writer_events_;
}; /// class writer_tot
typedef writer_tot<> writer_to;

} /// namespace hex
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_HEX_WRITER_TO_HPP
