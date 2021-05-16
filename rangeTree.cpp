#include "rangeTree.h"

rangeTreeY::rangeTreeY(rangeTreeX* v)
{
    
}

rangeTreeY::rangeTreeY(Point v, rangeTreeX* l, rangeTreeX* r) : val{v}, left{l}, right{r}
{
}

rangeTreeX::rangeTreeX(Point v, rangeTreeX* l, rangeTreeX* r) : val{v}, left{l}, right{r}
{
    y = new rangeTreeY(v,l,r);
}

rangeTreeX::~rangeTreeX()
{
    if ( y != nullptr ) delete y;
    if ( left != nullptr ) delete left;
    if ( right != nullptr ) delete right;
    delete this;
}

void rangeTreeX::fixY()
{
    if(y != nullptr )delete y;
    y = new rangeTreeY(val,left,right);
    left->fixY();
    right->fixY();
}


void rangeTreeX::insert(rangeTreeX* root, Point i)
{
    rangeTreeX* z = static_cast<rangeTreeX*>(AVL::insert(root, i.x));
    z->val = i;
    root->fixY();
}

vector<rangeTreeX*> rangeTreeX::boundSearch(rangeTreeX* root, int x1, int x2)
{
    vector<rangeTreeX*> ret;
    vector<rangeTreeX*> L;
    vector<rangeTreeX*> R;
    if (root == nullptr) return ret;
    if (root->val.x > x1) L = boundSearch(root->left, x1, x2);
    if (root->val.x < x2) R = boundSearch(root->right, x1, x2);
    if (root->val.x >= x1 && root->val.x <= x2) ret.push_back(root);
    ret.reserve(L.size() + R.size() + 1);
    ret.insert( ret.end(), L.begin(), L.end() );
    ret.insert( ret.end(), R.begin(), R.end() );
    return ret;
}


vector<rangeTreeX*> rangeTreeX::topSearch(vector<rangeTreeX*> bound, int x1, int x2)
{
    vector<rangeTreeX*> ret;
    for(int i = 0; i < bound.size(); ++i) {
        if (bound[i]->left && !std::find(bound[i]->left, bound.begin(), bound.end()))
            ret.push_back(bound[i]->left);
        else if (bound[i]->right && !std::find(bound[i]->right, bound.begin(), bound.end())) 
            ret.push_back(bound[i]->right);
    }
    return ret;
}

vector<rangeTreeX*> rangeTreeX::rangeSearch(rangeTreeX* root, Point s1, Point s2)
{
    vector<rangeTreeX*> bound = boundSearch(root, s1.x, s2.x);
    vector<rangeTreeX*> top = topSearch(bound, s1.x, s2.x);
    vector<rangeTreeX*> ret;
    for (int j = 0; j < bound.size(); ++j)
        if (bound[j]->val.y >= s1.y && bound[j]->val.y <= s2.y) ret.push_back(bound[i]);
    for (int k = 0; k < top.size(); ++k)
        //BST::rangeSearch(top[k]->y, s1.y, s2.y)
        //Adjoin when returns rangeTreeXs
    return ret;
}