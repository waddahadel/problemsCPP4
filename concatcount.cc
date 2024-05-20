#include <bits/stdc++.h>
using namespace std;

#define debug(x) (cerr << #x << ": " << (x) << endl);

struct Suffix
{
    int index;
    int rank[2];
};

bool cmp(Suffix a, Suffix b)
{
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1]) : (a.rank[0] < b.rank[0]);
}

vector<int> buildSuffixArray(string t)
{
    int n = t.length();
    vector<Suffix> suffixes(n);
    vector<int> index(n);

    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = t[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (t[i + 1] - 'a') : -1;
    }

    sort(suffixes.begin(), suffixes.end(), cmp);

    for (int k = 4; k < 2 * n; k <<= 1)
    {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        index[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++)
        {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            index[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[index[nextindex]].rank[0] : -1;
        }

        sort(suffixes.begin(), suffixes.end(), cmp);
    }

    vector<int> suffixArray(n);
    for (int i = 0; i < n; i++)
    {
        suffixArray[i] = suffixes[i].index;
    }
    return suffixArray;
}

vector<int> buildLCPArray(string t, vector<int> &suffixArray)
{
    int n = t.length();
    vector<int> lcp(n, 0);
    vector<int> invSuffixArray(n, 0);

    for (int i = 0; i < n; i++)
    {
        invSuffixArray[suffixArray[i]] = i;
    }

    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (invSuffixArray[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = suffixArray[invSuffixArray[i] + 1];
        while (i + k < n && j + k < n && t[i + k] == t[j + k])
        {
            k++;
        }
        lcp[invSuffixArray[i]] = k;
        if (k > 0)
            k--;
    }
    return lcp;
}

long long countOccurrences(string t, vector<int> &suffixArray, vector<int> &lcp, vector<string> &si)
{
    int n = t.length();
    int m = si.size();
    long long totalCount = 0;

    for (int i = 0; i < m; i++)
    {
        string s = si[i];
        int sLen = s.length();
        int low = 0, high = n - 1;
        int firstOccurrence = -1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int cmp = t.compare(suffixArray[mid], min(sLen, n - suffixArray[mid]), s);
            if (cmp == 0)
            {
                firstOccurrence = mid;
                high = mid - 1;
            }
            else if (cmp < 0)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        low = 0, high = n - 1;
        int lastOccurrence = -1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int cmp = t.compare(suffixArray[mid], min(sLen, n - suffixArray[mid]), s);
            if (cmp == 0)
            {
                lastOccurrence = mid;
                low = mid + 1;
            }
            else if (cmp < 0)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        if (firstOccurrence != -1 && lastOccurrence != -1)
        {
            long long occurrences = lastOccurrence - firstOccurrence + 1;
            totalCount += occurrences;
        }
    }
    return totalCount;
}

int main()
{
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> si(n);
    for (int i = 0; i < n; i++)
    {
        cin >> si[i];
    }

    vector<int> suffixArray = buildSuffixArray(t);
    vector<int> lcp = buildLCPArray(t, suffixArray);
    long long totalOccurrences = countOccurrences(t, suffixArray, lcp, si);

    cout << totalOccurrences << endl;

    return 0;
}