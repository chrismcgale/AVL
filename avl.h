#include <algorithm>
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;

class BST {
        int data;
        int height;
        BST *left, *right, *parent;
        BST* minSub(BST* b);
        BST(int i, BST* parent = nullptr, BST* left = nullptr, BST* right = nullptr);
        ~BST();
    public:
        friend class AVL;
        BST* insert(BST* root, int i);
        BST* del(BST* root, int d);
        BST* search(BST* root, int s);
        vector<BST*> BST::rangeSearch(BST* root, int x1, int x2);
};

class AVL : public BST {
        void setHeight(AVL& z);
        AVL* restruct(AVL& x, AVL& y, AVL& z);
        AVL* rotate_left(AVL* z);
        AVL* rotate_right(AVL* z);
    public:
        AVL* insert(AVL* root, int i);
        void del(AVL* root, int d);
        AVL* search(AVL* root, int s);
        vector<AVL*> rangeSearch(AVL* root, int x1, int x2);
};