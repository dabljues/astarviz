#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <QPoint>

#include <algorithm>
#include <array>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <thread>

#include "algorithm_utils.h"
#include "mapview.h"

class astar_algorithm
{
    const std::vector<std::vector<bool>> _maze_matrix;
    const QPoint _start;
    const QPoint _end;

public:
    astar_algorithm() = delete;
    astar_algorithm(const std::vector<std::vector<bool>>& maze_matrix, const QPoint& start,
                    const QPoint& end)
        : _maze_matrix(maze_matrix), _start(start), _end(end)
    {
    }
    result_path calculate(mapview*, int dirs = 4);
    mapview* map_view;

private:
    int directions;
    int heuristic_cost_estimate(const QPoint& start, const QPoint& end) const;
    std::vector<std::shared_ptr<node>> get_neighbors(node& n) const;
    std::vector<QPoint> _get_neighbors(node& n) const;
    std::vector<node> get_neighbors_diagonal(node& n) const;
    bool valid_point(int x, int y) const;
    void draw_change(const node &n)
    {
        map_view->drawVisited(n);
        qApp->processEvents();
    }
};

#endif  // ASTAR_ALGORITHM_H
