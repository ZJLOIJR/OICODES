#include <cstdio>

const int N = 1e5 + 3;

int T, n, a[N], sum[N];

int main()
{
	scanf("%d", &T);
	for (int c = 1; c <= T; c++)
	{
		int ans = 0, mxl, mxr;
		scanf("%d", &n);
		sum[0] = 0;
		for (int i = 1; i <= n; i++) scanf("%d", a + i), sum[i] = sum[i - 1] + a[i];
		for (int i = 1, mi = 0, mival = -2147483647; i <= n; i++)
		{
			if (sum[i] - sum[mi] > ans)
				ans = sum[i] - sum[mi], mxl = mi + 1, mxr = i;
			if (sum[i] < mival) mival = sum[i], mi = i;
		}
		printf("Case %d:\n", c);
		for (int i = mxl; i <= mxr; i++) printf("%d ", a[i]);
		printf("\n\n");
	}
	return 0;
}
