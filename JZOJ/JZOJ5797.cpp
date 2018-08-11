#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

int lenh, arrh[23], leng;
ll ans, k, g[43], gsum[(1 << 19) + 3];

int n, mid, h[43];
int buc[23][(1 << 19) + 3];

void dfs1(int now, ll sum, int las)
{
	if (now > mid) { gsum[++leng] = sum; return; }
	if (h[now] >= h[las]) dfs1(now + 1, sum + g[now], now);
	dfs1(now + 1, sum, las);
}

void dfs2(int now, ll sum, int las)
{
	if (now > mid)
	{
		buc[h[las]][lower_bound(gsum + 1, gsum + leng + 1, sum) - gsum]++;
		return;
	}
	if (h[now] >= h[las]) dfs2(now + 1, sum + g[now], now);
	dfs2(now + 1, sum, las);
}

void dfs3(int now, ll sum, int las, int fir)
{
	if (now > n)
	{
		if (fir) ans += buc[upper_bound(arrh + 1, arrh + lenh + 1, h[fir]) - arrh - 1][lower_bound(gsum + 1, gsum + leng + 1, k - sum) - gsum];
		else ans += buc[lenh][lower_bound(gsum + 1, gsum + leng + 1, k - sum) - gsum];
		return;
	}
	if (h[now] >= h[las])
	{
		if (!fir) dfs3(now + 1, sum + g[now], now, now);
		else dfs3(now + 1, sum + g[now], now, fir);
	}
	dfs3(now + 1, sum, las, fir);
}

int main()
{
	freopen("san.in", "r", stdin);
	freopen("san.out", "w", stdout);
	
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%lld", h + i, g + i);
	mid = n / 2 - 1;
	if (mid < 1) mid = 1;
	for (int i = 1; i <= mid; i++) arrh[++lenh] = h[i];
	sort(arrh + 1, arrh + lenh + 1);
	lenh = unique(arrh + 1, arrh + lenh + 1) - arrh - 1;
	for (int i = 1; i <= mid; i++) h[i] = lower_bound(arrh + 1, arrh + lenh + 1, h[i]) - arrh;
	dfs1(1, 0, 0);
	sort(gsum + 1, gsum + leng + 1);
	leng = unique(gsum + 1, gsum + leng + 1) - gsum - 1;
	dfs2(1, 0, 0);
	for (int i = 1; i <= lenh; i++)
		for (int j = leng; j >= 1; j--)
			buc[i][j] += buc[i - 1][j] + buc[i][j + 1] - buc[i - 1][j + 1];
	dfs3(mid + 1, 0, 0, 0);
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
