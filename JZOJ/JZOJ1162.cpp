#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int min(int a, int b) { return a < b ? a : b; }

const int N = 3e2 + 7;

int n, m, k_;
int tot = 0, st[N], to[N << 1], nx[N << 1], len[N << 1];
int f[N][N][2], temp[N][2];

inline void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

void dfs(int u, int from)
{
	f[u][0][0] = f[u][1][1] = 0;
	for (int i = st[u]; i; i = nx[i])
		if (to[i] != from)
		{
			int v = to[i];
			dfs(v, u);
			memcpy(temp, f[u], sizeof(f[u]));
			memset(f[u], 0x3f, sizeof(f[u]));
			for (int j = 0; j <= k_; j++)
			{
				for (int k = 0; k < j; k++) f[u][j][1] = min(f[u][j][1], min(f[v][k][1] + temp[j - k][1] + len[i], f[v][k][0] + temp[j - k][1]));
				for (int k = 0; k <= j; k++) f[u][j][0] = min(f[u][j][0], min(f[v][k][1] + temp[j - k][0], f[v][k][0] + temp[j - k][0] + (m == 2) * len[i]));
			}
		}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k_);
	if (n - k_ < m - 1) { printf("-1\n"); return 0; }
	for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
	memset(f, 0x3f, sizeof(f));
	dfs(1, 0);
	printf("%d\n", f[1][k_][1]);
	return 0;
}
