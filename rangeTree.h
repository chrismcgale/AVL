#include "avl.h"

struct Point
{
    int x;
    int y;
};

class rangeTreeY : public AVL
{
    Point val;
    rangeTreeY *left, *right;

public:
    rangeTreeY(rangeTreeX* v);
    rangeTreeY(Point v, rangeTreeX *l = nullptr, rangeTreeX *r = nullptr);
};

class rangeTreeX : public AVL
{
    Point val;
    rangeTreeX *left, *right;
    rangeTreeY *y;
    void fixY();
    vector<rangeTreeX*> boundSearch(rangeTreeX* root, int x1, int x2);
    vector<rangeTreeX*> topSearch(vector<rangeTreeX*> bound, int x1, int x2);
    ~rangeTreeX();

public:
    rangeTreeX(Point v, rangeTreeX *l = nullptr, rangeTreeX *r = nullptr);
    void insert(rangeTreeX* root, Point i);
    void del(rangeTreeX* root, Point d);
    vector<rangeTreeX*> rangeSearch(rangeTreeX* root, Point s1, Point s2);
};