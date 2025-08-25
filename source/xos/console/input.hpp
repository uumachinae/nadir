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
///   File: input.hpp
///
/// Author: $author$
///   Date: 8/5/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_INPUT_HPP
#define XOS_CONSOLE_INPUT_HPP

#include "xos/console/sequence.hpp"

namespace xos {
namespace console {

/// ...in...
file_t std_in();
ssize_t inf(const char *format, ...);
ssize_t infv(const char *format, va_list va);
ssize_t in(char *what, size_t size);
ssize_t inf(file_t f, const char *format, ...);
ssize_t infv(file_t f, const char *format, va_list va);
ssize_t in(file_t f, char *what, size_t size);

/// class inputt
template 
<typename TChar = char, typename TFile = FILE*, class TLocked = locked, 
 class TSequence = xos::console::sequencet<TChar, TFile, TLocked>,
 class TImplements = TSequence>

class exported inputt: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef inputt derives; 
    
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
    virtual ~inputt() {
    }

    /// in...
    virtual ssize_t inf(const sized_t *format, ...) {
        ssize_t count = 0;
        va_list va;
        va_start(va, format);
        count = this->infv(format, va);
        va_end(va);
        return count;
    }
    virtual ssize_t infv(const sized_t *format, va_list va) {
        return 0;
    }
    virtual ssize_t in(what_t *what, size_t size) {
        file_t f = in_std_in();
        return in(f, what, size);
    }
    virtual ssize_t in(file_t in, what_t *what, size_t size) {
        return console::in(in, what, size);
    }
protected:
    virtual file_t in_std_in() {
        return std_in();
    }
    virtual file_t std_in() const {
        return (file_t)stdin;
    }

}; /// class inputt
typedef inputt<> input;

} /// namespace console
} /// namespace xos

#endif /// ndef XOS_CONSOLE_INPUT_HPP
