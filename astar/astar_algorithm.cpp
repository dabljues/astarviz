#include "astar_algorithm.h"


result_path astar_algorithm::calculate()
{
    // auto closed_set =
    // auto open_set =
    std::map<node,int> came_from;
    std::map<node, int> g_score;
    std::map<node, int> f_score;
    g_score[_start] = 0;
    f_score[_start] = 0;
}
