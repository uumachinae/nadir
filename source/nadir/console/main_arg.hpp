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
///   File: main_arg.hpp
///
/// Author: $author$
///   Date: 6/21/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_MAIN_ARG_HPP
#define _NADIR_CONSOLE_MAIN_ARG_HPP

#include "nadir/base/base.hpp"

namespace nadir {
namespace console {

typedef implement_base main_argt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: main_argt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,
 typename TEndChar = TChar, TEndChar VEndChar = 0,
 class TImplements = main_argt_implements>

class _EXPORT_CLASS main_argt: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TChar char_t;
    typedef TEndChar end_char_t;
    enum { end_char = VEndChar };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int get_arguments(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int before_get_arguments(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_get_arguments(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int invalid_argument(const char_t* arg) {
        int err = 1;
        return err;
    }
    virtual int missing_argument(const char_t* arg) {
        int err = 1;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_argument
    (const char_t* arg, int argind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual const char_t* arguments(const char_t**& args) {
        args = 0;
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef main_argt<> main_arg;

} // namespace console 
} // namespace nadir 

#endif // _NADIR_CONSOLE_MAIN_ARG_HPP 
