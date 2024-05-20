#include <bits/stdc++.h>
using namespace std;

#define debug(x) (cerr << #x << ": " << (x) << endl);

vector<int> compute_prefix_function(const string &str)
{
    int n = str.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && str[i] != str[j])
        {
            j = pi[j - 1];
        }
        if (str[i] == str[j])
        {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

int main()
{
    string s, t;
    cin >> s >> t;

    string combined = t + "#" + s;
    vector<int> pi = compute_prefix_function(combined);

    int overlap_length = pi.back();
    int min_letters_needed = s.size() + t.size() - overlap_length;

    cout << min_letters_needed << endl;

    return 0;
}