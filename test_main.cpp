#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005, SIGMA = 30;

int sigma;
int g[MAXN][SIGMA], ming[MAXN][SIGMA];
int col[MAXN], a[MAXN];

char term[MAXN];
bool diff[MAXN][MAXN], used[MAXN];

queue < pair<int, int> > qq;
vector<int> minterm, gr[MAXN][SIGMA];

void dfs(int v) {
    used[v] = 1;

    for (int i = 0; i < sigma; i++) {
        if (!used[g[v][i]]) {
            dfs(g[v][i]);
        }
    }
}

int main(int argc, char* argv[]) {
    //freopen ("input.txt", "r", stdin);
    //freopen ("output.txt", "w", stdout);
    freopen(argv[1], "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;
    sigma = s.size();
    
    int q, q0, t, v;
    cin >> q >> q0 >> t;
    q0--;

    for (int i = 0; i < t; i++) {
        cin >> v;
        term[v - 1] = 1;
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < sigma; j++) {
            cin >> g[i][j];
            g[i][j]--;
            gr[g[i][j]][j].push_back(i);
        }
    }
        
    dfs(q0);

    for (int i = 0; i < q; i++) {
        if (used[i]) {
            for (int j = i + 1; j < q; j++) {
                if ((used[j]) && (term[i] ^ term[j])) {
                    diff[i][j] = 1;
                    diff[j][i] = 1;
                    qq.push(make_pair(i, j));
                }
            }

        }
    }
    while (!qq.empty()) {
        int v = qq.front().first;
        int u = qq.front().second;
        qq.pop();
        
        for(int i = 0; i < sigma; i++) {
            for (int j = 0; j < gr[v][i].size(); j++) {
                int vv = gr[v][i][j];
                if (!used[vv]) {
                    continue;
                }
                for (int k = 0; k < gr[u][i].size(); k++) {
                    int uu = gr[u][i][k];
                    if ((used[uu]) && (!diff[vv][uu])) {
                        diff[vv][uu] = 1;
                        diff[uu][vv] = 1;
                        qq.push(make_pair(vv, uu));
                    }
                }
            }
        }
    }

    for (int i = 0; i < q; i++) {
        col[i] = -1;
    }
    int c = 0, c0;

    for (int i = 0; i < q; i++) {
        if ((col[i] == -1) && (used[i])) {
            col[i] = c;
            a[c] = i;
            if (term[i]) {
                minterm.push_back(c);
            }
            for (int j = 0; j < q; j++) {
                if ((used[j]) && (!diff[i][j])) {
                    col[j] = c;
                }
            }
            c++;
        }
        if (i == q0) {
            c0 = col[i];
        }
    }


    for (int i = 0; i < c; i++) {
        for (int j = 0; j < sigma; j++) {
            ming[i][j] = col[g[a[i]][j]];
        }
    }

    cout << c << '\n' << c0 + 1 << ' ' << minterm.size() << ' ';

    for (int i = 0; i < minterm.size(); i++)
        cout << minterm[i] + 1 << ' ';
    cout << '\n';
    for (int i = 0; i < c; i++) { 
        for (int j = 0; j < sigma; j++) {
            cout << ming[i][j] + 1 << ' ';
        }
        cout << '\n';
    }

}


/*
g++ -std=gnu++11  main.cpp
*/

/*

*/ 
