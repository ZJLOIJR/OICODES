#include <cstdio>
#include <cstring>

const int N = 10007, M = 500007;
int n, m, u, v, w, tot = 0, s, head, tail;
int dis[N], vis[N], st[N], to[M], nx[M], len[M], que[N * 50];

void init()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; i++)
        dis[i] = 2147483647;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        to[++tot] = v;
        nx[tot] = st[u];
        len[tot] = w;
        st[u] = tot;
    }
}

void spfa()
{
    head = 1, tail = 0;
    dis[s] = 0, vis[s] = 1, que[++tail] = s;
    while (head <= tail)
    {
        int u = que[head++];
        vis[u] = 0;
        for (int i = st[u]; i; i = nx[i])
        {
            int v = to[i];
            if (dis[u] + len[i] < dis[v])
            {
                dis[v] = dis[u] + len[i];
                if (!vis[v])
                {
                    vis[v] = 1;
                    que[++tail] = v;
                }
            }
        }
    }	
}

int main()
{
    init();
    spfa();
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}
