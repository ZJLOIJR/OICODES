#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
const int N = 1e6 + 7;

int n, rt, ans, cnt, size[N], buc[N], sum[N], vis[N], fa[N], arr[N];
int tot, st[N], to[N << 1], nx[N << 1];
int top, sta[N];

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

int main()
{
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	sta[++top] = 1;
	while (top > 0)
	{
		int u = sta[top--];
		vis[u] = 1, arr[++cnt] = u;
		for (int i = st[u]; i; i = nx[i])
			if (!vis[to[i]])
				fa[to[i]] = u, sta[++top] = to[i];
	}
	for (int i = 1; i <= n; i++) size[i] = 1;
	for (int i = cnt; i; i--) size[fa[arr[i]]] += size[arr[i]];
	for (int i = 1; i <= n; i++) buc[size[i]]++;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)
			sum[i] += buc[j];
	rt = sqrt(n);
	for (int i = 1; i <= rt; i++)
		if (n % i == 0)
		{
			if (sum[i] == n / i) ans++;
			if (n / i != i && sum[n / i] == i) ans++;
		}
	printf("%d\n", ans);
	return 0;
}
