#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef long long ll;
const int N = 1e2 + 3, P = 1e5;

int n, m;
ll hp[N], mp[N], typ[N], dam[N], f_all[P + 3], f_single[P + 3], ans = 666666666666LL;
char str[10];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", hp + i);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%*s%lld%s%lld", mp + i, str, dam + i);
		if (!mp[i]) { printf("0\n"); return 0; }
		if (dam[i] > P) dam[i] = P;
		typ[i] = (str[0] == 'S');
	}
	memset(f_all, 0x3f, sizeof(f_all));
	memset(f_single, 0x3f, sizeof(f_single));
	f_all[0] = f_single[0] = 0;
	for (int i = 1; i <= m; i++)
		if (dam[i] && typ[i])
			for (int j = dam[i]; j <= P; j++)
				f_single[j] = min(f_single[j], f_single[j - dam[i]] + mp[i]);
	for (int i = P - 1; i >= 0; i--) f_single[i] = min(f_single[i], f_single[i + 1]);
	for (int i = 1; i <= m; i++)
		if (dam[i] && !typ[i])
			for (int j = dam[i]; j <= P; j++)
				f_all[j] = min(f_all[j], f_all[j - dam[i]] + mp[i]);
	for (int i = 0; i <= P; i++)
	{
		ll sum = f_all[i];
		for (int j = 1; j <= m; j++)
			if (hp[j] - i > 0)
				sum += f_single[hp[j] - i];
		ans = min(ans, sum);
	}
	printf("%lld\n", ans);
	return 0;
}
