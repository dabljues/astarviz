#include "astar_algorithm.h"

result_path astar_algorithm::calculate(mapview *m_view, int dirs)
{
    map_view = m_view;
    directions = dirs;
    auto closed_set = std::vector<std::shared_ptr<node>>();
    auto start_node = std::make_shared<node>(_start);
    auto open_set = std::vector<std::shared_ptr<node>>{start_node};

    std::shared_ptr<node> current;
    while (!open_set.empty())
        {
            current = *std::min_element(
                open_set.begin(), open_set.end(),
                [&](const std::shared_ptr<node> &lhs, const std::shared_ptr<node> &rhs) {
                    return lhs->G + lhs->H < rhs->G + rhs->H;
                });

            if (*current == _end) break;

            draw_change(*current);

            open_set.erase(std::find(open_set.begin(), open_set.end(), current));
            closed_set.push_back(current);

            auto neighbors = _get_neighbors(*current);

            for (auto &neighbor : neighbors)
                {
                    if (std::find_if(closed_set.begin(), closed_set.end(),
                                     [&](std::shared_ptr<node> const &p) {
                                         return p->pos == neighbor;
                                     }) != closed_set.end())
                        continue;

                    auto tentative_g_score = current->G + 1;

                    auto exists_in_set = std::find_if(
                        open_set.begin(), open_set.end(),
                        [&](std::shared_ptr<node> const &p) { return p->pos == neighbor; });
                    if (exists_in_set == open_set.end())
                        {
                            auto n = std::make_shared<node>(QPoint(neighbor.x(), neighbor.y()));
                            n->G = tentative_g_score;
                            n->H = heuristic_cost_estimate(neighbor, _end);
                            n->parent = current;
                            open_set.push_back(std::move(n));
                        }
                    else if (tentative_g_score < (*exists_in_set)->G)
                        {
                            (*exists_in_set)->parent = current;
                            (*exists_in_set)->G = tentative_g_score;
                        }
                }
        }
    auto result = result_path();
    while (*current != *start_node)
        {
            result.path.push_back(current->pos);
            current = current->parent;
        }
    result.path.push_back(start_node->pos);
    std::reverse(result.path.begin(), result.path.end());
    return result;
}

int astar_algorithm::heuristic_cost_estimate(const QPoint &start, const QPoint &end) const
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
    if (x >= 0 && y >= 0 && x < box_count && y < box_count &&
        std::find(map_view->terrains.begin(), map_view->terrains.end(), QPoint(x, y)) ==
            map_view->terrains.end())
        {
            return true;
        }
    return false;
}

std::vector<QPoint> astar_algorithm::_get_neighbors(node &n) const
{
    std::vector<QPoint> neighbors;
    auto x = n.pos.x();
    auto y = n.pos.y();
    // Top
    if (valid_point(x, y - 1)) neighbors.push_back(QPoint(x, y - 1));
    // Left
    if (valid_point(x - 1, y)) neighbors.push_back(QPoint(x - 1, y));
    // Right
    if (valid_point(x + 1, y)) neighbors.push_back(QPoint(x + 1, y));
    // Bottom
    if (valid_point(x, y + 1)) neighbors.push_back(QPoint(x, y + 1));
    return neighbors;
}

std::vector<std::shared_ptr<node>> astar_algorithm::get_neighbors(node &n) const
{
    std::vector<std::shared_ptr<node>> neighbors;
    auto x = n.pos.x();
    auto y = n.pos.y();
    // Top
    if (valid_point(x, y - 1)) neighbors.push_back(std::make_shared<node>((QPoint(x, y - 1))));
    // Left
    if (valid_point(x - 1, y)) neighbors.push_back(std::make_shared<node>((QPoint(x - 1, y))));
    // Right
    if (valid_point(x + 1, y)) neighbors.push_back(std::make_shared<node>((QPoint(x + 1, y))));
    // Bottom
    if (valid_point(x, y + 1)) neighbors.push_back(std::make_shared<node>((QPoint(x, y + 1))));
    return neighbors;
}

std::vector<node> astar_algorithm::get_neighbors_diagonal(node &n) const
{
    std::vector<node> neighbors;
    auto x = n.pos.x();
    auto y = n.pos.y();
    auto box_count = map_view->drawing_params.box_count;
    for (auto r = 0; r < 3; r++)
        {
            for (auto c = 0; c < 3; c++)
                {
                    if (r == 1 && c == 1) continue;
                    auto pos_x = x - 1 + c;
                    auto pos_y = y - 1 + r;
                    if (pos_x < 0 || pos_y < 0 || pos_x >= box_count || pos_y >= box_count)
                        continue;
                    auto it = std::find(map_view->terrains.begin(), map_view->terrains.end(),
                                        QPoint(pos_x, pos_y));
                    if (it != map_view->terrains.end()) continue;
                    auto neighbor = node(QPoint(pos_x, pos_y));
                    //            neighbor.parent = &n;
                    neighbors.push_back(neighbor);
                }
        }
    return neighbors;
}
