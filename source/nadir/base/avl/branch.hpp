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
#ifndef _NADIR_BASE_AVL_BRANCH_HPP
#define _NADIR_BASE_AVL_BRANCH_HPP

#include "nadir/base/binary/branch.hpp"

namespace nadir {
namespace avl {

class _EXPORT_CLASS branch;
typedef binary::branch_implements branch_implements;
typedef binary::brancht
<leaf, branch, branch_implements, brancht
<leaf, branch, branch_implements, branch_extends> > branch_extends;
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
    (const leaf_t& leaf, int depth = 1,
     branch_t* tree = 0, branch_t* left = 0, branch_t* right = 0)
    : Extends(leaf, tree, left, right), depth_(depth) {
    }
    brancht(const brancht& copy)
    : Extends(copy), depth_(1) {
    }
    brancht(): depth_(1) {
    }
    virtual ~brancht() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int set_depth(int to) {
        depth_ = to;
        return depth_;
    }
    virtual int depth() const {
        return depth_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    int depth_;
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
    (const leaf_t& leaf, int depth = 1,
     branch* tree = 0, branch* left = 0, branch* right = 0)
    : Extends(leaf, depth, tree, left, right) {}
    branch(const branch& copy): Extends(copy) {}
    branch() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace avl
} // namespace nadir 

#endif // _NADIR_BASE_AVL_BRANCH_HPP
