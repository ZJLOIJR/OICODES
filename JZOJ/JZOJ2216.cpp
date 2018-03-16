#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 207;

int n, m, u, v, w, q;
int t[N];
int f[N][N], dis[N][N];

inline int read()
{
    int x = 0, f = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
    return f ? -x : x;
}

inline int min(int a, int b) { return a < b ? a : b; }

void init()
{
    memset(f, 0x3f, sizeof(f));
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        *(t + i) = read();
    for (int i = 1; i <= m; i++)
    {
        u = read(), v = read(), w = read();
        u++, v++;
        f[u][v] = f[v][u] = w;
    }
}

void solve()
{
    int las = 0;
    q = read();
    while (q--)
    {
        u = read(), v = read(), w = read();
        u++, v++;
        while (t[las] <= w)
        {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    f[i][j] = min(f[i][j], f[i][las] + f[las][j]);
            las++;
        }
        if (f[u][v] == 0x3f3f3f3f || t[u] > w || t[v] > w)
            printf("-1\n");
        else
            printf("%d\n", f[u][v]);
    }
}

int main()
{
    init();
    solve();
    return 0;
}
