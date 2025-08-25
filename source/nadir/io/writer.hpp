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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 1/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_IO_WRITER_HPP
#define _NADIR_IO_WRITER_HPP

#include "nadir/base/base.hpp"

namespace nadir {
namespace io {

typedef implement_base writert_implements;
///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TImplements = writert_implements>

class _EXPORT_CLASS writert: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TSized char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size = -1) { return 0; }
    virtual ssize_t flush() { return 0; }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t writel(const what_t* what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = writev(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t writev(const what_t* what, va_list va) {
        ssize_t count = 0;
        ssize_t length = 0;
        for (count = 0; what; count += length) {
            if (0 > (length = write(what)))
                return count;
            what = va_arg(va, const sized_t*);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t writef(const sized_t* format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = writefv(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t writefv(const sized_t* format, va_list va) {
        ssize_t count = 0;
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef writert<void, char, int, 0> writer;

typedef writert<char, char, int, 0> char_writer;
typedef writert<wchar_t, wchar_t, int, 0> wchar_writer;
typedef writert<tchar_t, tchar_t, int, 0> tchar_writer;

typedef writert<byte_t, byte_t, int, 0> byte_writer;

namespace echoed {

typedef base writer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = void, typename TSized = char,
 typename TEnd = int, TEnd VEnd = 0,
 class TWriter = io::writert<TWhat, TSized, TEnd, VEnd>,
 class TImplements = TWriter, class TExtends = writer_extends>

class _EXPORT_CLASS writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TWriter writer_t;
    typedef TWhat what_t;
    typedef TSized sized_t;
    typedef TSized char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writert(writer_t& written, writer_t& echoed)
    : written_(written), echoed_(echoed) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, ssize_t size = -1) {
        ssize_t count = written_.write(what, size);
        echoed_.write(what, size);
        return count;
    }
    virtual ssize_t flush() {
        ssize_t count = written_.flush();
        echoed_.flush();
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    writer_t &written_, &echoed_;
};
typedef writert<> writer;

} // namespace echoed
} // namespace io
} // namespace nadir 

#endif // _NADIR_IO_WRITER_HPP 
