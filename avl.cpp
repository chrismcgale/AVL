#include "avl.h"

BST::BST(int i, BST* parent, BST* left, BST* right) : data{i}, height{0}, parent{parent}, left{left},  right{right}
{}

BST* BST::insert(BST* root, int i)
{
    if(!root) return new BST(i);

    if(i > root->data) root->right = insert(root->right, i);
    else root->left = insert(root->left, i);

    return root;

}

void AVL::setHeight(AVL& z) 
{
    z.height = 1 + std::max(z.left->height, z.right->height);
}

AVL* AVL::rotate_right(AVL* z) 
{
    AVL* y = static_cast<AVL*>(z->left);
    z->left = y->right;
    y->right = z;
    setHeight(*z);
    setHeight(*y);
    return y;
}

AVL* AVL::rotate_left(AVL* z)
{
    AVL* y = static_cast<AVL*>(z->right);
    z->right = y->left;
    y->left = z;
    setHeight(*z);
    setHeight(*y);
    return y;
}

AVL* AVL::restruct(AVL& x, AVL& y, AVL& z) 
{
    if (x.data < y.data  && y.data < z.data) return rotate_right(&z);

    if(x.data > y.data  && y.data < z.data) {
        z.left = rotate_left(&y);
        return rotate_right(&z);
    }

    if(x.data < y.data  && y.data > z.data) {
        z.right = rotate_right(&y);
        return rotate_left(&z);
    }

    else return rotate_left(&z);
}

void AVL::insert(AVL* root, int i)
{
    AVL* z = static_cast<AVL*>(BST::insert(root, i));
    while (z != nullptr) {
        if (z->left != nullptr && z->right != nullptr) {
            if (std::abs(z->left->height - z->right->height) > 1) {
            AVL * y = (z->left->height > z->right->height) ? static_cast<AVL*>(z->left) : static_cast<AVL*>(z->right);
            AVL * x = (y->left->height > y->right->height) ? static_cast<AVL*>(y->left) : static_cast<AVL*>(y->right);
            z = restruct(*x, *y, *z);
            break;
        }
        }
        setHeight(*z);
        z = static_cast<AVL*>(z->parent);
    } 
}

BST* BST::minSub(BST* b)
{
    BST* curr = b;
    while (curr && curr->left != nullptr) curr = curr->left;
    return curr;
}



BST* BST::del(BST* root, int d)
{
    if (root == nullptr) return root;
    if (d < root->data) root->left = BST::del(root->left, d);
    else if ( d > root->data) root->right = BST::del(root->right, d);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if(root->left == nullptr) {    
            BST* temp = root->right;
            BST* par = root->parent;
            if (par != nullptr) {
                if( par->left == root) par->left = temp;
                else par->right = temp;
            }
            delete root;
            return temp;
        }
        else if(root->right == nullptr) {
            BST* temp = root->left;
            BST* par = root->parent;
            if (par != nullptr) {
                if( par->left == root) par->left = temp;
                else par->right = temp;
            }
            delete root;
            return temp;
        }

        BST* temp = minSub(root->right);
        root->data = temp->data;
        BST::del(root->right, temp->data);
    }
    return root;
}

void AVL::del(AVL * root, int d)
{
    AVL* z = static_cast<AVL*>(BST::del(root, d));
    while (z != nullptr) {
        if (z->left != nullptr && z->right != nullptr) {
            if (std::abs(z->left->height - z->right->height) > 1) {
            AVL * y = (z->left->height > z->right->height) ? static_cast<AVL*>(z->left) : static_cast<AVL*>(z->right);
            AVL * x = (y->left->height > y->right->height) ? static_cast<AVL*>(y->left) : static_cast<AVL*>(y->right);
            z = restruct(*x, *y, *z);
            break;
        }
        }
        setHeight(*z);
        z = static_cast<AVL*>(z->parent);
    }
}

BST* BST::search(BST* root, int s)
{
    if (root == nullptr || root->data == s) return root;
    if (root->data < s) return BST::search(root->right, s);
    else return BST::search(root->left, s);
}

void AVL::search(AVL* root,int s)
{
    BST::search(root, s);
}
