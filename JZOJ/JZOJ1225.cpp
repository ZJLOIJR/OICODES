#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 2e2 + 7;

int n, m, ans;
ll a[N][N], sum[N][N];

struct presum { ll val; int ind; } s[N];
int cmp(presum a, presum b) { return a.val == b.val ? a.ind < b.ind : a.val < b.val; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			sum[i][j] = sum[i][j - 1] + a[j][i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
		{
			ll S = 0;
			for (int k = 1; k <= m; k++) S += sum[k][i] - sum[k][j - 1], s[k] = (presum){S, k};
			s[m + 1] = (presum){0, 0};
			sort(s + 1, s + m + 2, cmp);
			int mxlen = 0;
			for (int k = 1, mi = m + 1; k <= m + 1; k++)
			{
				if (s[k].ind > mi) mxlen = max(mxlen, s[k].ind - mi);
				mi = min(mi, s[k].ind);
			}
			ans = max(ans, (i - j + 1) * mxlen);
		}
	printf("%d\n", ans);
	return 0;
}
