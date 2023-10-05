#include <iostream>
#include <bits/stdc++.h>

using namespace std;

map<tuple<char, char>, int> graph;

int heuristic(char node) {
    switch (node) {
        case 'A':
            return 9;
        case 'B':
            return 10;
        case 'C':
            return 13;
        case 'D':
            return 9;
        case 'E':
            return 19;
        case 'F':
            return 6;
        case 'H':
            return 9;
        case 'I':
            return 15;
        case 'J':
            return 11;
        case 'K':
            return 14;
        case 'L':
            return 2;
        case 'M':
            return 6;
        case 'N':
            return 4;
        case 'O':
            return 6;
        case 'P':
            return 11;
        case 'Q':
        case 'R':
            return 4;
        case 'S':
            return 12;
        case 'G':
        default:
            return 0;
    }
}

string get_neighbours(char node) {
    switch (node) {
        case 'S':
            return "CHJM";
        case 'A':
            return "BCD";
        case 'B':
            return "AF";
        case 'C':
            return "ADHS";
        case 'D':
            return "ACFH";
        case 'E':
            return "IK";
        case 'F':
            return "BDHL";
        case 'H':
            return "CDFMS";
        case 'I':
            return "EJK";
        case 'J':
            return "IKOPS";
        case 'K':
            return "EIJP";
        case 'L':
            return "FGN";
        case 'M':
            return "HOS";
        case 'N':
            return "GLQ";
        case 'O':
            return "JMPR";
        case 'P':
            return "JKO";
        case 'Q':
            return "GNR";
        case 'R':
            return "GOQ";
        case 'G':
            return "LNQR";
        default:
            return "";
    }
}

void init_graph(map<tuple<char, char>, int> &g) {
    g[make_tuple('A', 'B')] = 4;
    g[make_tuple('A', 'C')] = 16;
    g[make_tuple('A', 'D')] = 20;

    g[make_tuple('B', 'A')] = 4;
    g[make_tuple('B', 'F')] = 8;

    g[make_tuple('C', 'A')] = 16;
    g[make_tuple('C', 'D')] = 6;
    g[make_tuple('C', 'H')] = 6;
    g[make_tuple('C', 'S')] = 6;

    g[make_tuple('D', 'A')] = 20;
    g[make_tuple('D', 'C')] = 6;
    g[make_tuple('D', 'F')] = 4;
    g[make_tuple('D', 'H')] = 6;

    g[make_tuple('E', 'I')] = 6;
    g[make_tuple('E', 'K')] = 6;

    g[make_tuple('F', 'B')] = 8;
    g[make_tuple('F', 'D')] = 4;
    g[make_tuple('F', 'H')] = 16;
    g[make_tuple('F', 'L')] = 6;

    g[make_tuple('G', 'L')] = 4;
    g[make_tuple('G', 'N')] = 6;
    g[make_tuple('G', 'Q')] = 6;
    g[make_tuple('G', 'R')] = 10;

    g[make_tuple('H', 'S')] = 16;
    g[make_tuple('H', 'C')] = 6;
    g[make_tuple('H', 'D')] = 6;
    g[make_tuple('H', 'F')] = 16;
    g[make_tuple('H', 'M')] = 4;

    g[make_tuple('I', 'K')] = 6;
    g[make_tuple('I', 'E')] = 6;
    g[make_tuple('I', 'J')] = 24;

    g[make_tuple('J', 'I')] = 24;
    g[make_tuple('J', 'K')] = 24;
    g[make_tuple('J', 'P')] = 24;
    g[make_tuple('J', 'S')] = 6;
    g[make_tuple('J', 'O')] = 10;

    g[make_tuple('K', 'E')] = 6;
    g[make_tuple('K', 'I')] = 6;
    g[make_tuple('K', 'J')] = 24;
    g[make_tuple('K', 'P')] = 6;

    g[make_tuple('L', 'F')] = 6;
    g[make_tuple('L', 'N')] = 6;
    g[make_tuple('L', 'G')] = 4;

    g[make_tuple('M', 'H')] = 4;
    g[make_tuple('M', 'O')] = 16;
    g[make_tuple('M', 'S')] = 16;

    g[make_tuple('N', 'L')] = 6;
    g[make_tuple('N', 'G')] = 6;
    g[make_tuple('N', 'Q')] = 6;

    g[make_tuple('O', 'R')] = 8;
    g[make_tuple('O', 'M')] = 16;
    g[make_tuple('O', 'J')] = 10;
    g[make_tuple('O', 'P')] = 16;

    g[make_tuple('P', 'O')] = 16;
    g[make_tuple('P', 'J')] = 24;
    g[make_tuple('P', 'K')] = 6;

    g[make_tuple('Q', 'N')] = 6;
    g[make_tuple('Q', 'G')] = 6;
    g[make_tuple('Q', 'R')] = 6;

    g[make_tuple('R', 'O')] = 8;
    g[make_tuple('R', 'Q')] = 6;
    g[make_tuple('R', 'G')] = 10;

    g[make_tuple('S', 'J')] = 6;
    g[make_tuple('S', 'C')] = 6;
    g[make_tuple('S', 'H')] = 16;
    g[make_tuple('S', 'M')] = 16;
}

