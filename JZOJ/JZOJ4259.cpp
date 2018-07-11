#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int LEN = 4e3 + 7;

int len;
char str[LEN];
int sum[LEN];
ll a, rt, ans = 0, buc[LEN * 10];

int main()
{
	scanf("%lld%s", &a, str + 1);
	len = strlen(str + 1);
	for (int i = 1; i <= len; i++) sum[i] = sum[i - 1] + str[i] - '0';
	for (int i = 1; i <= len; i++)
		for (int j = 1; j <= i; j++)
			buc[sum[i] - sum[j - 1]]++;
	if (a == 0) ans += buc[0] * (1LL * len * (len + 1) - buc[0]);
	else
	{
		rt = sqrt(a);
		for (ll i = 1; i <= rt; i++)
			if (a % i == 0)
			{
				if (i < 36000 && a / i < 36000)
				{
					ans += buc[i] * buc[a / i];
					if (a / i != i) ans += buc[i] * buc[a / i];
				}
			}
	}
	printf("%lld\n", ans);
	return 0;
}
