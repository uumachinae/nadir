///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: main.hpp
///
/// Author: $author$
///   Date: 3/12/2019
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_CONSOLE_LIB_VERSION_MAIN_HPP
#define _NADIR_CONSOLE_LIB_VERSION_MAIN_HPP

#include "nadir/console/getopt/main.hpp"
#include "nadir/lib/nadir/version.hpp"

namespace nadir {
namespace console {
namespace lib {
namespace version {

typedef ::nadir::console::getopt::main::Implements maint_implements;
typedef ::nadir::console::getopt::main maint_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template 
<class TVersion = ::nadir::lib::nadir::version, 
 class TImplements = maint_implements, class TExtends = maint_extends>

class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TVersion version_t;
    typedef typename Extends::char_t char_t;
    typedef typename Extends::endchar_t endchar_t;
    static const endchar_t endchar = Extends::endchar;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }
private:
    maint(const maint &copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int version_run(int argc, char_t** argv, char_t** env) {
        const ::nadir::lib::version& version = version_t::which();
        this->outl(version.name(), " version = ", version.to_string().chars(), NULL);
        this->outln();
        this->out_flush();
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS maint
typedef maint<> main;

} /// namespace version
} /// namespace lib
} /// namespace console
} /// namespace nadir

#endif /// _NADIR_CONSOLE_LIB_VERSION_MAIN_HPP 
