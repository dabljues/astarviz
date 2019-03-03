#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#include <QPoint>
#include <memory>
#include <vector>


struct result_path
{
public:
    std::vector<QPoint> path;
};

class node
{
public:
    node() : G(0), H(0) {}
    node(const QPoint& p) : pos(p), G(0), H(0) {}
    bool operator==(const node& o) const { return pos == o.pos;}
    bool operator==(const QPoint& o) const { return pos == o; }
    bool operator!=(const node& o) const { return pos != o.pos; }
    bool operator<(const node& o) const { return  G + H < o.G + o.H; }
    QPoint pos;
    std::shared_ptr<node> parent;
    int G;
    int H;
};

#endif  // ALGORITHM_UTILS_H
