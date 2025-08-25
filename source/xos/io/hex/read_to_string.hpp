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
///   File: read_to_string.hpp
///
/// Author: $author$
///   Date: 12/3/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_HEX_READ_TO_STRING_HPP
#define XOS_IO_HEX_READ_TO_STRING_HPP

#include "xos/io/hex/reader_to.hpp"

namespace xos {
namespace io {
namespace hex {

/// class read_to_stringt
template 
<class TString = xos::string,
 class TReader = xos::io::reader,
 class TReaderEvents = xos::io::hex::reader_to_eventst<TReader>, 
 class TExtends = extend, class TImplements = TReaderEvents>

class exported read_to_stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef read_to_stringt derives; 
    
    typedef TString string_t;
    typedef typename string_t::char_t char_t;
    typedef TReader reader_t;
    typedef TReaderEvents reader_events_t;
    typedef typename reader_events_t::what_t what_t;
    typedef typename reader_events_t::sized_t sized_t;

    /// constructors / destructor
    read_to_stringt(const read_to_stringt& copy)
    : string_(copy.string_), is_lower_hex_digit_(false), upper_hex_digit_(0) {
    }
    read_to_stringt(string_t &string)
    : string_(string), is_lower_hex_digit_(false), upper_hex_digit_(0) {
    }
    virtual ~read_to_stringt() {
    }

    /// on...
    virtual ssize_t on_begin(what_t* what, size_t size) {
        string_t &string = this->string();
        string.clear();
        is_lower_hex_digit_ = false;
        return size;
    }
    virtual ssize_t on_end(what_t* what, size_t size) {
        string_t &string = this->string();
        is_lower_hex_digit_ = false;
        return size;
    }
    virtual ssize_t on_hex_digit(uint8_t d, what_t* what, size_t size) {
        string_t &string = this->string();

        if ((is_lower_hex_digit_)) {
            char_t c = (char_t)(((upper_hex_digit_ & 0xff) << 4) | (d & 0xff));

            string.append(&c, 1);
            is_lower_hex_digit_ = false;
        } else {
            upper_hex_digit_ = d;
            is_lower_hex_digit_ = true;
        }
        return size;
    }

    /// string
    virtual string_t &string() const {
        return (string_t &)string_;
    }

protected:
    string_t &string_;
    bool is_lower_hex_digit_;
    uint8_t upper_hex_digit_;
}; /// class read_to_stringt
typedef read_to_stringt<> read_to_string;

} /// namespace hex
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_HEX_READ_TO_STRING_HPP
