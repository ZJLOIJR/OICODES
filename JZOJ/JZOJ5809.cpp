#include <cmath>
#include <cstdio>

typedef long long ll;
const ll P = 9901;

ll a, b, ans = 1LL, num[107], cnt[107];
int rt, tot = 0;

ll pow(ll a, ll b, ll mo)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mo;
		a = a * a % mo, b >>= 1;
	}
	return ret;
}

int main()
{
	freopen("sheep.in", "r", stdin);
	freopen("sheep.out", "w", stdout);
	
	scanf("%lld%lld", &a, &b);
	rt = sqrt(a);
	for (ll i = 2; i <= rt; i++)
		if (a % i == 0)
		{
			num[++tot] = i % P;
			while (a % i == 0) a /= i, cnt[tot]++;
		}
	if (a > 1) num[++tot] = a % P, cnt[tot] = 1;
	for (int i = 1; i <= tot; i++)
	{
		cnt[i] *= b;
		ans = ans * ((pow(num[i], cnt[i] + 1, P) - 1 + P) % P * pow(num[i] - 1, P - 2, P) % P) % P;
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
