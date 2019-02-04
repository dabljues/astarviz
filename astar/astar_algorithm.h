#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <QPoint>

#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <utility>
#include <functional>
#include <memory>
#include <set>

#include "mapview.h"

struct result_path
{
public:
    std::vector<QPoint> path;
};

class node
{
public:
    node() {}
    node(const QPoint& p) : pos(p) {}
    bool operator == (const node& o ) const { return pos.x() == o.pos.x() && pos.y() == o.pos.y(); }
    bool operator == (const QPoint& o ) const { return pos.x() == o.x() && pos.y() == o.y(); }
    bool operator != (const node& o) const {return pos.x() != o.pos.x() || pos.y() != o.pos.y(); }
    bool operator <(const node& o ) const { return G + H < o.G + o.H; }
    QPoint pos;
    std::shared_ptr<node> parent;
    int G = 0;
    int H = 0;
};

class astar_algorithm
{
    const std::vector<std::vector<bool>> _maze_matrix;
    const QPoint _start;
    const QPoint _end;
public:
    astar_algorithm() = delete;
    astar_algorithm(const std::vector<std::vector<bool>>& maze_matrix, const QPoint& start, const QPoint& end) : _maze_matrix(maze_matrix), _start(start), _end(end) {}
    result_path calculate(mapview*);
    mapview* map_view;
private:
    int heuristic_cost_estimate(const QPoint& start, const QPoint& end) const;
    std::vector<node> get_neighbors(node& n) const;
    std::vector<node> get_neighbors_diagonal(node& n) const;
    bool valid_point(int x, int y) const;
};

#endif // ASTAR_ALGORITHM_H
