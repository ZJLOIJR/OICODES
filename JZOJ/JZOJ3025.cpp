#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int K = 52;

long long ans = 0;
int n, p, col, cost, now;
int las[K], sum[K], cnt[K];

int main()
{
	scanf("%d%*d%d", &n, &p);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &col, &cost);
		if (cost <= p) now = i;
		if (now >= las[col]) sum[col] = cnt[col];
		las[col] = i;
		ans += sum[col];
		cnt[col]++;
	}
	printf("%lld\n", ans);
	return 0;
}
