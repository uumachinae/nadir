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
///   File: tree.hpp
///
/// Author: $author$
///   Date: 5/20/2017
///////////////////////////////////////////////////////////////////////
#ifndef _NADIR_BASE_TREE_HPP
#define _NADIR_BASE_TREE_HPP

#include "nadir/base/branch.hpp"

namespace nadir {

class _EXPORT_CLASS tree;
typedef implement_base tree_implements;
typedef base tree_extends;
///////////////////////////////////////////////////////////////////////
///  Class: treet
///////////////////////////////////////////////////////////////////////
template
<class TLeaf = leaf, class TBranch = branch, class TTree = tree,
 class TImplements = tree_implements, class TExtends = tree_extends>

class _EXPORT_CLASS treet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef TTree Derives;

    typedef TBranch branch_t;
    typedef TLeaf leaf_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    treet(branch_t *root): root_(root) {
    }
    treet(const treet& copy): root_(0) {
    }
    treet(): root_(0) {
    }
    virtual ~treet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* insert(branch_t& branch) {
        branch_t* b = 0;
        return b;
    }
    virtual branch_t* remove(branch_t& branch) {
        branch_t* b = 0;
        return b;
    }
    virtual branch_t* remove() {
        branch_t* b = root();
        clear();
        return b;
    }
    virtual void clear() {
        root_ = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* find(const leaf_t& leaf) const {
        branch_t* b = 0;
        return b;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* next(branch_t& branch) const {
        branch_t* b = 0;
        return b;
    }
    virtual branch_t* prev(branch_t& branch) const {
        branch_t* b = 0;
        return b;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* first(branch_t& branch) const {
        branch_t* b = 0;
        return b;
    }
    virtual branch_t* last(branch_t& branch) const {
        branch_t* b = 0;
        return b;
    }
    virtual branch_t* first() const {
        branch_t* b = 0;
        if ((b = root())) {
            b = first(*b);
        }
        return b;
    }
    virtual branch_t* last() const {
        branch_t* b = 0;
        if ((b = root())) {
            b = last(*b);
        }
        return b;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* least(branch_t& branch) const {
        branch_t* b = first(branch);
        return b;
    }
    virtual branch_t* greatest(branch_t& branch) const {
        branch_t* b = last(branch);
        return b;
    }
    virtual branch_t* least() const {
        branch_t* b = first();
        return b;
    }
    virtual branch_t* greatest() const {
        branch_t* b = last();
        return b;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* set_root(branch_t* to) {
        root_ = to;
        return root_;
    }
    virtual branch_t* root() const {
        return root_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    branch_t* root_;
};

typedef treet
<leaf, branch, tree, tree_implements, tree_extends> tree_extend;
///////////////////////////////////////////////////////////////////////
///  Class: tree
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS tree: public tree_extend {
public:
    typedef tree_extend Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    tree(branch *root): Extends(root) {}
    tree(const tree& copy): Extends(copy) {}
    tree() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace nadir

#endif // _NADIR_BASE_TREE_HPP 
