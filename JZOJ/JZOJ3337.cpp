#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 5e4 + 7, P = 19260817;

int len1, len2, sum1[N], sum2[N], pow[N];
char str1[N], str2[N];

int hashval(int* arr, int l, int r)
{
	if (l > r) return 0;
	return (arr[r] - arr[l - 1] * 1LL * pow[r - l + 1] % P + P) % P;
}

int check(int m)
{
	for (int i = 1; i <= len2 - m + 1; i++)
	{
		int l = 1, r = m, mid, ans = 0;
		while (l <= r)
		{
			mid = l + r >> 1;
			if (sum1[mid] == hashval(sum2, i, i + mid - 1)) l = mid + 1, ans = mid;
			else r = mid - 1;
		}
		if (hashval(sum1, ans + 2, m) == hashval(sum2, i + ans + 1, i + m - 1)) return 1;
	}
	return 0;
}

int main()
{
	pow[0] = 1; for (int i = 1; i <= 50000; i++) pow[i] = pow[i - 1] * 233LL % P;
	scanf("%s%s", str1 + 1, str2 + 1);
	len1 = strlen(str1 + 1), len2 = strlen(str2 + 1);
	for (int i = 1; i <= len1; i++) sum1[i] = (sum1[i - 1] * 233LL % P + str1[i] - 'a') % P;
	for (int i = 1; i <= len2; i++) sum2[i] = (sum2[i - 1] * 233LL % P + str2[i] - 'a') % P;
	int l = 0, r = len1, mid, ans = -1;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
