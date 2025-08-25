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
///   File: sequence.hpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_SEQUENCE_HPP
#define XOS_CONSOLE_SEQUENCE_HPP

#include "xos/base/locked.hpp"

namespace xos {
namespace console {

/// class sequencet
template 
<typename TChar = char, typename TFile = FILE*, 
 class TLocked = locked, class TImplements = TLocked>

class exported sequencet: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef sequencet derives; 
    
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
    virtual ~sequencet() {
    }

    /// dtox / xtod
    virtual char_t dtox(uint8_t d, bool upper_case = false) const {
        char a = (upper_case)?('A'):('a'); char_t x = (char_t)(0);
        if ((0 <= d) && (9 >= d)) {
            x = (char_t)(('0') +  d);
        } else {
            if ((10 <= d) && (15 >= d)) {
                x = (char_t)((a) + (d - 10));
            } else {
                x = invalid_dtox(d);
            }
        }
        return x;
    }
    virtual int8_t xtod(const char_t& x) const {
        int8_t d = -1;
        if (((char_t)('A') <= x) && ((char_t)('F') >= x)) {
            d = ((x - (char_t)('A')) + 10);
        } else {
            if (((char_t)('a') <= x) && ((char_t)('f') >= x)) {
                d = ((x - (char_t)('a')) + 10);
            } else  {
                if (((char_t)('0') <= x) && ((char_t)('9') >= x)) {
                    d = ((x - (char_t)('0')));
                } else {
                    d = invalid_xtod(x);
                }
            }
        }
        return d;
    }
    virtual char_t invalid_dtox(uint8_t d) const {
        return (char_t)(0);
    }
    virtual int8_t invalid_xtod(const char_t& x) const {
        return (int8_t)(-1);
    }

    /// ...dtob64 / ...b64tod
    virtual char_t dtob64(uint8_t d) const {
        char_t x = (char_t)(0);
        if ((0 <= d) && (25 >= d)) {
            x = (char_t)(('A') + d);
        } else {
            if ((26 <= d) && (51 >= d)) {
                x = (char_t)(('a') + (d - 26));
            } else {
                if ((52 <= d) && (61 >= d)) {
                    x = (char_t)(('0') + (d - 52));
                } else {
                    if ((62 == d)) {
                        x = (char_t)(('+'));
                    } else {
                        if ((63 == d)) {
                            x = (char_t)(('/'));
                        } else {
                            x = invalid_dtob64(d);
                        }
                    }
                }
            }
        }
        return x;
    }
    virtual int8_t b64tod(const char_t& x) const {
        int8_t d = (int8_t)(0);
        if (((char_t)('A') <= x) && ((char_t)('Z') >= x)) {
            d = (x - (char_t)('A'));
        } else {
            if (((char_t)('a') <= x) && ((char_t)('z') >= x)) {
                d = ((x - (char_t)('a')) + 26);
            } else {
                if (((char_t)('0') <= x) && ((char_t)('9') >= x)) {
                    d = ((x - (char_t)('0')) + 52);
                } else {
                    if (((char_t)('+') == x)) {
                        d = (62);
                    } else {
                        if (((char_t)('/') == x)) {
                            d = (63);
                        } else {
                            d = invalid_b64tod(x);
                        }
                    }
                }
            }
        }
        return d;
    }
    virtual char_t invalid_dtob64(uint8_t d) const {
        return (char_t)(0);
    }
    virtual int8_t invalid_b64tod(const char_t& x) const {
        return (int8_t)(-1);
    }

}; /// class sequencet
typedef sequencet<> sequence;

} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_SEQUENCE_HPP
