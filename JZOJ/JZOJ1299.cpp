#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 4e4 + 3;

int n, m, x;
int f[N], p[N], last[N];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("cleanup.in", "r", stdin);
	freopen("cleanup.out", "w", stdout);

	memset(last, 0xff, sizeof(last));
	scanf("%d%*d", &n);
	m = sqrt(n) + 1;
	for (int i = 1; i <= n; i++) f[i] = i;
	scanf("%d", &x);
	last[x] = 1, p[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		scanf("%d", &x);
		p[0] = i;
		for (int j = m; j >= 1; j--) if (last[x] < p[j]) p[j] = p[j - 1];
		for (int j = 1; j <= m; j++) if (p[j] >= 1) f[i] = min(f[i], f[p[j] - 1] + j * j);
		last[x] = i;
	}
	printf("%d\n", f[n]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
