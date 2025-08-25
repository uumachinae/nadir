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
///   File: string.hpp
///
/// Author: $author$
///   Date: 12/21/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_STRING_HPP
#define _NADIR_IO_STRING_HPP

#include "nadir/base/string.hpp"
#include "nadir/io/reader.hpp"
#include "nadir/io/writer.hpp"
#include "nadir/io/stream.hpp"

namespace nadir {
namespace io {
namespace string {

typedef reader readert_implements;
typedef base readert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<typename TString = char_string,
 class TImplements = readert_implements, class TExtends = readert_extends>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TString string_t;
    typedef typename TString::char_t char_t;
    typedef typename TImplements::what_t what_t;
    typedef typename TImplements::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const string_t& string)
    : string_(string), tell_(0) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        size_t  length = string_.length();
        sized_t* sized = 0;
        if ((sized = ((sized_t*)what)) && (size) && (length > (tell_))) {
            const char_t* chars = 0;
            if (length < (tell_ + size)) {
                if (1 > (size = length - tell_)) {
                    return 0;
                }
            }
            if ((chars = string_.chars())) {
                ssize_t count = 0;
                if ((sizeof(sized_t) == sizeof(char_t))) {
                    for (chars += tell_; size; --size, ++chars, ++sized, ++count) {
                        *sized = *(((const sized_t*)chars));
                    }
                }
                tell_ += count;
                return count;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t reset() {
        ssize_t told = tell_;
        tell_ = 0;
        return told;
    }
    virtual ssize_t seek(size_t to) {
        size_t length = string_.length();
        if (length < (to)) {
            to = length;
        }
        tell_ = to;
        return tell_;
    }
    virtual ssize_t tell() const {
        return tell_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    const string_t& string_;
    size_t tell_;
};
typedef readert<> reader;
typedef readert<byte_string> byte_reader;
typedef readert<char_string> char_reader;
typedef readert<tchar_string> tchar_reader;
typedef readert<wchar_string> wchar_reader;

typedef writer writert_implements;
typedef base writert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template
<typename TString = char_string,
 class TImplements = writert_implements, class TExtends = writert_extends>

class _EXPORT_CLASS writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TString string_t;
    typedef typename string_t::char_t char_t;
    typedef typename Implements::what_t what_t;
    typedef typename Implements::sized_t sized_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writert(string_t& string)
    : string_(string) {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        const sized_t* sized = 0;
        if ((0 != (size)) && (sized = ((const sized_t*)what))) {
            if (0 > (size)) {
                size_t length = string_.length();
                string_.append(sized);
                return string_.length() - length;
            } else {
                string_.append(sized, size);
                return size;
            }
        }
        return 0;
    }
    virtual ssize_t writefv(const what_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t& string_;
};
typedef writert<> writer;
typedef writert<byte_string> byte_writer;
typedef writert<char_string> char_writer;
typedef writert<tchar_string> tchar_writer;
typedef writert<wchar_string> wchar_writer;

} /// namespace string
} /// namespace io
} /// namespace nadir

#endif /// ndef _NADIR_IO_STRING_HPP
