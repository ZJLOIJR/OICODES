#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
inline ll max(ll a, ll b) { return a > b ? a : b; }
const int N = 2e2 + 7;

int n, m;
ll ans = -(1LL << 62), sum[N][N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%lld", &sum[i][j]), sum[i][j] += sum[i][j - 1];
	for (int i = 1; i <= m; i++)
		for (int j = i; j <= m; j++)
		{
			ll s = 0, mx = -(1LL << 62);
			for (int k = 1; k <= n; k++)
			{
				s += sum[k][j] - sum[k][i - 1];
				mx = max(mx, s);
				if (s < 0) s = 0;
			}
			ans = max(ans, mx);
		}
	printf("%lld\n", ans);
	return 0;
}
