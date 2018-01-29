#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 1000007, M = 2000007, P = 100003;

int n, m, u, v, w, tot = 0;
int to[M], nx[M], st[N];

inline int read()
{
    int x = 0, f = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
    return f ? -x : x;
}

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

queue<int> q;
int vis[N], dis[N], ans[N];
void spfa()
{
    memset(vis, 0, sizeof(vis)), memset(dis, 0x7f, sizeof(dis)), memset(ans, 0, sizeof(ans));
    ans[1] = 1, vis[1] = 1, dis[1] = 0, q.push(1);
    while (!q.empty())
    {
        int u = q.front();
        vis[u] = 0, q.pop();
        for (int i = st[u]; i; i = nx[i])
        {
            int v = to[i];
            if (dis[u] + 1 < dis[v])
            {
                dis[v] = dis[u] + 1;
                ans[v] = ans[u];
                if (!vis[v])
                    vis[v] = 1, q.push(v);
            }
            else if (dis[u] + 1 == dis[v])
                ans[v] = (ans[v] + ans[u]) % P;
        }
    }
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= m; i++)
        u = read(), v = read(), add(u, v), add(v, u);
    spfa();
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}
