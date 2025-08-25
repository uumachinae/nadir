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
///   File: leaf.hpp
///
/// Author: $author$
///   Date: 5/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_LEAF_HPP
#define _NADIR_BASE_LEAF_HPP

#include "nadir/base/string.hpp"

namespace nadir {

class _EXPORT_CLASS leaf;
class _EXPORT_CLASS branch;
typedef implement_base leaf_implements;
typedef base leaf_extends;
///////////////////////////////////////////////////////////////////////
///  Class: leaft
///////////////////////////////////////////////////////////////////////
template
<typename TWhat = char_string, class TBranch = branch,
 class TImplements = leaf_implements, class TExtends = leaf_extends>

class _EXPORT_CLASS leaft: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TWhat what_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    leaft(const what_t& what): what_(what_) {
    }
    leaft(const leaft& copy): what_(copy.what_) {
    }
    leaft() {
    }
    virtual ~leaft() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int compare(const leaft& to) const {
        const what_t& to_what = to.what();
        int unequal = compare(to_what);
        return unequal;
    }
    virtual int compare(const what_t& to) const {
        int unequal = 0;
        if (what_ < to) {
            unequal = -1;
        } else {
            if (what_ > to) {
                unequal = 1;
            }
        }
        return unequal;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual what_t& set_what(const what_t& to) {
        what_ = to;
        return what_;
    }
    virtual what_t& what() const {
        return (what_t&)what_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual what_t& operator () () const {
        return (what_t&)what_;
    }
    virtual operator what_t& () const {
        return (what_t&)what_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    what_t what_;
};

typedef leaft
<char_string, branch, leaf_implements, leaf_extends> leaf_extend;
///////////////////////////////////////////////////////////////////////
///  Class: leaf
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS leaf: public leaf_extend {
public:
    typedef leaf_extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    leaf(const what_t& what): Extends(what_) {}
    leaf(const leaf& copy): Extends(copy.what_) {}
    leaf() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace nadir

#endif // _NADIR_BASE_LEAF_HPP 
