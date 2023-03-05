#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int next[26];
    int id;
    char val;
    int endmark;
    Vertex(){id = val = endmark = 0; memset(next, 0, sizeof next);}
};

struct Trie {
    vector<Vertex> trie;
    Trie(){trie.push_back(Vertex());}
    void insert(const string &s) {
        int root = 0;
        for (auto it : s) {
            int c = it - 'a';
            if (!trie[root].next[c]) {
                Vertex new_node;
                new_node.id = trie.size();
                new_node.val = it;
                trie[root].next[c] = new_node.id;
                trie.push_back(new_node);
            }
            root = trie[root].next[c];
        }
        trie[root].endmark++;
    }
    bool search(const string &s) {
        int root = 0;
        for (auto it : s) {
            int c = it - 'a';
            if (!trie[root].next[c]) {
                return false;
            }
            root = trie[root].next[c];
        }
        return trie[root].endmark > 0;
    }
};

signed main()
{

}