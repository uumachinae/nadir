//////////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2023 $organization$
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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 3/19/2023
//////////////////////////////////////////////////////////////////////////
#ifndef XOS_CONSOLE_MAIN_OPT_HPP
#define XOS_CONSOLE_MAIN_OPT_HPP

#include "xos/console/main.hpp"

namespace xos {
namespace console {

/// class main_optt
template 
<typename TChar = char, class TIo = iot<TChar>, 
 class TExtends = xos::console::maint<TChar, TIo>, class TImplements = typename TExtends::implements>

class exported main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef main_optt derives;

    /// constructor / destructor
    main_optt() {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt &copy) {
        throw exception(exception_unexpected);
    }

protected:
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace console 
} /// namespace xos 

#endif /// ndef XOS_CONSOLE_MAIN_OPT_HPP
