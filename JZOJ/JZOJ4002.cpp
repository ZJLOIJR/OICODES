#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 1e5 + 3, P = 1e7 + 7;

int n, len;
char str[LEN << 1];
int power[LEN << 1], sum1[LEN << 1], sum2[LEN << 1];

int quickpower(int a, int n)
{
	int ret = 1;
	while (n)
	{
		if (n & 1) ret = ret * a % P;
		a = a * a % P;
		n >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str + 1); len = strlen(str + 1);
		for (int i = len + 1; i <= len * 2; i++) str[i] = str[i - len];
		len *= 2;
		power[0] = 1, sum1[0] = 0, sum2[len + 1] = 0;
		for (int i = 1; i <= len; i++) power[i] = power[i - 1] * 27 % P;
		for (int i = 1; i <= len; i++) sum1[i] = (sum1[i - 1] * 27 % P + str[i] - 'a') % P;
		for (int i = len; i >= 1; i--) sum2[i] = (sum2[i + 1] * 27 % P + str[i] - 'a') % P;
		len /= 2;
		int flag = 1;
		for (int i = 1; i <= len; i++)
		{
			int hash1 = (sum1[i + len - 1] - sum1[i - 1] * power[len] % P + P) % P * quickpower(power[i - 1], P - 2) % P,
				hash2 = (sum2[i] - sum2[i + len] * power[len] % P + P) % P * quickpower(power[i + len - 1], P - 2) % P;
			printf("%d %d\n", hash1, hash2);
			if (hash1 == hash2) { flag = 0; break; }
		}
		if (flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
