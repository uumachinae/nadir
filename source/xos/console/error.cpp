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
///   File: error.cpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#include "xos/console/error.hpp"

#if !defined(XOS_CONSOLE_ERROR_INSTANCE)
///#define XOS_CONSOLE_ERROR_INSTANCE
#endif /// !defined(XOS_CONSOLE_ERROR_INSTANCE)

namespace xos {
namespace console {

/// err...
file_t std_err() {
    return (file_t)stderr;
}
ssize_t errlln(const char *what, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, what);
    count = errllnv(what, va);
    va_end(va);
    return count;
}
ssize_t errl(const char *what, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, what);
    count = errlv(what, va);
    va_end(va);
    return count;
}
ssize_t errllnv(const char *what, va_list va) {
    return outllnv(std_err(), what, va);
}
ssize_t errlv(const char *what, va_list va) {
    return outlv(std_err(), what, va);
}
ssize_t errf(const char *format, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, format);
    count = errfv(format, va);
    va_end(va);
    return count;
}
ssize_t errfv(const char *format, va_list va) {
    return outfv(std_err(), format, va);
}
ssize_t err(const char *what, size_t length) {
    return out(std_err(), what, length);
}
ssize_t err(const char *what) {
    return out(std_err(), what);
}

///  Class: errort
#if defined(XOS_CONSOLE_ERROR_INSTANCE)
static error the_error;
#endif /// defined(XOS_CONSOLE_ERROR_INSTANCE)

} /// namespace console
} /// namespace xos
