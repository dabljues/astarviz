#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H

#include <QPoint>

#include <algorithm>
#include <array>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>

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
    void set_visualization_grid(mapview* m) { map_view = m; }
    void set_visualization(bool viz) { visualization = viz; }
    result_path calculate(int dirs = 4);
    mapview* map_view = nullptr;

private:
    bool visualization = false;
    int directions;
    int heuristic_cost_estimate(const QPoint& start, const QPoint& end) const;
    std::vector<std::shared_ptr<node>> get_neighbors(node& n) const;
    std::vector<QPoint> _get_neighbors(node& n) const;
    std::vector<node> get_neighbors_diagonal(node& n) const;
    bool valid_point(int x, int y) const;
    void draw_change(const node& n) const
    {
        map_view->drawVisited(n);
        qApp->processEvents();
    }
    result_path _calculate(int dirs);
    result_path _calculate_visualization(int dirs);
};

#endif  // ASTAR_ALGORITHM_H
