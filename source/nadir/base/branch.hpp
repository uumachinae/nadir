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
#ifndef _NADIR_BASE_BRANCH_HPP
#define _NADIR_BASE_BRANCH_HPP

#include "nadir/base/leaf.hpp"

namespace nadir {

typedef implement_base branch_implements;
typedef base branch_extends;
///////////////////////////////////////////////////////////////////////
///  Class: brancht
///////////////////////////////////////////////////////////////////////
template
<class TLeaf = leaf, class TBranch = branch,
 class TImplements = branch_implements, class TExtends = branch_extends>

class _EXPORT_CLASS brancht: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TBranch branch_t;
    typedef TLeaf leaf_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    brancht(const leaf_t& leaf, branch_t* tree = 0)
    : tree_(tree), leaf_(leaf) {
    }
    brancht(const brancht& copy)
    : tree_(0), leaf_(copy.leaf()) {
    }
    brancht(): tree_(0) {
    }
    virtual ~brancht() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* set_tree(branch_t* to) {
        tree_ = to;
        return tree_;
    }
    virtual branch_t* tree() const {
        return tree_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual leaf_t& set_leaf(const leaf_t& to) {
        return leaf_;
    }
    virtual leaf_t& leaf() const {
        return (leaf_t&)leaf_;
    }
    virtual operator leaf_t& () const {
        return (leaf_t&)leaf_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int compare(const branch_t& to) const {
        const leaf_t& to_leaf = to.leaf();
        int unequal = compare(to_leaf);
        return unequal;
    }
    virtual int compare(const leaf_t& to) const {
        int unequal = 0;
        return unequal;
    }
    virtual int operator != (const branch_t& to) const {
        int unequal = compare(to);
        return unequal;
    }
    virtual int operator != (const leaf_t& to) const {
        int unequal = compare(to);
        return unequal;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    branch_t *tree_;
    leaf_t leaf_;
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
    branch(const leaf_t& leaf, branch* tree = 0): Extends(leaf, tree) {}
    branch(const branch& copy): Extends(copy) {}
    branch() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual leaf_t& set_leaf(const leaf_t& to) {
        leaf_ = to;
        return leaf_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int compare(const leaf_t& to) const {
        int unequal = leaf_.compare(to);
        return unequal;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace nadir

#endif // _NADIR_BASE_BRANCH_HPP 
