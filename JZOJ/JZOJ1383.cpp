#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef long long ll;

int s, tot, sum, num[20], check[20][150][20];
ll a, b, f[20][150];

ll dfs(int len, int sum, int flag)
{
	if (sum > s || sum + len * 9 < s) return 0;
	if (!len) return sum == s;
	if (!flag && ~f[len][sum]) return f[len][sum];
	int mx = flag ? num[len] : 9; ll ret = 0;
	for (int i = 0; i <= mx; i++) ret += dfs(len - 1, sum + i, (flag && i == mx));
	if (!flag) f[len][sum] = ret;
	return ret;
}

ll solve(ll x)
{
	tot = 0; memset(num, 0, sizeof(num));
	while (x) { num[++tot] = x % 10, x /= 10; }
	return dfs(tot, 0, 1);
}

void makenum(int po, int now)
{
	if (!po) return;
	for (int i = 0; i < 10; i++)
		if (check[po][now][i]) { num[po] = i, makenum(po - 1, now - i); return; }
}

int main()
{
	memset(f, 0xff, sizeof(f));
	scanf("%lld%lld%d", &a, &b, &s);
	printf("%lld\n", solve(b) - solve(a - 1));
	for (int i = 0; i < 10; i++) check[1][i][i] = 1;
	for (int i = 2; i <= 15; i++)
		for (int j = 0; j <= i * 9; j++)
			for (int k = 0; k < 10; k++)
				if (j - k >= 0)
					for (int l = 0; l < 10; l++)
						check[i][j][k] |= check[i - 1][j - k][l];
	ll tmp = a;
	tot = 0; memset(num, 0, sizeof(num));
	while (tmp) num[++tot] = tmp % 10, sum += tmp % 10, tmp /= 10;
	if (sum == s) { printf("%lld\n", a); return 0; }
	for (int i = 1; i <= 15; i++)
	{
		sum -= num[i];
		for (int j = num[i] + 1; j < 10; j++)
			if (check[i][s - sum][j])
			{
				num[i] = j, makenum(i - 1, s - sum - j);
				for (int k = max(tot, i); k >= 1; k--) printf("%d", num[k]);
				putchar('\n'); return 0;
			}
	}
	return 0;
}
