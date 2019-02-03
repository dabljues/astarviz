#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H
#include <vector>
#include <map>
#include <QPoint>

struct result_path
{
    std::vector<QPoint> path;
};

class node
{
public:
    node(const QPoint& p) : pos(p) {}
    bool operator == (const node& o ) { return pos == o.pos; }
    bool operator == (const QPoint& o ) { return pos == o; }
    bool operator < (const node& o ) { return dist + cost < o.dist + o.cost; }
    QPoint pos, parent;
    int dist, cost;
};

class astar_algorithm
{
    const std::vector<std::vector<bool>> _maze_matrix;
    const QPoint _start;
    const QPoint _end;
public:
    astar_algorithm() = delete;
    astar_algorithm(const std::vector<std::vector<bool>>& maze_matrix, const QPoint& start, const QPoint& end) : _maze_matrix(maze_matrix), _start(start), _end(end) {}
    result_path calculate();
};

#endif // ASTAR_ALGORITHM_H
