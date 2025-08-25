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
///   File: sequence.hpp
///
/// Author: $author$
///   Date: 3/10/2020, 8/6/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_SEQUENCE_HPP
#define XOS_IO_SEQUENCE_HPP

#include "xos/base/base.hpp"

namespace xos {
namespace io {

///  Class: sequencet
template 
<typename TWhat = char, typename TSized = TWhat,
 typename TEndof = TSized, TEndof VEndof = 0,
 class TImplements = implement>

class exported sequencet: virtual public TImplements {
public:
    typedef TImplements implements;
    
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TEndof endof_t;
    static const endof_t endof = VEndof;
    
};
typedef sequencet<void, char> sequence;

typedef sequencet<byte_t, byte_t> byte_sequence;
typedef sequencet<word_t, word_t> word_sequence;

///  Class: char_sequencet
template <class TChar = char, class TImplements = sequencet<TChar, TChar> >
class exported char_sequencet: virtual public TImplements {
public:
    typedef TImplements implements;

    typedef TChar char_t;
    typedef typename implements::what_t what_t;
    typedef typename implements::sized_t sized_t;
    typedef typename implements::endof_t endof_t;
    static const endof_t endof = implements::endof;

    ///
    /// ...dtox / ...xtod / ...
    /// ...
    virtual char_t dtox(uint8_t d, bool upper_case = false) const {
        const char a = (upper_case)?('A'):('a');
        char_t x = (char_t)(0);
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
        int8_t d = (int8_t)(0);
        if (((char_t)('A') <= x) && ((char_t)('F') >= x)) {
            d = ((x - (char_t)('A')) + 10);
        } else {
            if (((char_t)('a') <= x) && ((char_t)('f') >= x)) {
                d = ((x - (char_t)('a')) + 10);
            } else {
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
    /// ...
    /// ...dtox / ...xtod / ...
    ///

    ///
    /// ...dtob64 / ...b64tod / ...
    /// ...
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
    virtual bool is_end_b64tod(const char_t& c) const {
        switch ((char_t)c) {
        case '=':
            return true;
        }
        return false;
    }
    virtual char_t invalid_dtob64(uint8_t d) const {
        return (char_t)(0);
    }
    virtual int8_t invalid_b64tod(const char_t& x) const {
        return (int8_t)(-1);
    }
    /// ...
    /// ...dtob64 / ...b64tod / ...
    ///

}; /// class exported char_sequencet

typedef char_sequencet<char> char_sequence;
typedef char_sequencet<tchar_t> tchar_sequence;
typedef char_sequencet<wchar_t> wchar_sequence;

} /// namespace io
} /// namespace xos

#endif /// ndef XOS_IO_SEQUENCE_HPP 
