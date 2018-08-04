#include <cstdio>
#include <cstring>
#include <cstdlib>

const int P = 100000000;

int n, m, full, map[13][13];
int ans, f[13][1 << 12];

int check(int S, int line)
{
	if (S & (S << 1)) return 0;
	for (int i = 1; i <= m; i++) if (!map[line][i] && (S & (1 << (i - 1)))) return 0;
	return 1;
}

int main()
{
	freopen("cowfood.in", "r", stdin);
	freopen("cowfood.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);
	full = (1 << m) - 1;
	memset(f, 0, sizeof(f));
	for (int s = 0; s <= full; s++)
	{
		if (!check(s, 1)) continue;
		f[1][s] = 1;
	}
	for (int i = 2; i <= n; i++)
		for (int s = 0; s <= full; s++)
		{
			if (!check(s, i)) continue;
			for (int s_ = 0; s_ <= full; s_++)
			{
				if (s & (s_)) continue;
				if (!check(s_, i - 1)) continue;
				f[i][s] = (f[i][s] + f[i - 1][s_]) % P;
			}
		}
	for (int s = 0; s <= full; s++) ans = (ans + f[n][s]) % P;
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
