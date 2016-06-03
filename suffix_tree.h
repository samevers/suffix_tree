#pragma once

#include <vector>
#include <string>
#include <map>

class Node {
public:
    int count;
    std::string name;
    std::map<std::string, Node*> dict;

    Node(std::string iname);
};

void parse_vec(Node *node, std::vector<std::string>& vec, int rev);

void top_nodes(Node *node, int limit, int rev, int nfnd, int level, int lvlimit);
