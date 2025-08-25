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
///   Date: 3/3/2022
///////////////////////////////////////////////////////////////////////
#ifndef XOS_IO_CONSOLE_OUTPUT_HPP
#define XOS_IO_CONSOLE_OUTPUT_HPP

#include "xos/io/crt/file/output.hpp"
#include "xos/console/io.hpp"

namespace xos {
namespace io {
namespace console {

/// class outputt
template 
<class TExtendsOutput = crt::file::output, 
 class TExtends = TExtendsOutput, class TImplements = typename TExtends::implements>

class exported outputt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef outputt derives; 
    
    typedef typename extends::file_t file_t;
    typedef typename extends::output_t output_t;
    typedef typename implements::string_t string_t;
    typedef typename implements::char_t char_t;
    typedef typename implements::end_char_t end_char_t;
    enum { end_char = implements::end_char };

    typedef char_t what_t;
    typedef char_t sized_t;

    /// constructors / destructor
    outputt(const outputt& copy) {
    }
    outputt() {
    }
    virtual ~outputt() {
    }

    /// out...
    virtual ssize_t outsfv(char_t *string, size_t size, const sized_t *format, va_list va) {
        ssize_t count = 0;
        return count;
    }
    virtual ssize_t outfv(const sized_t *format, va_list va) {
        ssize_t count = 0;
        file_t f = out_std_out();
        count = xos::console::outfv(f, format, va);
        return count;
    }
    using implements::out;
    virtual ssize_t out(const what_t *what, size_t length) {
        ssize_t count = 0;
        file_t f = out_std_out();
        count = xos::console::out(f, what, length);
        return count;
    }
    virtual ssize_t out_flush() {
        ssize_t count = 0;
        file_t f = out_std_out();
        count = xos::console::out_flush(f);
        return count;
    }

protected:
    virtual file_t out_std_out() const {
        return std_out();
    }
    virtual file_t std_out() const {
        return (file_t)stdout;
    }

protected:
}; /// class outputt
typedef outputt<> output;

} /// namespace console
} /// namespace io
} /// namespace xos

#endif /// XOS_IO_CONSOLE_OUTPUT_HPP
