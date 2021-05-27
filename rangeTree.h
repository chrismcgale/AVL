#include "avl.h"

struct Point
{
    int x;
    int y;
};

class rangeTreeY;

class rangeTreeX : public AVL
{
    Point val;
    rangeTreeX *left, *right;
    rangeTreeY *y;
    void fixY();
    vector<rangeTreeX*> boundSearch(rangeTreeX* root, int x1, int x2);
    vector<rangeTreeX*> topSearch(vector<rangeTreeX*> bound, int x1, int x2);
public:
    rangeTreeX(Point v, rangeTreeX *l = nullptr, rangeTreeX *r = nullptr);
    ~rangeTreeX();
    void insert(rangeTreeX* root, Point i);
    void del(rangeTreeX* root, Point d);
    Point getVal() { return val; }
    rangeTreeX* getLeft() { return left; }
    rangeTreeX* getRight() { return right; }
    vector<rangeTreeX*> rangeSearch(rangeTreeX* root, Point s1, Point s2);
};

class rangeTreeY : public AVL
{
    Point val;
    rangeTreeY *left, *right;

public:
    rangeTreeY* xy(rangeTreeX* x, rangeTreeY* y = nullptr);
    void insert(rangeTreeY* root, Point i);
    rangeTreeY(rangeTreeX* v);
    rangeTreeY(Point v, rangeTreeX *l = nullptr, rangeTreeX *r = nullptr);
};
