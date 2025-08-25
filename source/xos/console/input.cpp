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
///   File: input.cpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#include "xos/console/input.hpp"

#if !defined(XOS_CONSOLE_INPUT_INSTANCE)
///#define XOS_CONSOLE_INPUT_INSTANCE
#endif /// !defined(XOS_CONSOLE_INPUT_INSTANCE)

namespace xos {
namespace console {

/// in...
file_t std_in() {
    return (file_t)stdin;
}
ssize_t inf(const char *format, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, format);
    count = infv(std_in(), format, va);
    va_end(va);
    return count;
}
ssize_t infv(const char *format, va_list va) {
    ssize_t count = 0;
    count = infv(std_in(), format, va);
    return count;
}
ssize_t in(char *what, size_t size) {
    ssize_t count = 0;
    count = in(std_in(), what, size);
    return count;
}
ssize_t inf(file_t f, const char *format, ...) {
    ssize_t count = 0;
    va_list va;
    va_start(va, format);
    count = infv(f, format, va);
    va_end(va);
    return count;
}
ssize_t infv(file_t f, const char *format, va_list va) {
    ssize_t count = 0;
    if ((f != ((file_t)null)) && (format)) {
        count = ::vfscanf(f, format, va);
    }
    return count;
}
ssize_t in(file_t f, char *what, size_t size) {
    ssize_t count = 0;
    if ((f != ((file_t)null)) && (what)) {
        count = ::fread(what, sizeof(char), size, f);
    }
    return count;
}

///  Class: inputt
#if defined(XOS_CONSOLE_INPUT_INSTANCE)
static input the_input;
#endif /// defined(XOS_CONSOLE_INPUT_INSTANCE)


} /// namespace console
} /// namespace xos
