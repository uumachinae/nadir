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
///   File: out.cpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#include "xos/console/out.hpp"

#if !defined(XOS_CONSOLE_OUT_INSTANCE)
///#define XOS_CONSOLE_OUT_INSTANCE
#endif /// !defined(XOS_CONSOLE_OUT_INSTANCE)

namespace xos {
namespace console {

ssize_t outllnv(file_t f, const char *what, va_list va) {
    ssize_t count = 0, amount = 0;
    if (0 <= (count = outlv(f, what, va))) {
        if (0 <= (amount = outln(f))) {
            count += amount;
        } else {
            count = amount;
        }
    }
    return count;
}
ssize_t outlv(file_t f, const char *what, va_list va) {
    typedef const char *what_t;
    ssize_t count = 0, amount = 0;
    for (count = 0; what; count += amount) {
        if (0 > (amount = out(f, what))) {
            return amount;
        }
        what = va_arg(va, what_t);
    }
    return count;
}
ssize_t outfv(file_t f, const char *format, va_list va) {
    ssize_t count = 0;
    if ((f != ((file_t)null)) && (format)) {
        count = ::vfprintf(f, format, va);
    }
    return count;
}
ssize_t outln(file_t f, const char *what, size_t length) {
    ssize_t count = 0;
    if (0 <= (count = out(f, what, length))) {
        ssize_t amount = 0;
        if (0 <= (amount = outln(f))) {
            count += amount;
        } else {
            count = amount;
        }
    }
    return count;
}
ssize_t outln(file_t f, const char *what) {
    ssize_t count = 0;
    if (0 <= (count = out(f, what))) {
        ssize_t amount = 0;
        if (0 <= (amount = outln(f))) {
            count += amount;
        } else {
            count = amount;
        }
    }
    return count;
}
ssize_t out(file_t f, const char *what, size_t length) {
    ssize_t count = 0;
    if ((f != ((file_t)null)) && (what)) {
        count = ::fwrite(what, sizeof(char), length, f);
    }
    return count;
}
ssize_t out(file_t f, const char *what) {
    ssize_t count = 0;
    if ((f != ((file_t)null)) && (what)) {
        ssize_t amount = 0;
        for (char c = *(what); c; c = *(++what), count += amount) {
            if (0 >= (amount = out(f, &c, 1))) {
                return amount;
            }
        }
    }
    return count;
}
ssize_t outln(file_t f) {
    ssize_t count = 0;
    if ((f != ((file_t)null))) {
        static const char lf = '\n';
        count = ::fwrite(&lf, sizeof(char), 1, f);
    }
    return count;
}
ssize_t out_flush(file_t f) {
    ssize_t count = 0;
    if ((f != ((file_t)null))) {
        count = ::fflush(f);
    }
    return count;
}

///  Class: outt
#if defined(XOS_CONSOLE_OUT_INSTANCE)
static out the_out;
#endif /// defined(XOS_CONSOLE_OUT_INSTANCE)

} /// namespace console
} /// namespace xos
