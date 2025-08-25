///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: string.hpp
///
/// Author: $author$
///   Date: 9/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_STRING_HPP
#define _NADIR_BASE_STRING_HPP

#include "nadir/base/to_char.hpp"
#include "nadir/base/chars.hpp"
#include <sstream>
#include <string>

namespace nadir {

typedef implement_base stringt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: char_stringt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TEnd = TChar, TEnd VEnd = 0,
 class TChars = charst<TChar, TEnd, VEnd>,
 class TCharTo = to_chart<TChar, char>,
 class TWCharTo = to_chart<TChar, wchar_t>,
 class TSStream = ::std::basic_stringstream<TChar>,
 class TString = ::std::basic_string<TChar>,
 class TImplements = TChars, class TExtends = TString>

class _EXPORT_CLASS char_stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TChars chars_t;
    typedef TCharTo char_to;
    typedef TWCharTo wchar_to;
    typedef TSStream sstream_t;
    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    static const end_t endof = VEnd;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    char_stringt(const char* chars) {
        this->append(chars);
    }
    char_stringt(const char* chars, size_t length) {
        this->append(chars, length);
    }
    char_stringt(const char* chars, const char* vchars, ...) {
        this->append(chars);
        if (vchars) {
            va_list va; va_start(va, vchars);
            appendv(vchars, va);
            va_end(va);
        }
    }
    char_stringt(const wchar_t* chars) {
        this->append(chars);
    }
    char_stringt(const wchar_t* chars, size_t length) {
        this->append(chars, length);
    }
    char_stringt(const wchar_t* chars, const wchar_t* vchars, ...) {
        this->append(chars);
        if (vchars) {
            va_list va; va_start(va, vchars);
            appendv(vchars, va);
            va_end(va);
        }
    }
    char_stringt(const unsigned_t& c) {
        this->append_unsigned(c);
    }
    char_stringt(const signed_t& c) {
        this->append_signed(c);
    }
    char_stringt(const bool& c) {
        this->append_bool(c);
    }
    char_stringt(const Extends& copy): Extends(copy) {
    }
    char_stringt(const char_stringt& copy): Extends(copy) {
    }
    char_stringt() {
    }
    virtual ~char_stringt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& assign(const char_stringt& s) {
        this->clear();
        return append(s);
    }
    virtual char_stringt& assign(const char& c) {
        this->clear();
        return append(c);
    }
    virtual char_stringt& assign(const char* chars) {
        this->clear();
        return append(chars);
    }
    virtual char_stringt& assign(const char* chars, size_t length) {
        this->clear();
        return append(chars, length);
    }
    virtual char_stringt& assignl(const char* chars, ...) {
        va_list va; va_start(va, chars);
        assignv(chars, va);
        va_end(va);
        return *this;
    }
    virtual char_stringt& assignv(const char* chars, va_list va) {
        this->clear();
        return appendv(chars, va);
    }
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& assign(const wchar_t& c) {
        this->clear();
        return append(c);
    }
    virtual char_stringt& assign(const wchar_t* chars) {
        this->clear();
        return append(chars);
    }
    virtual char_stringt& assign(const wchar_t* chars, size_t length) {
        this->clear();
        return append(chars, length);
    }
    virtual char_stringt& assignl(const wchar_t* chars, ...) {
        va_list va; va_start(va, chars);
        assignv(chars, va);
        va_end(va);
        return *this;
    }
    virtual char_stringt& assignv(const wchar_t* chars, va_list va) {
        this->clear();
        return appendv(chars, va);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& append(const char_stringt& s) {
        return append(s.chars());
    }
    virtual char_stringt& append(const char& c) {
        return append(&c, 1);
    }
    virtual char_stringt& append(const char* chars) {
        if ((chars) && (*chars)) {
            char_to to;
            for (; *chars; ++chars) {
                Extends::append(to.transcode(*chars));
            }
        }
        return *this;
    }
    virtual char_stringt& append(const char* chars, size_t length) {
        if ((chars) && (length)) {
            char_to to;
            for (; length; --length, ++chars) {
                Extends::append(to.transcode(*chars));
            }
        }
        return *this;
    }
    virtual char_stringt& appendl(const char* chars, ...) {
        va_list va; va_start(va, chars);
        appendv(chars, va);
        va_end(va);
        return *this;
    }
    virtual char_stringt& appendv(const char* chars, va_list va) {
        if ((chars)) {
            do { append(chars);
            } while ((chars = va_arg(va, const char*)));
        }
        return *this;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& append(const wchar_t& c) {
        return append(&c, 1);
    }
    virtual char_stringt& append(const wchar_t* chars) {
        if ((chars) && (*chars)) {
            wchar_to to;
            for (; *chars; ++chars) {
                Extends::append(to.transcode(*chars));
            }
        }
        return *this;
    }
    virtual char_stringt& append(const wchar_t* chars, size_t length) {
        if ((chars) && (length)) {
            wchar_to to;
            for (; length; --length, ++chars) {
                Extends::append(to.transcode(*chars));
            }
        }
        return *this;
    }
    virtual char_stringt& appendl(const wchar_t* chars, ...) {
        va_list va; va_start(va, chars);
        appendv(chars, va);
        va_end(va);
        return *this;
    }
    virtual char_stringt& appendv(const wchar_t* chars, va_list va) {
        if ((chars)) {
            do { append(chars);
            } while ((chars = va_arg(va, const wchar_t*)));
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& assignx
    (const void* in, size_t length, bool upper_case = false) {
        this->clear();
        this->appendx(in, length, upper_case);
        return *this;
    }
    virtual char_stringt& assign0x
    (const void* in, size_t length, bool upper_case = false) {
        this->clear();
        this->append0x(in, length, upper_case);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& appendx
    (const void* in, size_t length, bool upper_case = false) {
        const byte_t* bytes = (const byte_t*)(in);
        if ((bytes) && (length)) {
            char_t x[2];
            byte_t b;
            for (; 0 < length; --length) {
                b = (*bytes++);
                x[0] = dtox(b >> 4, upper_case);
                x[1] = dtox(b & 15, upper_case);
                append(x, 2);
            }
        }
        return *this;
    }
    virtual char_stringt& append0x
    (const void* in, size_t length, bool upper_case = false) {
        const byte_t* bytes = (const byte_t*)(in);
        if ((bytes) && (length)) {
            byte_t b = (*bytes);
            char_t x[5];

            x[0] = ((char_t)',');
            x[1] = ((char_t)'0');
            x[2] = ((char_t)((upper_case)?('X'):('x')));
            x[3] = dtox(b >> 4, upper_case);
            x[4] = dtox(b & 15, upper_case);
            append(x+1, 4);

            for (++bytes, --length; length > 0; --length, ++bytes) {
                b = (*bytes);
                x[3] = dtox(b >> 4, upper_case);
                x[4] = dtox(b & 15, upper_case);
                append(x, 5);
            }
        }
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t dtox(byte_t d, bool upper_case = false) const {
        char a = (upper_case)?('A'):('a');
        char_t x = (char_t)(0);
        if ((0 <= d) && (9 >= d))
            x = (char_t)(('0') +  d);
        else
        if ((10 <= d) && (15 >= d))
            x = (char_t)((a) + (d - 10));
        return x;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& assign_pointer(const pointer_t& c) {
        this->clear();
        return append_pointer(c);
    }
    virtual char_stringt& assign_signed(const signed_t& c) {
        this->clear();
        return append_signed(c);
    }
    virtual char_stringt& assign_unsigned(const unsigned_t& c) {
        this->clear();
        return append_unsigned(c);
    }
    virtual char_stringt& assign_bool(const bool& c) {
        this->clear();
        return append_bool(c);
    }
    virtual char_stringt& assign_int(const int& c) {
        this->clear();
        return append_int(c);
    }
    virtual char_stringt& assign_float(const int& c) {
        this->clear();
        return append_float(c);
    }
    virtual char_stringt& assign_double(const int& c) {
        this->clear();
        return append_double(c);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& append_pointer(const pointer_t& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }
    virtual char_stringt& append_signed(const signed_t& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }
    virtual char_stringt& append_unsigned(const unsigned_t& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }
    virtual char_stringt& append_bool(const bool& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }
    virtual char_stringt& append_int(const int& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }
    virtual char_stringt& append_float(const float& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }
    virtual char_stringt& append_double(const double& c) {
        sstream_t ss; ss << c;
        Extends::append(ss.str());
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& operator << (const pointer_t& c) {
        append_pointer(c);
        return *this;
    }
    virtual char_stringt& operator << (const signed_t& c) {
        append_signed(c);
        return *this;
    }
    virtual char_stringt& operator << (const unsigned_t& c) {
        append_unsigned(c);
        return *this;
    }
    virtual char_stringt& operator << (const bool& c) {
        append_bool(c);
        return *this;
    }
    virtual char_stringt& operator << (const float& c) {
        append_float(c);
        return *this;
    }
    virtual char_stringt& operator << (const double& c) {
        append_double(c);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_stringt& operator << (const char& c) {
        append(c);
        return *this;
    }
    virtual char_stringt& operator << (const char* chars) {
        append(chars);
        return *this;
    }
    virtual char_stringt& operator << (const wchar_t& c) {
        append(c);
        return *this;
    }
    virtual char_stringt& operator << (const wchar_t* chars) {
        append(chars);
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* has_chars(size_t& length) const {
        length = this->length();
        return has_chars();
    }
    virtual const char_t* has_chars() const {
        if ((this->length())) {
            return this->c_str();
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* chars(size_t& length) const {
        length = this->length();
        return chars();
    }
    virtual const char_t* chars() const {
        return this->c_str();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual signed_t to_signed() const {
        signed_t to = 0;
        sstream_t ss(*this);
        ss >> to;
        return to;
    }
    virtual unsigned_t to_unsigned() const {
        unsigned_t to = 0;
        sstream_t ss(*this);
        ss >> to;
        return to;
    }
    virtual bool to_bool() const {
        bool to = 0;
        sstream_t ss(*this);
        ss >> to;
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::compare_cased;
    virtual int compare_cased(const string_t& to) const {
        int unequal = this->compare_cased
        (this->c_str(), this->length(), to.c_str(), to.length());
        return unequal;
    }
    using Implements::compare_uncased;
    virtual int compare_uncased(const string_t& to) const {
        int unequal = this->compare_uncased
        (this->c_str(), this->length(), to.c_str(), to.length());
        return unequal;
    }
    virtual int compare(const string_t& to) const {
        int unequal = this->compare_cased
        (this->c_str(), this->length(), to.c_str(), to.length());
        return unequal;
    }
    virtual int compare(const char_t* to, ssize_t length) const {
        int unequal = this->compare_cased
        (this->c_str(), this->length(), to, length);
        return unequal;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef char_stringt<char> char_string;
typedef char_stringt<tchar_t> tchar_string;
typedef char_stringt<wchar_t> wchar_string;
typedef char_stringt<byte_t> byte_string;

typedef stringt_implements char_string_implements;
typedef stringt_implements tchar_string_implements;
typedef stringt_implements wchar_string_implements;
typedef stringt_implements byte_string_implements;

} // namespace nadir 

#endif // _NADIR_BASE_STRING_HPP 
