#include "avl.h"

//Constructor
BST::BST(int i, BST* parent, BST* left, BST* right) : data{i}, height{0}, parent{parent}, left{left},  right{right}
{}

//Destructor
BST::~BST()
{
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
    delete this;
}

BST* BST::insert(BST* root, int i)
{
    if(!root) return new BST(i);

    if(i > root->data) root->right = insert(root->right, i);
    else root->left = insert(root->left, i);

    return root;
}

//Updates height after insert/delete
void AVL::setHeight(AVL& z) 
{
    z.height = 1 + std::max(z.left->height, z.right->height);
}

//Rotates branches to ensure balance
AVL* AVL::rotate_right(AVL* z) 
{
    AVL* y = static_cast<AVL*>(z->left);
    z->left = y->right;
    y->right = z;
    setHeight(*z);
    setHeight(*y);
    return y;
}

//Rotates branches to ensure balance
AVL* AVL::rotate_left(AVL* z)
{
    AVL* y = static_cast<AVL*>(z->right);
    z->right = y->left;
    y->left = z;
    setHeight(*z);
    setHeight(*y);
    return y;
}

//Decides what rotatations are needed
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

//Inserts new AVL node with data i
AVL* AVL::insert(AVL* root, int i)
{
    AVL* z = static_cast<AVL*>(BST::insert(root, i));
    AVL* ret = z;
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
    return ret;
}

//Returns leftmost node from b
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

//Deletes AVL with value d or prints not found
void AVL::del(AVL * root, int d)
{
    AVL* z = static_cast<AVL*>(BST::del(root, d));
    if (z == nullptr ) cout << "Not found" << endl;
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

//Returns AVL node with value s
AVL* AVL::search(AVL* root,int s)
{
   return static_cast<AVL*>(BST::search(root, s));
}

// * Change to return boundary and topmost inside seperatly *
vector<BST*> BST::rangeSearch(BST* root, int x1, int x2)
{
    if (root == nullptr) return vector<BST*>();
    if (x2 <= root->data && root->data <= x1) {
        vector<BST*> L = BST::rangeSearch(root->left, x1, x2);
        vector<BST*> R = BST::rangeSearch(root->right, x1, x2);
        vector<BST*> ret;
        ret.reserve(L.size() + R.size() + 1);
        ret.push_back(root);
        ret.insert( ret.end(), L.begin(), L.end() );
        ret.insert( ret.end(), R.begin(), R.end() );
        return ret;
    }
    if (root->data < x1) return BST::rangeSearch(root->right, x1, x2);
    if (root->data > x2) return BST::rangeSearch(root->left, x1, x2);
}

//Returns AVL nodes with data between x1 and x2
vector<AVL*> AVL::rangeSearch(AVL* root, int x1, int x2)
{
    vector<BST*> b = BST::rangeSearch(root, x1, x2);
    vector<AVL*> a;
    for (int i = 0; i < b.size() ; ++i)
        a.push_back(static_cast<AVL*>(b[i]));
    return a;
}
