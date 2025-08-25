///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: to_string.hpp
///
/// Author: $author$
///   Date: 2/18/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_TO_STRING_HPP
#define _NADIR_BASE_TO_STRING_HPP

#include "nadir/base/string.hpp"

namespace nadir {

///////////////////////////////////////////////////////////////////////
///  Class: chars_to_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = char_stringt<TChar> >

class _EXPORT_CLASS chars_to_stringt: public TExtends {
public:
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    chars_to_stringt(const char* chars) {
        if (chars) {
            this->append("\"");
            this->append(chars);
            this->append("\"");
        } else {
            this->append("0");
        }
    }
    chars_to_stringt(const wchar_t* chars) {
        if (chars) {
            this->append("\"");
            this->append(chars);
            this->append("\"");
        } else {
            this->append("0");
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef chars_to_stringt<char> chars_to_string;
typedef chars_to_stringt<tchar_t> chars_to_tstring;
typedef chars_to_stringt<wchar_t> chars_to_wstring;

///////////////////////////////////////////////////////////////////////
///  Class: bool_to_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = char_stringt<TChar> >

class _EXPORT_CLASS bool_to_stringt: public TExtends {
public:
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    bool_to_stringt(bool to) {
        this->append_bool(to);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef bool_to_stringt<char> bool_to_string;
typedef bool_to_stringt<tchar_t> bool_to_tstring;
typedef bool_to_stringt<wchar_t> bool_to_wstring;

///////////////////////////////////////////////////////////////////////
///  Class: int_to_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = char_stringt<TChar> >

class _EXPORT_CLASS int_to_stringt: public TExtends {
public:
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int_to_stringt(int to) {
        this->append_int(to);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef int_to_stringt<char> int_to_string;
typedef int_to_stringt<tchar_t> int_to_tstring;
typedef int_to_stringt<wchar_t> int_to_wstring;

///////////////////////////////////////////////////////////////////////
///  Class: signed_to_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = char_stringt<TChar> >

class _EXPORT_CLASS signed_to_stringt: public TExtends {
public:
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    signed_to_stringt(signed to) {
        this->append_signed(to);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef signed_to_stringt<char> signed_to_string;
typedef signed_to_stringt<tchar_t> signed_to_tstring;
typedef signed_to_stringt<wchar_t> signed_to_wstring;

///////////////////////////////////////////////////////////////////////
///  Class: unsigned_to_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = char_stringt<TChar> >

class _EXPORT_CLASS unsigned_to_stringt: public TExtends {
public:
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_to_stringt(unsigned to) {
        this->append_unsigned(to);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef unsigned_to_stringt<char> unsigned_to_string;
typedef unsigned_to_stringt<tchar_t> unsigned_to_tstring;
typedef unsigned_to_stringt<wchar_t> unsigned_to_wstring;

///////////////////////////////////////////////////////////////////////
///  Class: pointer_to_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 class TExtends = char_stringt<TChar> >

class _EXPORT_CLASS pointer_to_stringt: public TExtends {
public:
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    pointer_to_stringt(pointer_t to) {
        this->append_pointer(to);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef pointer_to_stringt<char> pointer_to_string;
typedef pointer_to_stringt<tchar_t> pointer_to_tstring;
typedef pointer_to_stringt<wchar_t> pointer_to_wstring;

} // namespace nadir

#endif // _NADIR_BASE_TO_STRING_HPP 
