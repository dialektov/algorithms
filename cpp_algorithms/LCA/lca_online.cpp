#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 20;
int par[LOG][MAXN], depth[MAXN], a[2 * MAXN];
vector<int> g[MAXN];

void dfs(int v, int p = 0)
{
    par[0][v] = p;
    depth[v] = depth[p] + 1;
    for (int i = 1; i < LOG; i++)
        par[i][v] = par[i - 1][par[i - 1][v]];
    for (int to : g[v])
        if (to != p)
            dfs(to, v);
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (depth[par[i][u]] >= depth[v])
            u = par[i][u];
    if (u == v)
        return u;
    for (int i = LOG - 1; i >= 0; i--)
        if (par[i][u] != par[i][v])
            u = par[i][u], v = par[i][v];
    return par[0][u];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; i++)
    {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    dfs(0);

    cin >> a[0] >> a[1];
    int x, y, z;
    cin >> x >> y >> z;
    for (int i = 2; i < 2 * m; i++)
        a[i] = (1LL * x * a[i - 2] + 1LL * y * a[i - 1] + z) % n;

    long long ans = 0;
    for (int i = 0; i < 2 * m; i += 2)
    {
        int v = lca(a[i], a[i + 1]);
        ans += v;
        a[i + 2] = (a[i + 2] + v) % n;
    }

    cout << ans << "\n";

    return 0;
}



