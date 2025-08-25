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
///   File: output.cpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#include "xos/console/output.hpp"

#if !defined(XOS_CONSOLE_OUTPUT_INSTANCE)
///#define XOS_CONSOLE_OUTPUT_INSTANCE
#endif /// !defined(XOS_CONSOLE_OUTPUT_INSTANCE)

namespace xos {
namespace console {

/// out...
file_t std_out() {
    return (file_t)stdout;
}
ssize_t outlln(const char *what, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, what);
    count = outllnv(what, va);
    va_end(va);
    return count;
}
ssize_t outl(const char *what, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, what);
    count = outlv(what, va);
    va_end(va);
    return count;
}
ssize_t outllnv(const char *what, va_list va) {
    return outllnv(std_out(), what, va);
}
ssize_t outlv(const char *what, va_list va) {
    return outlv(std_out(), what, va);
}
ssize_t outf(const char *format, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, format);
    count = outfv(format, va);
    va_end(va);
    return count;
}
ssize_t outfv(const char *format, va_list va) {
    return outfv(std_out(), format, va);
}
ssize_t out(const char *what, size_t length) {
    return out(std_out(), what, length);
}
ssize_t out(const char *what) {
    return out(std_out(), what);
}

///  Class: outputt
#if defined(XOS_CONSOLE_OUTPUT_INSTANCE)
static output the_output;
#endif /// defined(XOS_CONSOLE_OUTPUT_INSTANCE)

} /// namespace console
} /// namespace xos
