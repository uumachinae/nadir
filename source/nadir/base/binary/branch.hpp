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
///   File: branch.hpp
///
/// Author: $author$
///   Date: 5/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_BINARY_BRANCH_HPP
#define _NADIR_BASE_BINARY_BRANCH_HPP

#include "nadir/base/branch.hpp"

namespace nadir {
namespace binary {

class _EXPORT_CLASS branch;
typedef nadir::branch_implements branch_implements;
typedef nadir::brancht
<leaf, branch, branch_implements, nadir::branch_extends> branch_extends;
///////////////////////////////////////////////////////////////////////
///  Class: brancht
///////////////////////////////////////////////////////////////////////
template
<class TLeaf = leaf, class TBranch = branch,
 class TImplements = branch_implements, class TExtends = branch_extends>

class _EXPORT_CLASS brancht: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TBranch branch_t;
    typedef TLeaf leaf_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    brancht
    (const leaf_t& leaf, branch_t* tree = 0,
     branch_t* left = 0, branch_t* right = 0)
    : Extends(leaf, tree), left_(left), right_(right) {
    }
    brancht(const brancht& copy)
    : Extends(copy), left_(0), right_(0) {
    }
    brancht(): left_(0), right_(0) {
    }
    virtual ~brancht() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t*& set_left(branch_t* to) {
        left_ = to;
        return left_;
    }
    virtual branch_t*& left() const {
        return (branch_t*&)left_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t*& set_right(branch_t* to) {
        right_ = to;
        return right_;
    }
    virtual branch_t*& right() const {
        return (branch_t*&)right_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    branch_t *left_, *right_;
};

typedef brancht
<leaf, branch, branch_implements, branch_extends> branch_extend;
///////////////////////////////////////////////////////////////////////
///  Class: branch
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS branch: public branch_extend {
public:
    typedef branch_extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    branch
    (const leaf_t& leaf, branch* tree = 0,
     branch* left = 0, branch* right = 0)
    : Extends(leaf, tree, left, right) {}
    branch(const branch& copy): Extends(copy) {}
    branch() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace binary
} // namespace nadir 

#endif // _NADIR_BASE_BINARY_BRANCH_HPP
