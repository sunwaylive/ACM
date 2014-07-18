#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

const int CHAR_COUNT = 256;
const int MAX_ITEM_COUNT = 100000;
const int EACH_ITEM_MAX = 10;
const int TOTAL_NODE_COUNT = MAX_ITEM_COUNT * EACH_ITEM_MAX + 1;

struct TrieNode{
    TrieNode* next[CHAR_COUNT];
    bool is_tail;
    int tail_num;
};

struct Trie{
    TrieNode *root;
    int size;
    TrieNode nodes[TOTAL_NODE_COUNT];
};

Trie* createTrie()
{
    Trie *T = new Trie;
    T->root = &(T->nodes[0]);
    memset(T->nodes, 0, sizeof(T->nodes));
    T->size = 1;
    return T;
}

void clearTrie(Trie *tree)
{
    memset(tree->nodes, 0, sizeof(tree->nodes));
    tree->size = 1;
}

void freeTrie(Trie *tree)
{
    delete tree;
    tree = NULL;
}

void trieInsert(Trie *tree, const char *word)
{
    TrieNode *p = tree->root;
    while(*word){
        int curWord = *word - '0';
        if(p->next[curWord] == NULL){
            p->next[curWord] = &(tree->nodes[tree->size]);
            ++(tree->size);
        }
        p->next[curWord]->tail_num++;
        p = p->next[curWord];
        ++word;
    }
    p->is_tail = true;
}

int trieSearch(Trie *tree, const char *word)
{
    TrieNode *p = tree->root;
    while(*word){
        int curWord = *word - '0';
        if(p->next[curWord] == NULL) return 0;
        else p = p->next[curWord];
        ++word;
    }
    return p->tail_num;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());

    Trie *tree = createTrie();
    int n, m;
    char word[EACH_ITEM_MAX];
    cin>>n;
    while(n--){
        cin>>word;
        trieInsert(tree, word);
    }

    cin>>m;
    while(m--){
        cin>>word;
        cout<<trieSearch(tree, word)<<endl;
    }

    freeTrie(tree);
    in.close();
    return 0;
}
