#include <cstdio>

const int N = 100007;
int a[N], f[N][32], lg[N];
int n, q, x, y;

inline int max(int a, int b) { return a > b ? a : b; }

void init()
{
    scanf("%d%d", &n, &q);
    lg[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        f[i][0] = a[i];
        if (i != 1)
            lg[i] = lg[i >> 1] + 1;
    }
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

inline int qry_max(int l, int r)
{
    int le = r - l + 1;
    return max(f[l][lg[le]], f[r - (1 << lg[le]) + 1][lg[le]]);
}

int main()
{
    init();
    while (q--)
    {
        scanf("%d%d", &x, &y);
        printf("%d\n", qry_max(x, y));
    }
    return 0;
}
