#include <bits/stdc++.h>
using namespace std;

vector<int> use(10);

struct node
{
    char c;
    int v;
};

int check(node* nodeArr, const int count, vector<string> strings)
{
    int m = 1, j, i;
    vector<int> vals(strings.size(), 0);

    for (int k = 0; k < strings.size(); k++)
    {
        string s = strings[k];
        for (i = s.length() - 1; i >= 0; i--)
        {
            char ch = s[i];
            for (j = 0; j < count; j++)
                if (nodeArr[j].c == ch)
                    break;

            vals[k] += m * nodeArr[j].v;
            m *= 10;
        }
        m = 1;
    }

    int sum = vals[0];
    for (int k = 1; k < strings.size() - 1; k++)
    {
        sum += vals[k];
    }

    return (sum == vals.back());
}

bool permutation(const int count, node* nodeArr, int n, vector<string> strings)
{
    if (n == count - 1)
    {
        for (int i = 0; i < 10; i++)
        {
            if (use[i] == 0)
            {
                nodeArr[n].v = i;
                if (check(nodeArr, count, strings))
                {
                    cout << "Solution found:";
                    for (int j = 0; j < count; j++)
                        cout << " " << nodeArr[j].c << " = " << nodeArr[j].v;
                    cout << endl;
                }
            }
        }
        return false;
    }

    bool found = false;
    for (int i = 0; i < 10; i++)
    {
        if (use[i] == 0)
        {
            nodeArr[n].v = i;
            use[i] = 1;
            found |= permutation(count, nodeArr, n + 1, strings);
            use[i] = 0;
        }
    }
    return found;
}

bool solveCryptographic(vector<string> strings)
{
    int count = 0;
    vector<int> freq(26);

    for (string s : strings)
    {
        for (int i = 0; i < s.length(); i++)
            ++freq[s[i] - 'A'];
    }

    for (int i = 0; i < 26; i++)
        if (freq[i] > 0)
            count++;

    if (count > 10)
    {
        cout << "Invalid strings";
        return false;
    }

    node nodeArr[count];

    for (int i = 0, j = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            nodeArr[j].c = char(i + 'A');
            j++;
        }
    }

    return permutation(count, nodeArr, 0, strings);
}

int main()
{
    int numStrings;
    cout << "Enter the number of strings: ";
    cin >> numStrings;
    vector<string> strings(numStrings);

    for (int i = 0; i < numStrings; i++)
    {
        cout << "Enter string " << i + 1 << ": ";
        cin >> strings[i];
    }

    if (!solveCryptographic(strings))
        cout << "No solution";
    return 0;
}