int edge_cost(char n1, char n2) {
    return graph[make_tuple(n1, n2)];
}

void BFS(char start) {
    list<char> frontier;
    set<char> explored;
    map<char, char> parent;

    char goal = 'G';

    frontier.push_back(start);
    parent[start] = '-';
    int iteration = 0;

    while (!frontier.empty()) {
        iteration++;
        cout << "Iteration " << iteration << endl;
        cout << "Frontier: {";
        for (auto i: frontier) {
            cout << i << ", ";
        }
        cout << "\b\b}" << endl;

        if (!explored.empty()) {
            cout << "Explored: {";
            for (auto i: explored) {
                cout << "(" << i << ", " << parent[i] << "), ";
            }
            cout << "\b\b}" << endl;
        } else { cout << "Explored: {}" << endl; }

        auto node = frontier.front();
        frontier.pop_front();

        cout << "Node removed: " << node << endl;
        explored.insert(node);

        if (node == goal) {
            cout << "\nGoal found!" << endl;
            vector<char> path;
            while (node != start) {
                node = parent[node];
                path.push_back(node);
            }
            std::reverse(path.begin(), path.end());
            cout << "Path : {";
            for (auto n: path) {
                cout << n << ", ";
            }
            cout << goal << "}" << endl;
            return;
        } else {
            cout << "Neighbours: {";
            for (auto neighbour: get_neighbours(node)) {
                cout << "(" << neighbour << ", ";
                auto exp_it = explored.find(neighbour);
                auto fro_it = find(frontier.begin(), frontier.end(), neighbour);
                if (exp_it == explored.end() && fro_it == frontier.end()) {
                    cout << "not found), ";
                    frontier.push_back(neighbour);
                    parent[neighbour] = node;
                } else {
                    cout << "found), ";
                }
            }
            cout << "\b\b}" << endl;
        }
        cout << endl;
    }
}

void DFS(char start) {
    list<char> frontier;
    set<char> explored;
    map<char, char> parent;

    char goal = 'G';

    frontier.push_back(start);
    parent[start] = '-';
    int iteration = 0;

    while (!frontier.empty()) {
        iteration++;
        cout << "Iteration " << iteration << endl;
        cout << "Frontier: {";
        for (auto i: frontier) {
            cout << i << ", ";
        }
        cout << "\b\b}" << endl;

        if (!explored.empty()) {
            cout << "Explored: {";
            for (auto i: explored) {
                cout << "(" << i << ", " << parent[i] << "), ";
            }
            cout << "\b\b}" << endl;
        } else { cout << "Explored: {}" << endl; }

        auto node = frontier.back();
        frontier.pop_back();

        cout << "Node removed: " << node << endl;
        explored.insert(node);

        if (node == goal) {
            cout << "\nGoal found!" << endl;
            vector<char> path;
            while (node != start) {
                node = parent[node];
                path.push_back(node);
            }
            std::reverse(path.begin(), path.end());
            cout << "Path : {";
            for (auto n: path) {
                cout << n << ", ";
            }
            cout << goal << "}" << endl;
            return;
        } else {
            cout << "Neighbours: {";
            for (auto neighbour: get_neighbours(node)) {
                cout << "(" << neighbour << ", ";
                auto exp_it = explored.find(neighbour);
                auto fro_it = find(frontier.begin(), frontier.end(), neighbour);
                if (exp_it == explored.end() && fro_it == frontier.end()) {
                    cout << "not found), ";
                    frontier.push_back(neighbour);
                    parent[neighbour] = node;
                } else {
                    cout << "found), ";
                }
            }
            cout << "\b\b}" << endl;
        }
        cout << endl;
    }
}

