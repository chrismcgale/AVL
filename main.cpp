#include "rangeTree.h"

int main(int argc, char** argv)
{
    int x, y;

    cout << "Input at least one point in format:x y";
    cout << "Input a non number character when done";
    while (true)
    {
        cin >> x >> y;
        if (cin.fail())
            std::cerr << "ERROR: INVALID POINT" << endl;
        else
            break;
    }
    rangeTreeX root = rangeTreeX(Point{x, y});
    while (cin >> x, y)
        root.insert(&root, Point{x, y});

    int x1, x2, y1, y2;
    while (true)
    {
        cout << "Input a rectangle to search in format:x1 y1 x2 y2" << endl;
        cout << "Or q to quit";
        while (true)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 == 'q')
                break;
            if (cin.fail())
                std::cerr << "ERROR: INVALID RANGE" << endl;
            else
                break;
        }

        if (x1 == 'q')
            break;
        root.rangeSearch(&root, Point{x1, y1}, Point{x2, y2});
    }
}