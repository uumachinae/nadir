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
///   File: output.hpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_OUTPUT_HPP
#define XOS_CONSOLE_OUTPUT_HPP

#include "xos/console/out.hpp"

namespace xos {
namespace console {

/// out...
file_t std_out();
ssize_t outlln(const char *what, ...);
ssize_t outllnv(const char *what, va_list va);
ssize_t outl(const char *what, ...);
ssize_t outlv(const char *what, va_list va);
ssize_t outf(const char *format, ...);
ssize_t outfv(const char *format, va_list va);
ssize_t out(const char *what, size_t length);
ssize_t out(const char *what);

/// class outputt
template 
<typename TChar = char, typename TFile = FILE*, class TLocked = locked, 
 class TOut = xos::console::outt<TChar, TFile, TLocked>, class TImplements = TOut>

class exported outputt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef outputt derives; 
    
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
    virtual ~outputt() {
    }

    /// out...
    virtual ssize_t outln(const string_t& chars) {
        ssize_t count = outln(chars.chars(), chars.length());
        return count;
    }
    virtual ssize_t out(const string_t& chars) {
        ssize_t count = out(chars.chars(), chars.length());
        return count;
    }
    virtual ssize_t outlln(const what_t *what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = this->outllnv(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outl(const what_t *what, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, what);
        count = this->outlv(what, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outllnv(const what_t *what, va_list va) {
        file_t f = out_std_out();
        return console::outllnv(f, what, va);
    }
    virtual ssize_t outlv(const what_t *what, va_list va) {
        file_t f = out_std_out();
        return console::outlv(f, what, va);
    }
    virtual ssize_t outf(const sized_t *format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = this->outfv(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t outfv(const sized_t *format, va_list va) {
        return 0;
    }

    using implements::outxln;
    using implements::outx;
    virtual ssize_t outXln(const void* out, size_t length, bool upper_case = true) {
        file_t f = out_std_out();
        return this->outxln(f, out, length, upper_case);
    }
    virtual ssize_t outX(const void* out, size_t length, bool upper_case = true) {
        file_t f = out_std_out();
        return this->outx(f, out, length, upper_case);
    }
    virtual ssize_t outxln(const void* out, size_t length, bool upper_case = false) {
        file_t f = out_std_out();
        return this->outxln(f, out, length, upper_case);
    }
    virtual ssize_t outx(const void* out, size_t length, bool upper_case = false) {
        file_t f = out_std_out();
        return this->outx(f, out, length, upper_case);
    }

    using implements::out0xln;
    using implements::out0x;
    virtual ssize_t out0Xln(const void* out, size_t length, bool upper_case = true) {
        file_t f = out_std_out();
        return this->out0xln(f, out, length, upper_case);
    }
    virtual ssize_t out0X(const void* out, size_t length, bool upper_case = true) {
        file_t f = out_std_out();
        return this->out0x(f, out, length, upper_case);
    }
    virtual ssize_t out0xln(const void* out, size_t length, bool upper_case = false) {
        file_t f = out_std_out();
        return this->out0xln(f, out, length, upper_case);
    }
    virtual ssize_t out0x(const void* out, size_t length, bool upper_case = false) {
        file_t f = out_std_out();
        return this->out0x(f, out, length, upper_case);
    }

    using implements::out64ln;
    using implements::out64;
    virtual ssize_t out64ln(const void* out, size_t length) {
        file_t f = out_std_out();
        return this->out64ln(f, out, length);
    }
    virtual ssize_t out64(const void* out, size_t length) {
        file_t f = out_std_out();
        return this->out64(f, out, length);
    }

    virtual ssize_t outln(const what_t *what, size_t length) {
        file_t f = out_std_out();
        return console::outln(f, what, length);
    }
    virtual ssize_t outln(const what_t *what) {
        file_t f = out_std_out();
        return console::outln(f, what);
    }
    virtual ssize_t out(const what_t *what, size_t length) {
        file_t f = out_std_out();
        return console::out(f, what, length);
    }
    virtual ssize_t out(const what_t *what) {
        file_t f = out_std_out();
        return console::out(f, what);
    }
    virtual ssize_t outln() {
        file_t f = out_std_out();
        return console::outln(f);
    }
    virtual ssize_t out_flush() {
        file_t f = out_std_out();
        return console::out_flush(f);
    }
protected:
    virtual file_t out_std_out() {
        return std_out();
    }
    virtual file_t std_out() const {
        return (file_t)stdout;
    }

}; /// class outputt
typedef outputt<> output;

} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_OUTPUT_HPP
