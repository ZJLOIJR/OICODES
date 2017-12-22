Source Code
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 10007;
int p[N], prime[N], f[N];
int n, tot = 0, lim;

void solve(int x)
{
	int ans = 0;
	for (int i = 1; i <= tot; i++)
	{
		int sum = 0, j = i;
		while (1)
		{
			sum += prime[j++];
			if (sum == x)
				ans++;
			if (sum > x)
				break;
			if (j > tot)
				break;
		}
	}
	printf("%d\n", ans);
}

int main()
{
	memset(p, 0, sizeof(p));
	p[1] = 1, lim = sqrt(N);
	for (int i = 2; i <= N; i++)
		if (!p[i])
		{
			prime[++tot] = i;
			for (int j = 2; i * j <= N; j++)
				p[i * j] = 1;
		}
	scanf("%d", &n);
	while (n)
	{
		solve(n);
		scanf("%d", &n);
	}
	return 0;
}
