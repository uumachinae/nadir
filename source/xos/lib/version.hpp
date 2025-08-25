///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: version.hpp
///
/// Author: $author$
///   Date: 3/10/2020
///////////////////////////////////////////////////////////////////////
#ifndef XOS_LIB_VERSION_HPP
#define XOS_LIB_VERSION_HPP

#include "xos/base/string.hpp"

namespace xos {
namespace lib {

///  Class: versiont
template 
<class TChar = char, class TString = stringt<TChar>, class TImplements = implement>

class exported versiont: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef versiont derives;

    typedef TString string_t;
    typedef TChar char_t;
    
    /// to_string
    virtual string_t to_string() const {
        string_t to;
        to_string(to);
        return to;
    }
    virtual string_t& to_string(string_t& to) const {
        const char_t *chars = 0;

        to.assign(this->name());

        to.append(this->name_separator());
        to.append_unsigned(this->major());

        to.append(this->major_separator());
        to.append_unsigned(this->minor());

        to.append(this->minor_separator());
        to.append_unsigned(this->revision());

        if ((chars = build()) && (chars[0])) {
           to.append(this->revision_separator());
           to.append(chars);
        }
        return to;
    }
    virtual const char_t* to_chars(string_t& to) const {
        const char_t* chars = to_string(to).chars();
        return chars;
    }

    /// name / ...separator
    virtual const char_t* name() const {
        return "version";
    }
    virtual const char_t* name_separator() const {
        return "-";
    }
    virtual const char_t* major_separator() const {
        return ".";
    }
    virtual const char_t* minor_separator() const {
        return ".";
    }
    virtual const char_t* revision_separator() const {
        return "-";
    }

    /// major / minor / revision / build
    virtual unsigned major() const {
        return 0;
    }
    virtual unsigned minor() const {
        return 0;
    }
    virtual unsigned revision() const {
        return 0;
    }
    virtual const char_t* build() const {
        return 0;
    }
}; /// class versiont
typedef versiont<> version;

namespace extended {
/// class versiont
template <class TExtends = extend, class TImplements = lib::version>
class exported versiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef versiont derives;

    typedef typename implements::string_t string_t;
    typedef typename implements::char_t char_t;

    /// constructor / destructor
    versiont(const versiont& copy): extends(copy) {
    }
    versiont(const char_t* name, unsigned major, unsigned minor, unsigned revision, const char_t* build)
    : name_(name), major_(major), minor_(minor), revision_(revision), build_(build) {
    }
    virtual ~versiont() {
    }

    /// name / major / minor / revision / build
    virtual const char_t* name() const {
        return name_.chars();
    }
    virtual unsigned major() const {
        return major_;
    }
    virtual unsigned minor() const {
        return minor_;
    }
    virtual unsigned revision() const {
        return revision_;
    }
    virtual const char_t* build() const {
        size_t length = 0;
        return build_.has_chars(length);
    }

protected:
    string_t name_;
    unsigned major_, minor_, revision_;
    string_t build_;
}; /// class versiont
typedef versiont<> version;
} /// namespace extended

} /// namespace lib
} /// namespace xos

#endif /// XOS_LIB_VERSION_HPP
