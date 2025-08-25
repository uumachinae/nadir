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
///   File: out.hpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_OUT_HPP
#define XOS_CONSOLE_OUT_HPP

#include "xos/console/sequence.hpp"
#include "xos/base/logger.hpp"

namespace xos {
namespace console {

ssize_t outlln(file_t f, const char *what, ...);
ssize_t outllnv(file_t f, const char *what, va_list va);
ssize_t outl(file_t f, const char *what, ...);
ssize_t outlv(file_t f, const char *what, va_list va);
ssize_t outf(file_t f, const char *format, ...);
ssize_t outfv(file_t f, const char *format, va_list va);
ssize_t outln(file_t f, const char *what, size_t length);
ssize_t outln(file_t f, const char *what);
ssize_t out(file_t f, const char *what, size_t length);
ssize_t out(file_t f, const char *what);
ssize_t outln(file_t f);
ssize_t out_flush(file_t f);

/// class outt
template 
<typename TChar = char, typename TFile = FILE*, class TLocked = locked, 
 class TSequence = xos::console::sequencet<TChar, TFile, TLocked>, 
 class TImplements = TSequence>

class exported outt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef outt derives; 
    
    typedef TFile file_t;
    typedef int null_file_t;
    enum { null_file = 0 };

    typedef stringt<TChar> string_t;
    typedef TChar char_t;
    typedef char_t end_char_t;
    enum { end_char = 0 };

    typedef char_t what_t;
    typedef char_t sized_t;
    
    /// constructors / destructor
    virtual ~outt() {
    }

protected:
    /// out...x...
    /// ...
    /// outx...
    virtual ssize_t outxln(file_t f, const void* out, size_t length, bool upper_case = false) const {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->outx(f, out, length, upper_case))) {
            count += amount;
            if (0 <= (amount = console::outln(f))) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t outx(file_t f, const void* out, size_t length, bool upper_case = false) const {
        ssize_t count = 0; const uint8_t* bytes = 0;

        if ((bytes = (const uint8_t*)(out)) && (length)) {
            ssize_t amount = 0; uint8_t b = 0; char_t x[2];

            for (; 0 < length; --length) {
                b = (*bytes++);
                x[0] =  this->dtox(b >> 4, upper_case);
                x[1] =  this->dtox(b & 15, upper_case);

                if (0 < (amount = console::out(f, x, 2))) {
                    count += amount;
                } else {
                    return amount;
                }
            }
        }
        return count;
    }
    /// out0x...
    virtual ssize_t out0xln(file_t f, const void* out, size_t length, bool upper_case = false) const {
        ssize_t count = 0, amount = 0;
        if (0 <= (amount = this->out0x(f, out, length, upper_case))) {
            count += amount;
            if (0 <= (amount = console::outln(f))) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t out0x(file_t f, const void* out, size_t length, bool upper_case = false) const {
        ssize_t count = 0; const uint8_t* bytes = 0;

        if ((bytes = (const uint8_t*)(out)) && (length)) {
            ssize_t amount = 0; uint8_t b = 0; 
            char_t ox[5], *ix = (ox + 1), *x = (ox + 3);

            ox[0] = ','; ox[1] = '0'; ox[2] = (upper_case)?('X'):('x');
            for (size_t n = (sizeof(ox) - 1); 0 < length; --length) {
                b = (*bytes++);
                x[0] =  this->dtox(b >> 4, upper_case);
                x[1] =  this->dtox(b & 15, upper_case);

                if (0 < (amount = console::out(f, ix, n))) {
                    count += amount;
                    if ((n < sizeof(ox))) {
                        n = sizeof(ox);
                        ix = ox;
                    }
                } else {
                    return amount;
                }
            }
        }
        return count;
    }
    /// ...
    /// out...x..

    /// out64...
    /// ...
    virtual ssize_t out64ln(file_t f, const void* out, size_t length) {
        ssize_t count = 0, amount = 0;

        if (0 <= (amount = this->out64(f, out, length))) {
            count += amount;
            if (0 <= (amount = console::outln(f))) {
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t out64(file_t f, const void* out, size_t length) {
        ssize_t count = 0;
        const uint8_t* byte = 0;

        if ((byte = (const uint8_t*)(out)) && (length)) {
            ssize_t amount = 0;
            uint8_t b = 0, carry = 0, shift = 0;
            if (0 <= length) {
                for (carry = 0, shift = 2; 0 < length; --length, ++byte) {
                    b = (*byte);
                    if (0 > (amount = this->put64(f, b, carry, shift))) {
                        return amount;
                    }
                    count += amount;
                }
            } else {
                for (carry = 0, shift = 2; (b = (*byte)); ++byte) {
                    if (0 > (amount = this->put64(f, b, carry, shift))) {
                        return amount;
                    }
                    count += amount;
                }
            }
            if ((2 != (shift))) {
                if (0 > (amount = this->put64_end(f, carry, shift))) {
                    return amount;
                }
                count += amount;
            }
        }
        return count;
    }
    virtual ssize_t put64(file_t f, uint8_t b, uint8_t& carry, uint8_t& shift) {
        ssize_t count = 0, amount = 0;
        sized_t sized = 0;
        uint8_t digit = 0;
        if (2 == (shift)) {
            digit = ((b) >> 2); /// 6 bits
            carry = (((b) & 0x3)); /// 2 bits 
            shift = 4;
            sized = (sized_t)(this->dtob64(digit));
            if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                return amount;
            }
            count += amount;            
        } else {
            if (4 == (shift)) {
                digit = (((b) >> 4) | (carry << 4)); /// 6 bits
                carry = ((((b) & 0xF))); /// 4 bits
                shift = 6;
                sized = (sized_t)(this->dtob64(digit));
                if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                    return amount;
                }
                count += amount;            
            } else {
                if (6 == (shift)) {
                    digit = (((b) >> 6) | (carry << 2)); /// 6 bits
                    carry = ((b) & 0x3F); /// 6 bits
                    shift = 2;
                    sized = (sized_t)(this->dtob64(digit));
                    if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                        return amount;
                    }
                    count += amount;            
                    sized = (sized_t)(this->dtob64(carry));
                    if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                        return amount;
                    }
                    count += amount;            
                } else {
                    LOGGER_LOG_ERROR("...unecpected invalid_shift(" << unsigned_to_string(shift).chars() << ")");
                }
            }
        }
        return count;
    }
    virtual ssize_t put64_end(file_t f, uint8_t& carry, uint8_t& shift) {
        ssize_t count = 0, amount = 0;
        sized_t sized = 0;
        uint8_t digit = 0;
        if (4 == (shift)) {
            digit = ((carry << 4)); /// 6 bits
            carry = 0;
            shift = 2;
            sized = (sized_t)(this->dtob64(digit));
            if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                return amount;
            }
            count += amount;
            sized = ((sized_t)'=');
            if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                return amount;
            }
            count += amount;            
            if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                return amount;
            }
            count += amount;            
        } else {
            if (6 == (shift)) {
                digit = ((carry << 2)); /// 6 bits
                carry = 0;
                shift = 2;
                sized = (sized_t)(this->dtob64(digit));
                if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                    return amount;
                }
                count += amount;            
                sized = ((sized_t)'=');
                if (0 > (amount = console::out(f, (const what_t*)(&sized), 1))) {
                    return amount;
                }
                count += amount;            
            }
        }
        return count;
    }

}; /// class outt

} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_OUT_HPP
