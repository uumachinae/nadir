///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: Version.hpp
///
/// Author: $author$
///   Date: 12/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _PATRONA_LIB_VERSION_HPP
#define _PATRONA_LIB_VERSION_HPP

#include "patrona/base/String.hpp"
#include "nadir/lib/version.hpp"

namespace patrona {
namespace lib {

typedef ::nadir::lib::version Version_implements;
///////////////////////////////////////////////////////////////////////
///  Class: Version
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS Version: virtual public Version_implements {
public:
    typedef Version_implements Implements;

    virtual String ToString() const {
        String to(to_string().chars());
        return to;
    }
    virtual const char_t* Name() const {
        return "Version";
    }
    virtual unsigned Major() const {
        return 0;
    }
    virtual unsigned Minor() const {
        return 0;
    }
    virtual unsigned Release() const {
        return 0;
    }

    virtual const char_t* name() const {
        return Name();
    }
    virtual unsigned major() const {
        return Major();
    }
    virtual unsigned minor() const {
        return Minor();
    }
    virtual unsigned release() const {
        return Release();
    }
};

} /// namespace lib
} /// namespace patrona

#endif /// ndef _PATRONA_LIB_VERSION_HPP
