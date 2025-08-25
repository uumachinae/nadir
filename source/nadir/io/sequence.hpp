///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   Date: 12/20/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_SEQUENCE_HPP
#define _NADIR_IO_SEQUENCE_HPP

#include "nadir/base/base.hpp"

namespace nadir {
namespace io {

typedef implement_base sequence_implement;
///////////////////////////////////////////////////////////////////////
///  Class: sequencet
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = char, typename TEnd = int, TEnd VEnd = 0,
 class TImplements = sequence_implement>

class _EXPORT_CLASS sequencet: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TWhat what_t;
    typedef TWhat char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t dtox(uint8_t d, bool upper_case = false) const {
        char a = (upper_case)?('A'):('a');
        char_t x = (char_t)(0);
        if ((0 <= d) && (9 >= d))
            x = (char_t)(('0') +  d);
        else
        if ((10 <= d) && (15 >= d))
            x = (char_t)((a) + (d - 10));
        return x;
    }
    virtual int8_t xtod(const char_t& x) const {
        int8_t d = -1;
        if (((char_t)('A') <= x) && ((char_t)('F') >= x))
            d = ((x - (char_t)('A')) + 10);
        else
        if (((char_t)('a') <= x) && ((char_t)('f') >= x))
            d = ((x - (char_t)('a')) + 10);
        else
        if (((char_t)('0') <= x) && ((char_t)('9') >= x))
            d = ((x - (char_t)('0')));
        return d;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef sequencet<> sequence;
typedef sequencet<byte_t> byte_sequence;
typedef sequencet<char_t> char_sequence;
typedef sequencet<wchar_t> wchar_sequence;
typedef sequencet<tchar_t> tchar_sequence;

} /// namespace io
} /// namespace nadir

#endif /// ndef _NADIR_IO_SEQUENCE_HPP
