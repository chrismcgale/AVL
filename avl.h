#include <algorithm>
#include <memory>
using std::unique_ptr;

class BST {
        int data;
        int height;
        BST *left, *right, *parent;
        BST* minSub(BST* b);
        BST(int i, BST* parent = nullptr, BST* left = nullptr, BST* right = nullptr);
    public:
        friend class AVL;
        BST* insert(BST* root, int i);
        BST* del(BST* root, int d);
        BST* search(BST* root, int s);
};

class AVL : public BST {
        void setHeight(AVL& z);
        AVL* restruct(AVL& x, AVL& y, AVL& z);
        AVL* rotate_left(AVL* z);
        AVL* rotate_right(AVL* z);
    public:
        void insert(AVL* root, int i);
        void del(AVL* root, int d);
        void search(AVL* root, int s);
};