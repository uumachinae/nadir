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
#ifndef _NADIR_BASE_BINARY_TREE_HPP
#define _NADIR_BASE_BINARY_TREE_HPP

#include "nadir/base/binary/branch.hpp"
#include "nadir/base/tree.hpp"

#if !defined(NADIR_BASE_BINARY_TREE_DEBUG)
#define BINARY_TREE_LOG_MESSAGE_DEBUG(args)
#else // !defined(NADIR_BASE_BINARY_TREE_DEBUG)
#define BINARY_TREE_LOG_MESSAGE_DEBUG(args) LOG_MESSAGE_DEBUG(args)
#endif // !defined(NADIR_BASE_BINARY_TREE_DEBUG)

namespace nadir {
namespace binary {

class _EXPORT_CLASS tree;
typedef nadir::tree_implements tree_implements;
typedef nadir::treet
<leaf, branch, tree, tree_implements, nadir::tree_extends> tree_extends;
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
    treet(branch_t* root): Extends(root) {
    }
    treet(const treet& copy): Extends(copy) {
    }
    treet() {
    }
    virtual ~treet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* insert(branch_t& branch) {
        branch_t *next = 0, *tree = 0;
        int unequal = 0;

        BINARY_TREE_LOG_MESSAGE_DEBUG("insert " << what(branch) << "...");
        if (!(next = this->root())) {
            BINARY_TREE_LOG_MESSAGE_DEBUG("...root = " << what(branch) << "");
            this->set_root(&branch);
        } else {
            do {
                tree = next;

                BINARY_TREE_LOG_MESSAGE_DEBUG("compare branch " << what(branch) << " to " << what(tree) << "...");
                if ((unequal = branch.compare(*tree)) < 0) {
                    BINARY_TREE_LOG_MESSAGE_DEBUG("...branch " << what(branch) << " < " << what(tree) << "");
                    if (!(next = tree->left())) {
                        BINARY_TREE_LOG_MESSAGE_DEBUG("..." << what(tree) << " <--- = branch " << what(branch) << "");
                        tree->set_left(&branch);
                    }
                } else {
                    BINARY_TREE_LOG_MESSAGE_DEBUG("...branch " << what(branch) << " >= " << what(tree) << "");
                    if (!(next = tree->right())) {
                        BINARY_TREE_LOG_MESSAGE_DEBUG("..." << what(tree) << " ---> = branch " << what(branch) << "");
                        tree->set_right(&branch);
                    }
                }
            } while(next);
            BINARY_TREE_LOG_MESSAGE_DEBUG("...branch " << what(branch) << " ---^ = " << what(tree) << "");
            branch.set_tree(tree);
        }
        BINARY_TREE_LOG_MESSAGE_DEBUG("...insert " << what(branch) << "");
        return &branch;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* remove(branch_t& branch) {
        branch_t *next = 0, *moved = 0;

        BINARY_TREE_LOG_MESSAGE_DEBUG("remove " << what(branch) << "...");
        if (!(branch.left()) || !(branch.right())) {
            BINARY_TREE_LOG_MESSAGE_DEBUG("...moved = " << what(branch) << "");
            moved = &branch;
        } else {
            BINARY_TREE_LOG_MESSAGE_DEBUG("...moved = next(" << what(branch) << ")");
            moved = this->next(branch);
        }
        if (!(next = moved->left())) {
            BINARY_TREE_LOG_MESSAGE_DEBUG("...next = " << what(moved) << " ---> ");
            next = moved->right();
        }
        if (next) {
            BINARY_TREE_LOG_MESSAGE_DEBUG("...next " << what(next) << " ---^ = " << what(moved) << " ---^ ");
            next->set_tree(moved->tree());
        }
        if (!(moved->tree())) {
            BINARY_TREE_LOG_MESSAGE_DEBUG("...root = next "  << what(next) << "");
            this->set_root(next);
        } else {
            if (moved == moved->tree()->left()) {
                BINARY_TREE_LOG_MESSAGE_DEBUG("...moved " << what(moved->tree()) << " ---^ <--- = next " << what(next) << "");
                moved->tree()->set_left(next);
            } else {
                BINARY_TREE_LOG_MESSAGE_DEBUG("...moved " << what(moved->tree()) << " ---^ ---> = next " << what(next) << "");
                moved->tree()->set_right(next);
            }
        }
        if (moved != &branch) {
            if ((next = moved->set_tree(branch.tree()))) {
                if (&branch == next->right()) {
                    BINARY_TREE_LOG_MESSAGE_DEBUG("...next " << what(next) << " ---> = moved " << what(moved) << "");
                    next->set_right(moved);
                } else {
                    BINARY_TREE_LOG_MESSAGE_DEBUG("...next " << what(next) << " <--- = moved " << what(moved) << "");
                    next->set_left(moved);
                }
            }
            if ((next = moved->set_left(branch.left()))) {
                BINARY_TREE_LOG_MESSAGE_DEBUG("...next " << what(next) << " ---^ = moved " << what(moved) << "");
                next->set_tree(moved);
            }
            if ((next = moved->set_right(branch.right()))) {
                BINARY_TREE_LOG_MESSAGE_DEBUG("...next " << what(next) << " ---^ = moved " << what(moved) << "");
                next->set_tree(moved);
            }
        }
        BINARY_TREE_LOG_MESSAGE_DEBUG("...remove " << what(branch) << "");
        return &branch;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* find(const leaf_t& leaf) const {
        branch_t *branch = 0;
        int unequal = 0;

        BINARY_TREE_LOG_MESSAGE_DEBUG("find " << leaf.what() << "...");
        if ((branch = this->root())) {
            do {
                BINARY_TREE_LOG_MESSAGE_DEBUG("compare branch "  << what(branch) << " to "<< leaf.what() << "...");
                if ((unequal = branch->compare(leaf)) < 0) {
                    BINARY_TREE_LOG_MESSAGE_DEBUG("...branch " << what(branch) << " < "<< leaf.what() << " --->");
                    branch = branch->right();
                } else {
                    if (unequal > 0) {
                        BINARY_TREE_LOG_MESSAGE_DEBUG("...branch " << what(branch) << " > "<< leaf.what() << " <---");
                        branch = branch->left();
                    } else {
                        BINARY_TREE_LOG_MESSAGE_DEBUG("...found " << leaf.what() << "");
                        break;
                    }
                }
            } while (branch);
        }
        return branch;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* next(branch_t& branch) const {
        branch_t *tree = 0;

        if ((tree = branch.right())) {
            return this->first(*tree);
        }
        if ((tree = branch.tree())) {
            branch_t *tbranch = &branch;
            do {
                if (tbranch != tree->right()) {
                    break;
                }
                tbranch = tree;
                tree = tree->tree();
            } while(tree);
        }
        return tree;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* prev(branch_t& branch) const {
        branch_t *tree;

        if ((tree = branch.left())) {
            return this->last(*tree);
        }
        if ((tree = branch.tree())) {
            branch_t *tbranch = &branch;
            do {
                if (tbranch != tree->left()) {
                    break;
                }
                tbranch = tree;
                tree = tree->tree();
            } while(tree);
        }
        return tree;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::first;
    virtual branch_t* first(branch_t& branch) const {
        branch_t *b = &branch, *next = 0;
        while ((next = b->left())) {
            b = next;
        }
        return b;
    }
    virtual branch_t* last(branch_t& branch) const {
        branch_t* b = &branch, *next = 0;
        while ((next = b->right())) {
            b = next;
        }
        return b;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* left(branch_t* branch) const {
        branch_t* b = (branch)?(branch->left()):(0);
        return b;
    }
    virtual branch_t* right(branch_t* branch) const {
        branch_t* b = (branch)?(branch->right()):(0);
        return b;
    }

#if defined(NADIR_BASE_BINARY_TREE_DEBUG)
    typedef typename leaf_t::what_t what_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual what_t& what(branch_t* branch) const {
        if ((branch)) {
            return what(*branch);
        }
        return (what_t&)(leaf_.what());
    }
    virtual what_t& what(branch_t& branch) const {
        return branch.leaf().what();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    leaf_t leaf_;
#endif // defined(NADIR_BASE_BINARY_TREE_DEBUG)
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
    tree(branch* root): Extends(root) {
    }
    tree(const tree& copy): Extends(copy) {
    }
    tree() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace binary
} // namespace nadir 

#endif // _NADIR_BASE_BINARY_TREE_HPP 
