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
///   File: output_to.hpp
///
/// Author: $author$
///   Date: 7/31/2022, 8/4/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_BASE64_OUTPUT_TO_HPP
#define XOS_IO_BASE64_OUTPUT_TO_HPP

#include "xos/base/base.hpp"

namespace xos {
namespace io {
namespace base64 {

/// class output_tot
template <class TTo, class TExtends = extend, class TImplements = implement>
class exported output_tot: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef output_tot derives; 
    
    typedef TTo to_t;
    typedef char char_t;
    
    /// constructors / destructor
    output_tot(const output_tot& copy): to_(copy.to_), byte_(0), carry_(0), shift_(2) {
    }
    output_tot(to_t& to): to_(to), byte_(0), carry_(0), shift_(2) {
    }
    virtual ~output_tot() {
    }

    /// ...out_base64_char...
    virtual ssize_t begin_out_base64_chars() {
        to_t &to = to_;
        return to.flush();
    }
    virtual ssize_t end_out_base64_chars() {
        to_t &to = to_;
        return to.flush();
    }
    virtual ssize_t out_base64_char(char_t c) {
        to_t &to = to_;
        return to.put(c);
    }

    /// ...out_base64_digit...
    virtual ssize_t begin_out_base64_digits() {
        to_t &to = to_;
        uint8_t &carry = carry_, &shift = shift_;
        carry = 0; shift = 2;
        return to.flush();
    }
    virtual ssize_t end_out_base64_digits() {
        to_t &to = to_;
        uint8_t &carry = carry_, &shift = shift_;
        carry = 0; shift = 2;
        return to.flush();
    }
    virtual ssize_t end_out_base64_digit(uint8_t d) {
        to_t &to = to_;
        uint8_t &carry = carry_, &shift = shift_, byte = ((uint8_t)d);
        to.put(byte);
        carry = 0; shift = 2;
        return to.flush();
    }
    virtual ssize_t out_base64_digit(uint8_t d) {
        to_t &to = to_;
        uint8_t &byte = byte_, &carry = carry_, &shift = shift_, b = ((uint8_t)d);
        if (2 == (shift)) {
            byte = ((b) << 2); /// 6 bits
            carry = 0; /// 0 bits 
            shift = 4;
        } else {
            if (4 == (shift)) {
                byte |= ((b) >> 4); /// 8 bits
                carry = ((((b) & 0xF)) << 4); /// 4 bits
                shift = 6;
                return to.put(byte);
            } else {
                if (6 == (shift)) {
                    byte = (carry | ((b) >> 2)); /// 8 bits
                    carry = ((((b) & 0x3)) << 6); /// 2 bits 
                    shift = 8;
                    return to.put(byte);
                } else {
                    if (8 == (shift)) {
                        byte = (carry | (b)); /// 8 bits
                        carry = 0; /// 0 bits 
                        shift = 2;
                        return to.put(byte);
                    } else {
                    }
                }
            }
        }
        return 0;
    }

protected:
    to_t& to_;
    uint8_t byte_, carry_, shift_;
}; /// class output_tot

} /// namespace base64
} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_BASE64_OUTPUT_TO_HPP
