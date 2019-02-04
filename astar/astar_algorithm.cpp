#include "astar_algorithm.h"


result_path astar_algorithm::calculate(mapview* m_view)
{
    map_view = m_view;
//    auto closed_set = std::vector<node>();
//    auto open_set = std::vector<node>{_start};
    auto closed_set = std::vector<std::shared_ptr<node>>();
    auto start_node = node(_start);
    auto open_set = std::vector<std::shared_ptr<node>>{std::make_shared<node>(start_node)};
    std::map<node, node> came_from;

    std::shared_ptr<node> current;
    while (!open_set.empty())
    {
        current = *std::min_element(open_set.begin(), open_set.end());
        if (*current == _end)
        {
            // TODO: Reconstruct a result path!!!
            break;
        }
        open_set.erase(std::find(open_set.begin(), open_set.end(), current));
        closed_set.push_back(current);
        auto neighbors = get_neighbors(*current);
        for (auto &neighbor : neighbors)
        {
            if (std::find_if(closed_set.begin(), closed_set.end(), [&](std::shared_ptr<node> const& p) {
                             return *p == neighbor;
                         }) != closed_set.end()) continue;

            auto tentative_g_score = current->G + 1;

            if (std::find_if(open_set.begin(), open_set.end(), [&](std::shared_ptr<node> const& p) {
                          return *p == neighbor;
                      }) == open_set.end())
            {
                neighbor.G = tentative_g_score;
                neighbor.H = heuristic_cost_estimate(neighbor.pos, _end);
                neighbor.parent = current;
                open_set.push_back(std::make_shared<node>(neighbor));
            }
            else if (tentative_g_score < neighbor.G)
            {
                neighbor.parent = current;
                neighbor.G = tentative_g_score;
            }
//            f_score[neighbor] = g_score[neighbor] + heuristic_cost_estimate(neighbor.pos, _end);
        }
    }
    auto result = result_path();
    while (*current != start_node)
    {
        result.path.push_back(current->pos);
        current = current->parent;
    }
    result.path.push_back(start_node.pos);
    std::reverse(result.path.begin(), result.path.end());
    return result;
}

int astar_algorithm::heuristic_cost_estimate(const QPoint& start, const QPoint& end) const
{
//    Diagonal
//    return std::max(std::abs(start.x() - end.x()),
//                    std::abs(start.y() - end.y()));
    // 4 directions
    return std::abs(start.x() - end.x()) + std::abs(start.y() - end.y());
}

bool astar_algorithm::valid_point(int x, int y) const
{
    auto box_count = map_view->drawing_params.box_count;
    if (x >= 0 && y >= 0 && x < box_count && y < box_count
            && std::find(map_view->terrains.begin(),
                         map_view->terrains.end(),
                         QPoint(x, y)) == map_view->terrains.end())
    {
        return true;
    }
    return false;
}

std::vector<node> astar_algorithm::get_neighbors(node& n) const
{
    std::vector<node> neighbors;
    auto x = n.pos.x();
    auto y = n.pos.y();
    // Top
    if (valid_point(x, y - 1)) neighbors.push_back(node(QPoint(x, y - 1)));
    // Left
    if (valid_point(x - 1, y)) neighbors.push_back(node(QPoint(x - 1, y)));
    // Right
    if (valid_point(x + 1, y)) neighbors.push_back(node(QPoint(x + 1, y)));
    // Bottom
    if (valid_point(x, y + 1)) neighbors.push_back(node(QPoint(x, y + 1)));
    return neighbors;
}

 std::vector<node> astar_algorithm::get_neighbors_diagonal(node& n) const
 {
    std::vector<node> neighbors;
    auto x = n.pos.x();
    auto y = n.pos.y();
    auto box_count = map_view->drawing_params.box_count;
    for(auto r = 0; r < 3; r++)
    {
        for (auto c = 0; c < 3; c++)
        {
            if (r == 1 && c == 1) continue;
            auto pos_x = x - 1 + c;
            auto pos_y = y - 1 + r;
            if (pos_x < 0 || pos_y < 0 || pos_x >= box_count || pos_y >= box_count) continue;
            auto it = std::find(map_view->terrains.begin(), map_view->terrains.end(), QPoint(pos_x, pos_y));
            if(it != map_view->terrains.end()) continue;
            auto neighbor = node(QPoint(pos_x, pos_y));
//            neighbor.parent = &n;
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
 }
