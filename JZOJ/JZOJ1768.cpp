#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 100, M = 10;

int n, m, full, f[2][1 << M][1 << M], cnt[1 << M], ok[1 << M], h[N + 3];
char ch;

inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf(" %c", &ch);
			if (ch == 'H') h[i] += (1 << (j - 1));
		}
	full = (1 << m) - 1;
	for (int s = 0, tmp; s <= full; s++)
	{
		tmp = s; while (tmp) cnt[s] += (tmp & 1), tmp >>= 1;
		ok[s] = (s & (s << 1) || s & (s << 2));
	}
	for (int s1 = 0; s1 <= full; s1++)
		for (int s2 = 0; s2 <= full; s2++)
		{
			if (ok[s1] || ok[s2] || s1 & s2 || s1 & h[2] || s2 & h[1]) continue;
			f[1][s2][0] = cnt[s2], f[0][s1][s2] = cnt[s1] + cnt[s2];
		}
	for (int i = 2; i < n; i++)
		for (int s1 = 0; s1 <= full; s1++)
		{
			if (ok[s1] || s1 & h[i]) continue;
			for (int s2 = 0; s2 <= full; s2++)
			{
				if (ok[s2] || s2 & h[i - 1] || s1 & s2) continue;
				for (int s = 0; s <= full; s++)
				{
					if (ok[s] || s & (s1 | s2) || s & h[i + 1]) continue;
					f[(i + 1) & 1][s][s1] = max(f[(i + 1) & 1][s][s1], f[i & 1][s1][s2] + cnt[s]);
				}
			}
		}
	int ans = 0;
	for (int s1 = 0; s1 <= full; s1++)
		for (int s2 = 0; s2 <= full; s2++)
			ans = max(ans, f[n & 1][s1][s2]);
	printf("%d\n", ans);
	return 0;
}
