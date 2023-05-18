#include <iostream>
#include <cmath>
#include <queue>
#include <map>
#include <chrono>
#include "npuzzle.h"
const int move_direction[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int puzzle_size = 8;
const int side_length = sqrt(puzzle_size + 1);
int test_case[8][3][3] = {
    {{1,2,3},{4,5,6},{7,8,0}},
    {{1,2,3},{4,5,6},{0,7,8}},
    {{1,2,3},{5,0,6},{4,7,8}},
    {{1,3,6},{5,0,2},{4,7,8}},
    {{1,3,6},{5,0,7},{4,8,2}},
    {{1,6,7},{5,0,3},{4,8,2}},
    {{7,1,2},{4,8,5},{6,3,0}},
    {{0,7,2},{4,6,1},{3,5,8}}  
};
int tmp, lens = 0, max_len = 0, expanded = 0;
// tmp: test case number; lens: number of frontier nodes; max_len: maximum frontier node
// expanded: number of nodes expanded
priority_queue<puzzle*, vector<puzzle*>, Less> nodes;
map<puzzle*, int, Mat_Less> visit; // record accessed puzzle

void expand_nodes_to_queue(puzzle *puz, int heuristic) { 
// Add the expanded new nodes (at most 4) to the queue
    int x, y; // '0' position
    for (int i = 0; i < side_length; i++)
        for (int j = 0; j < side_length; j++) 
            if (puz->matrix[i][j] == 0) {x = i, y = j; break;}
    for (int i = 0; i < 4; i++) { // four direction
        int px = x + move_direction[i][0], py = y + move_direction[i][1];
        if (px < 0 || px >= side_length || py < 0 || py >= side_length) continue;
        puzzle *new_puz = puz->swap_empty(x, y, px, py, heuristic); // move blank and generate node
        if (visit[new_puz] && visit[new_puz] <= new_puz->fval) continue;
        // use map to reduce redundant: when new puz is found in map and fval<=puz->fval, ignore puz 
        nodes.push(new_puz); 
        visit[new_puz] = new_puz->fval;
        // if we want to run version without map, just comment out line 36 & 39
        new_puz->from = puz;
        ++lens;
    }
}

void show_move_process(puzzle* puz, bool flag) {
    if (puz->from != nullptr)
        show_move_process(puz->from, 0);
    puz->print();
    if (!flag) printf("  |\n  V\n");
}

void A_star_search(puzzle* puz, int heuristic) { 
//0 for uniform cost search, 1 for misplaced tile heuristic, 2 for manhattan distance heuristic
    puz->cal_val(heuristic);
    nodes.push(puz);
    visit[puz] = puz->fval;
    ++lens;
    int id = 0;
    while (!nodes.empty()) {
        puzzle *node = nodes.top();
        nodes.pop();
        --lens, ++expanded; // expanded++, queue_length--
        if (lens + 1 > max_len) // update maximun frontier node
            max_len = lens + 1;
        if (node->is_goal()) {
            printf("Reach goal state!\n");
            printf("Move Process: \n");
            show_move_process(node, true);
            printf("Depth: %d\nNumber of nodes expanded: %d\nNumber of maximum frontier node: %d\n", node->gval, expanded, max_len);
            return;
        }
        expand_nodes_to_queue(node, heuristic);
    }
}

int main() {
    if (side_length * side_length - 1 != puzzle_size) {
        printf("Wrong Puzzle Size\n");
        return 0;
    }
    puzzle* puz = new puzzle(side_length);
    if (puzzle_size == 8) {
        printf("There are 8 default test cases (number from 0 to 7)\n\n");
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < side_length; j++) {
                if (j == 0) printf("%d\t[", i);
                else printf(" \t[");
                for (int k = 0; k < side_length; k++)
                    printf("%d%c", test_case[i][j][k], k == side_length - 1 ? ']' : ',');
                printf("\n");
            }
        printf("\nEnter \'0-7\' to use one test case, \'8\' to use the puzzle you created: \n");
        scanf("%d", &tmp);
        if (0 <= tmp && tmp <= 7) puz->copy_matrix((int *)test_case[tmp]);
        else puz->read_matrix();
    }
    else puz->read_matrix();
    puz->print();
    printf("Enter \'0\' to use the Uniform Cost Search algorithm, \'1\' to use the A* with the Misplaced Tile heuristic, \'2\' to use the A* with the Manhattan Distance heuristic: \n");
    scanf("%d", &tmp);
    auto start = std::chrono::high_resolution_clock::now();
    A_star_search(puz, tmp);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // calcualte time
    std::cout << "Time taken by program: " << duration.count() << " milliseconds" << std::endl; // output running time
    return 0;
}