#include <bits/stdc++.h>
using namespace std;

#define debug(x) (cerr << #x << ": " << (x) << endl)

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    TrieNode *children[ALPHABET_SIZE];
    int count;

    TrieNode() : count(0)
    {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode *root, const string &key)
{
    TrieNode *curr = root;
    for (char c : key)
    {
        int index = c - 'a';
        if (!curr->children[index])
        {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
        curr->count++;
    }
}

int countPrefix(TrieNode *root, const string &prefix)
{
    TrieNode *curr = root;
    for (char c : prefix)
    {
        int index = c - 'a';
        if (!curr->children[index])
        {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

int main()
{
    int n;
    cin >> n;

    TrieNode *root = new TrieNode();

    vector<int> output;

    while (n--)
    {
        string operation, name;
        cin >> operation >> name;

        if (operation == "add")
        {
            insert(root, name);
        }
        else if (operation == "find")
        {
            output.push_back(countPrefix(root, name));
        }
    }

    for (int count : output)
    {
        cout << count << endl;
    }

    return 0;
}