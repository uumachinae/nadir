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
///   File: main_exception.hpp
///
/// Author: $author$
///   Date: 5/2/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_MAIN_EXCEPTION_HPP
#define _NADIR_CONSOLE_MAIN_EXCEPTION_HPP

#include "nadir/base/base.hpp"

namespace nadir {
namespace console {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum main_exception_which {
    main_already_exists,
    main_doesnt_exist
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_exception {
public:
    main_exception(main_exception_which which): which_(which) {}
    virtual ~main_exception() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual main_exception_which which() const { return which_; }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    main_exception_which which_;
};

} // namespace console
} // namespace nadir 

#endif // _NADIR_CONSOLE_MAIN_EXCEPTION_HPP 