void GBFS(char start) {
    list<char> frontier;
    set<char> explored;
    map<char, char> parent;

    char goal = 'G';

    frontier.push_back(start);
    parent[start] = '-';

    int iteration = 0;

    while (!frontier.empty()) {
        iteration++;
        cout << "Iteration " << iteration << endl;

        cout << "Frontier: {";
        for (auto i: frontier) {
            cout << "(" << i << ", " << heuristic(i) << "), ";
        }
        cout << "\b\b}" << endl;

        if (!explored.empty()) {
            cout << "Explored: {";
            for (auto i: explored) {
                cout << "(" << i << ", " << parent[i] << "), ";
            }
            cout << "\b\b}" << endl;
        } else { cout << "Explored: {}" << endl; }

        auto node_it = min_element(frontier.begin(), frontier.end(), [](char a, char b) -> bool {
            return (heuristic(a) < heuristic(b));
        });
        auto node = *node_it;
        frontier.erase(node_it);

        cout << "Node removed: " << node << endl;
        explored.insert(node);

        if (node == goal) {
            cout << "\nGoal found!" << endl;
            vector<char> path;
            while (node != start) {
                node = parent[node];
                path.push_back(node);
            }
            std::reverse(path.begin(), path.end());
            cout << "Path : {";
            for (auto n: path) {
                cout << n << ", ";
            }
            cout << goal << "}" << endl;
            return;
        } else {
            cout << "Neighbours: {";
            for (auto neighbour: get_neighbours(node)) {
                cout << "(" << neighbour << ", " << heuristic(neighbour) << ", ";
                auto exp_it = explored.find(neighbour);
                auto fro_it = find(frontier.begin(), frontier.end(), neighbour);
                if (exp_it == explored.end() && fro_it == frontier.end()) {
                    cout << "not found), ";
                    frontier.push_back(neighbour);
                    parent[neighbour] = node;
                } else {
                    cout << "found), ";
                }
            }
            cout << "\b\b}" << endl;
        }
        cout << endl;
    }
}

void A_Star(char start) {
    list<char> frontier;
    set<char> explored;
    map<char, char> parent;
    map<char, int> f_value;
    map<char, int> cost;

    char goal = 'G';

    frontier.push_back(start);
    parent[start] = '-';
    f_value[start] = heuristic(start);

    int iteration = 0;

    while (!frontier.empty()) {
        iteration++;
        cout << "Iteration " << iteration << endl;

        cout << "Frontier: {";
        for (auto i: frontier) {
            cout << "(" << i << ", " << f_value[i] << "), ";
        }
        cout << "\b\b}" << endl;

        if (!explored.empty()) {
            cout << "Explored: {";
            for (auto i: explored) {
                cout << "(" << i << ", " << parent[i] << "), ";
            }
            cout << "\b\b}" << endl;
        } else { cout << "Explored: {}" << endl; }

        auto node_it = min_element(frontier.begin(), frontier.end(), [&f_value](char a, char b) -> bool {
            return (f_value[a] < f_value[b]);
        });
        auto node = *node_it;
        frontier.erase(node_it);

        cout << "Node removed: " << node << endl;
        explored.insert(node);

        if (node == goal) {
            cout << "\nGoal found!" << endl;
            vector<char> path;
            while (node != start) {
                node = parent[node];
                path.push_back(node);
            }
            std::reverse(path.begin(), path.end());
            cout << "Path : {";
            for (auto n: path) {
                cout << n << ", ";
            }
            cout << goal << "}" << endl;
            return;
        } else {
            cout << "Neighbours: {";
            for (auto neighbour: get_neighbours(node)) {
                cout << "(" << neighbour << ", " << heuristic(neighbour) << " + "
                     << edge_cost(neighbour, node) + cost[node] << ", ";
                auto exp_it = explored.find(neighbour);
                auto fro_it = find(frontier.begin(), frontier.end(), neighbour);
                if (exp_it == explored.end() && fro_it == frontier.end()) {
                    cout << "not found), ";
                    frontier.push_back(neighbour);
                    parent[neighbour] = node;
                    cost[neighbour] = edge_cost(neighbour, node) + cost[node];
                    f_value[neighbour] = heuristic(neighbour) + cost[neighbour];
                } else {
                    cout << "found, " << f_value[neighbour] << "), ";
                    int value = heuristic(neighbour) + edge_cost(neighbour, node) + cost[node];
                    if (value < f_value[neighbour]) {
                        parent[neighbour] = node;
                        cost[neighbour] = edge_cost(neighbour, node) + cost[node];
                        f_value[neighbour] = value;
                        if (exp_it != explored.end()) {
                            explored.erase(exp_it);
                            frontier.push_back(neighbour);
                        }
                    }
                }
            }
            cout << "\b\b}" << endl;
        }
        cout << endl;
    }
}

int main() {
    init_graph(graph);

    cout << "BFS :" << endl;
    BFS('S');
    cout << endl << "DFS :" << endl;
    DFS('S');
    cout << endl << "GBFS :" << endl;
    GBFS('S');
    cout << endl << "A* :" << endl;
    A_Star('S');
    return 0;
}
