#include <iostream>
#include <string>
#include <vector>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include "suffix_tree.h"

#define DEFAULT_LIMIT 500

using namespace std;

int main(int argc, char *argv[]) {
    int arg;
    int cfnd = 0;
    int ffnd = 0;
    int vfnd = 0;
    int nfnd = 0;
    string filename;
    int llimit = 0;
    int climit = DEFAULT_LIMIT;

    if(argc == 1) {
        cerr << argv[0] << " [-c count] [-f filename] [-l level limit] [-v] [-n]" << endl;
        cerr << " -v reverse" << endl;
        cerr << " -n show count" << endl;
        exit(0);
    }

    while((arg = getopt(argc, argv, "hnvc:f:l:")) != -1) {
        switch(arg) {
        case 'c':
            cfnd = 1;
            climit = atoi(optarg);
            break;
        case 'f':
            ffnd = 1;
            filename = optarg;
            break;
        case 'l':
            llimit = atoi(optarg);
            break;
        case 'v':
            vfnd = 1;
            break;
        case 'n':
            nfnd = 1;
            break;
        case 'h':
            cerr << argv[0] << "[-c count] [-f filename] [-l level limit] [-v]" << endl;
            exit(0);
        }
    }

    Node *root = new Node("");
    istream *sin = &cin;
    ifstream fin;
    if(ffnd) {
        fin.open(filename.c_str(), ios_base::in);
        if(fin)
            sin = &fin;
    }
    string line;
    while(getline(*sin, line)) {
        vector<string> vec;
        string buf;
        stringstream ss;
        ss << line;
        while(ss >> buf) {
            if(buf.length() == 0 || buf == " " || buf == "\n") continue;
            vec.push_back(buf);
        }
        if(!vfnd)
            reverse(vec.begin(), vec.end());
        parse_vec(root, vec, vfnd);
    }

    top_nodes(root, climit, vfnd, nfnd, 1, llimit);
    if(fin)
        fin.close();
    return 0;
}
