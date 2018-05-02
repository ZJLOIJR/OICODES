#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;

int T;
ll n, base, rt, ans, num[1000007], cnt[1000007];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld%lld", &n, &base);
		rt = sqrt(base), num[0] = 0;
		for (ll i = 2; i <= rt; i++)
			if (base % i == 0)
			{
				num[++num[0]] = i, cnt[num[0]] = 0;
				while (base % i == 0) base /= i, cnt[num[0]]++;
			}
		if (base > 1) num[++num[0]] = base, cnt[num[0]] = 1;
		ans = (1LL << 62);
		for (int i = 1; i <= num[0]; i++)
		{
			ll ret = 0, tmp = n;
			while (tmp) tmp /= num[i], ret += tmp;
			if (ret / cnt[i] < ans) ans = ret / cnt[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
