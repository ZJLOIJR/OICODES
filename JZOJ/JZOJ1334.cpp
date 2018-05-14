#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3;

int n, a, rt, tot, ans;
int num[27], f[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		rt = sqrt(a), tot = 0;
		for (int j = 2; j <= rt; j++)
			if (a % j == 0)
			{
				num[++tot] = j;
				while (a % j == 0) a /= j;
			}
		if (a > 1) num[++tot] = a;
		int mx = 0;
		for (int j = 1; j <= tot; j++) if (f[num[j]] > mx) mx = f[num[j]];
		for (int j = 1; j <= tot; j++) f[num[j]] = mx + 1;
	}
	ans = 0;
	for (int i = 1; i <= N - 3; i++) if (f[i] > ans) ans = f[i];
	printf("%d\n", ans);
	return 0;
}
