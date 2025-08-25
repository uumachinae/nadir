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
#ifndef _NADIR_BASE_AVL_TREE_HPP
#define _NADIR_BASE_AVL_TREE_HPP

#include "nadir/base/avl/branch.hpp"
#include "nadir/base/binary/tree.hpp"

#if !defined(NADIR_BASE_AVL_TREE_DEBUG)
#define AVL_TREE_LOG_MESSAGE_DEBUG(args)
#else // !defined(NADIR_BASE_AVL_TREE_DEBUG)
#define AVL_TREE_LOG_MESSAGE_DEBUG(args) LOG_MESSAGE_DEBUG(args)
#endif // !defined(NADIR_BASE_AVL_TREE_DEBUG)

namespace nadir {
namespace avl {

class _EXPORT_CLASS tree;
typedef binary::tree_implements tree_implements;
typedef binary::treet
<leaf, branch, tree, tree_implements, treet
<leaf, branch, tree, tree_implements, tree_extends> > tree_extends;
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
        branch.set_depth(1);
        branch.set_tree(0);
        branch.set_left(0);
        branch.set_right(0);
        AVL_TREE_LOG_MESSAGE_DEBUG("insert \"" << this->what(&branch) << "\"...");
        this->set_root(inserted(this->root(), &branch));
        AVL_TREE_LOG_MESSAGE_DEBUG("...insert \"" << this->what(&branch) << "\"");
        return &branch;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* remove(branch_t& branch) {
        AVL_TREE_LOG_MESSAGE_DEBUG("remove \"" << this->what(&branch) << "\"...");
        this->set_root(removed(this->root(), &branch));
        branch.set_depth(1);
        branch.set_tree(0);
        branch.set_left(0);
        branch.set_right(0);
        AVL_TREE_LOG_MESSAGE_DEBUG("...remove \"" << this->what(&branch) << "\"");
        return &branch;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* inserted(branch_t* tree, branch_t* branch) {
        if ((tree)) {
            if ((branch)) {
                if (branch->compare(*tree) < 0) {
                    AVL_TREE_LOG_MESSAGE_DEBUG("compared \"" << this->what(branch) << "\"(" << branch->depth() << ") < \"" << this->what(tree) << "\"(" << tree->depth() << ")");
                    tree->set_left(inserted(tree->left(), branch));
                    tree->left()->set_tree(tree);
                    if (depth(tree->left()) - depth(tree->right()) > 1) {
                        if (depth(tree->left()->right()) > depth(tree->left()->left())) {
                            tree->set_left(left(tree->left()));
                        }
                        return right(tree);
                    } else {
                        tree->set_depth(tree->left()->depth() + 1);
                    }
                } else {
                    AVL_TREE_LOG_MESSAGE_DEBUG("compared \"" << this->what(branch) << "\"(" << branch->depth() << ") >= \"" << this->what(tree) << "\"(" << tree->depth() << ")");
                    tree->set_right(inserted(tree->right(), branch));
                    tree->right()->set_tree(tree);
                    if (depth(tree->right()) - depth(tree->left()) > 1) {
                        if (depth(tree->right()->left()) > depth(tree->right()->right())) {
                            tree->set_right(right(tree->right()));
                        }
                        return left(tree);
                    } else {
                        tree->set_depth(tree->right()->depth() + 1);
                    }
                }
            }
        } else {
            return branch;
        }
        return tree;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* removed(branch_t* tree, branch_t* branch) {
        if ((tree) && (branch)) {
            int c = 0;
            if ((c = branch->compare(*tree)) > 0) {
                    AVL_TREE_LOG_MESSAGE_DEBUG("compared \"" << this->what(branch) << "\"(" << branch->depth() << ") > \"" << this->what(tree) << "\"(" << tree->depth() << ")");
                tree->set_right(removed(tree->right(),branch));
                if (depth(tree->left()) - depth(tree->right()) > 1) {
                    if (depth(tree->left()->right()) > depth(tree->left()->left())) {
                        tree->set_left(left(tree->left()));
                    }
                    tree = right(tree);
                } else {
                    tree->set_depth(new_depth(tree));
                }
            } else {
                if ((c) < 0) {
                    AVL_TREE_LOG_MESSAGE_DEBUG("compared \"" << this->what(branch) << "\"(" << branch->depth() << ") < \"" << this->what(tree) << "\"(" << tree->depth() << ")");
                    tree->set_left(removed(tree->left(),branch));
                    if (depth(tree->right()) - depth(tree->left()) > 1) {
                        if (depth(tree->right()->left()) > depth(tree->right()->right())) {
                            tree->set_right(right(tree->right()));
                        }
                        tree = left(tree);
                    }
                    else {
                        tree->set_depth(new_depth(tree));
                    }
                } else {
                    AVL_TREE_LOG_MESSAGE_DEBUG("compared \"" << this->what(branch) << "\"(" << branch->depth() << ") = \"" << this->what(tree) << "\"(" << tree->depth() << ")");
                    if (branch->depth() > 1) {
                        if (depth(branch->right()) > depth(branch->left())) {
                            tree = least(&(branch->right()));
                        } else {
                            tree = greatest(&(branch->left()));
                        }
                        tree->set_depth(new_depth(branch));
                        tree->set_tree(branch->tree());
                        if ((tree->set_left(branch->left()))) {
                            tree->left()->set_tree(tree);
                        }
                        if ((tree->set_right(branch->right()))) {
                            tree->right()->set_tree(tree);
                        }
                    } else {
                        tree = 0;
                    }
                }
            }
        }
        return tree;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* least(branch_t** tree) {
        branch_t* t = 0;
        if ((*tree)->left()) {
            t = least(&((*tree)->left()));
            if (depth((*tree)->right()) - depth((*tree)->left()) > 1) {
                if (depth((*tree)->right()->left()) > depth((*tree)->right()->right())) {
                    (*tree)->set_right(right((*tree)->right()));
                }
                *tree = left(*tree);
            } else {
                (*tree)->set_depth(new_depth(*tree));
            }
        } else {
            if ((*tree)->right()) {
                t = *tree;
                *tree = t->right();
                (*tree)->set_tree(t->tree());
            } else {
                t = *tree;
                *tree = 0;
            }
        }
        return t;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* greatest(branch_t** tree) {
        branch_t* t = 0;
        if ((*tree)->right()) {
            t = greatest(&((*tree)->right()));
            if (depth((*tree)->left()) - depth((*tree)->right()) > 1) {
                if (depth((*tree)->left()->right()) > depth((*tree)->left()->left())) {
                    (*tree)->set_left(left((*tree)->left()));
                }
                *tree = right(*tree);
            } else {
                (*tree)->set_depth(new_depth(*tree));
            }
        } else {
            if ((*tree)->left()) {
                t = *tree;
                *tree = t->left();
                (*tree)->set_tree(t->tree());
            } else {
                t = *tree;
                *tree = 0;
            }
        }
        return t;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* left(branch_t* tree) {
        branch_t* right = 0;
        if ((tree)) {
            AVL_TREE_LOG_MESSAGE_DEBUG("left \"" << this->what(tree) << "\"(" << tree->depth() << ")");
            if ((right = tree->right())) {
                if ((tree->set_right(right->left()))) {
                    tree->right()->set_tree(tree);
                }
                tree->set_depth(depth(tree->left())+1);

                if (depth(tree->right()) >= tree->depth()) {
                    tree->set_depth(tree->right()->depth()+1);
                }
                right->set_depth(tree->depth()+1);
                right->set_left(tree);
                right->set_tree(tree->tree());
                tree->set_tree(right);
            }
        }
        return right;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual branch_t* right(branch_t* tree) {
        branch_t* left = 0;
        if ((tree)) {
            AVL_TREE_LOG_MESSAGE_DEBUG("right \"" << this->what(tree) << "\"(" << tree->depth() << ")");
            if ((left = tree->left())) {
                if ((tree->set_left(left->right()))) {
                    tree->left()->set_tree(tree);
                }
                tree->set_depth(depth(tree->right())+1);

                if (depth(tree->left()) >= tree->depth()) {
                    tree->set_depth(tree->left()->depth()+1);
                }
                left->set_depth(tree->depth()+1);
                left->set_right(tree);
                left->set_tree(tree->tree());
                tree->set_tree(left);
            }
        }
        return left;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int new_depth(const branch_t* tree) const {
        int depth = 0;
        if ((tree)) {
            int rDepth = 0;
            if ((depth = this->depth(tree->left()))
                 > (rDepth = this->depth(tree->right()))) {
                depth += 1;
            } else {
                depth = rDepth + 1;
            }
        }
        return depth;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int depth(const branch_t* tree) const {
        int depth = 0;
        if ((tree)) {
            if ((1 > (depth = tree->depth()))) {
                depth = 1;
            }
        }
        return depth;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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
    virtual ~tree() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace avl
} // namespace nadir 

#endif // _NADIR_BASE_AVL_TREE_HPP 
