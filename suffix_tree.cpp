#include "suffix_tree.h"
#include <iostream>

using namespace std;
typedef map<string, Node*>::iterator DictIter;

Node::Node(string str)
:count(1),name(str) {
}

struct sort_pred {
    bool operator()(const std::pair<Node*,int> &left, const std::pair<Node*,int> &right) {
        return left.second > right.second;
    }
};

void parse_vec(Node *node, std::vector<std::string>& vec, int rev) {
    for(size_t i = 0; i < vec.size(); ++i) {
        string item = vec[i];
        if(node->dict.find(item) == node->dict.end()) {
            if(rev)
                node->dict[item] = new Node(node->name+item);
            else
                node->dict[item] = new Node(item+node->name);
        }
        else
            node->dict[item]->count += 1;
        node = node->dict[item];
    }
}

void top_nodes(Node *node, int limit, int rev, int nfnd, int level, int lvlimit) {
    vector< pair<Node*,int> > vec;
    for(DictIter it = node->dict.begin(); it != node->dict.end(); ++it) {
        Node *i = it->second;
        if(i->count >= limit)
            vec.push_back(pair<Node*,int>(i, i->count));
    }
    sort(vec.begin(), vec.end(), sort_pred());
    for(size_t i = 0;i < vec.size(); ++i) {
        Node* cur = vec[i].first;
        if(level != 1)
            cout << " ";
        cout << cur->name;
        if(nfnd)
            cout << " : " << cur->count;
        cout << endl;
        if(lvlimit > level)
            top_nodes(cur, limit, rev, nfnd, level+1, lvlimit);
    }
}
