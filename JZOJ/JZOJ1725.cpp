#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 57;

int T;
int n, X1, Y1, X2, Y2, X[N], Y[N], R[N];

int tot = 0, st[N], to[N], nx[N], fa[N], dep[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", X + i);
		for (int i = 1; i <= n; i++) scanf("%d", Y + i);
		for (int i = 1; i <= n; i++) scanf("%d", R + i);
		for (int i = 1; i <= n; i++)
	}
	return 0;
}
