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
///   File: Main.hpp
///
/// Author: $author$
///   Date: 2/24/2019
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_CONSOLE_LIB_VERSION_MAIN_HPP
#define _PATRONA_CONSOLE_LIB_VERSION_MAIN_HPP

#include "patrona/console/getopt/Main.hpp"
#include "patrona/lib/patrona/Version.hpp"

namespace patrona {
namespace console {
namespace lib {
namespace version {

typedef ::patrona::console::getopt::Main::Implements MainTImplements;
typedef ::patrona::console::getopt::Main MainTExtends;
///////////////////////////////////////////////////////////////////////
///  Class: MainT
///////////////////////////////////////////////////////////////////////
template 
<class TWhichVersion = ::patrona::lib::patrona::Version,
 class TImplements = MainTImplements, class TExtends = MainTExtends>

class _EXPORT_CLASS MainT: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TWhichVersion WhichVersion;
    typedef typename Extends::char_t char_t;
    typedef typename Extends::endchar_t endchar_t;
    static const endchar_t endchar = Extends::endchar;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    MainT() {
    }
    virtual ~MainT() {
    }
private:
    MainT(const MainT& copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int Run(int argc, char_t**argv, char_t** env) {
        int err = VersionRun(argc, argv, env);
        return err;
    }
    virtual int VersionRun(int argc, char_t**argv, char_t** env) {
        const ::patrona::lib::Version& version = WhichVersion::Which();
        int err = 0;
        this->OutL(version.Name(), " version = ", version.ToString().Chars(), NULL);
        this->OutLn();
        this->OutFlush();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS MainT
typedef MainT<> Main;

} /// namespace version
} /// namespace lib
} /// namespace console
} /// namespace patrona

#endif /// _PATRONA_CONSOLE_LIB_VERSION_MAIN_HPP 
