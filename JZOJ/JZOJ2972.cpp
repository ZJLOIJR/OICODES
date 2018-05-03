#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e4 + 3;

int n, m, ans, tot;
int fa[N], leaf[N], sons[N];

int main()
{
	sons[tot = 1] = 0;
	scanf("%d%d", &n, &m);
	int las = 1;
	while (tot < n)
	{
		if (sons[las] < m) fa[++tot] = las, sons[las]++, leaf[tot] = 1;
		else leaf[++las] = 0;
	}
	for (int i = 1; i <= n; i++) if (leaf[i]) ans++;
	printf("%d\n", ans);
	for (int i = 2; i <= n; i++) printf("%d ", fa[i]);
	return 0;
}
