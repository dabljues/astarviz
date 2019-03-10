#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#include <QPoint>
#include <memory>
#include <vector>

class result_path
{
public:
    std::vector<QPoint> path;
};

class node
{
public:
    node() : G(0), H(0) {}
    node(const QPoint& p) : pos(p), G(0), H(0) {}
    bool operator==(const node& o) const { return pos == o.pos; }
    bool operator==(const QPoint& o) const { return pos == o; }
    bool operator!=(const node& o) const { return pos != o.pos; }
    bool operator<(const node& o) const { return G + H < o.G + o.H; }
    QPoint pos;
    std::shared_ptr<node> parent;
    int G;
    int H;
};

inline result_path prepare_result_path(std::shared_ptr<node> start_node,
                                       std::shared_ptr<node> current_node)
{
    auto result = result_path();
    while (*current_node != *start_node)
    {
        result.path.push_back(current_node->pos);
        current_node = current_node->parent;
    }
    result.path.push_back(start_node->pos);
    std::reverse(result.path.begin(), result.path.end());
    return result;
}

#endif  // ALGORITHM_UTILS_H
