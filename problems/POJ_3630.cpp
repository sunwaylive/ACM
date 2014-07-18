#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int CHAR_COUNT = 10;
const int ITEM_NUM = 10000;
const int EACH_ITEM_MAX_COUNT = 10;
const int MAX_NODE_NUM = ITEM_NUM * EACH_ITEM_MAX_COUNT + 1;

struct TrieNode{
    TrieNode* next[CHAR_COUNT];
    bool is_tail;
};

struct Trie{
    TrieNode *root;
    int size;

    TrieNode nodes[MAX_NODE_NUM];
};

Trie* createTrie()
{
    Trie *T = new Trie;
    T->root = &(T->nodes[0]);
    memset(T->nodes, 0, sizeof(T->nodes));
    T->size = 1;
    return T;
}

void freeTrie(Trie *tree)
{
    delete tree;
    tree = NULL;
}

void clearTrie(Trie *tree)
{
    memset(tree->nodes, 0, sizeof(tree->nodes));
    tree->size = 1;
}

bool trieInsert(Trie *tree, const char *word)
{
    TrieNode *p = tree->root;
    while(*word){
        int curWord = *word - '0';
        if(p->next[curWord] == NULL){
            p->next[curWord] = &(tree->nodes[tree->size]);
            ++tree->size;
        }

        p = p->next[curWord];
        if(p->is_tail) return false;
        ++word;
    }
    p->is_tail = true;
    //check
    for(int i = 0; i < CHAR_COUNT; ++i){
        if(p->next[i] != NULL)
            return false;
    }
    return true;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());

    char phone[20];
    Trie *tree = createTrie();
    bool isLegal = true;
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        while(n--){
            cin>>phone;
            if(isLegal) isLegal = trieInsert(tree, phone);
        }
        if(isLegal) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
        clearTrie(tree);
        isLegal = true;
    }
    freeTrie(tree);
    in.close();
    return 0;
}
