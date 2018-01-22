#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 100007, M = 27;

int n, m, ans = 0, tmp, cnt, len;
char a[N], b[M], str[M];

int main()
{
	freopen("lcps.in", "r", stdin);
	freopen("lcps.out", "w", stdout);

	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	for (int i = 0; i <= (1 << m) - 1; i++)
	{
		tmp = 1, cnt = 1, len = 0;
		while (tmp <= i)
		{
			if (i & tmp) str[++len] = b[cnt];
			tmp <<= 1, cnt++;
		}
		if (len <= ans) continue;
		int j, k;
		for (j = 1; j <= (len >> 1); j++) if (str[j] != str[len - j + 1]) break;
		if (str[j] != str[len - j + 1]) continue;
		for (j = 1, k = 1; j <= n && k <= len; j++) if (a[j] == str[k]) k++;
		if (k > len) ans = len;
	}
	printf("%d\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}