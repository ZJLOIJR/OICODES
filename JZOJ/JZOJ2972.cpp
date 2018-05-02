#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e4 + 3;

int n, m, tot = 0, ans = 0, x;
int fa[N], leaf[N];

int main()
{
	scanf("%d%d", &n, &m);
	while (tot < n)
	{
		fa[++tot] = x, leaf[x = tot] = 0;
		for (int i = 1; i <= m - 1 && tot < n; i++) leaf[++tot] = 1, fa[tot] = x;
	}
	for (int i = 1; i <= n; i++) if (leaf[i]) ans++;
	printf("%d\n", ans);
	for (int i = 2; i <= n; i++) printf("%d ", fa[i]);
	return 0;
}
