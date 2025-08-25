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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 1/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_READER_HPP
#define _NADIR_IO_READER_HPP

#include "nadir/base/base.hpp"

namespace nadir {
namespace io {

typedef implement_base readert_implements;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplements = readert_implements>

class _EXPORT_CLASS readert: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) { return 0; }
    virtual ssize_t fill() { return 0; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t seek(ssize_t offset, int whence) { return -1; }
    virtual ssize_t tell() { return -1; }
    virtual ssize_t eof() { return -1; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t readf(const sized_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = readfv(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t readfv(const sized_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef readert<void, char, int, 0> reader;

typedef readert<char, char, int, 0> char_reader;
typedef readert<wchar_t, wchar_t, int, 0> wchar_reader;
typedef readert<tchar_t, tchar_t, int, 0> tchar_reader;

typedef readert<byte_t, byte_t, int, 0> byte_reader;
typedef readert<word_t, word_t, int, 0> word_reader;
} // namespace io
} // namespace nadir 

#endif // _NADIR_IO_READER_HPP 
