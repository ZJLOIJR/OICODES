#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 7, S = 5e3 + 7;

int s, tot = 0, cnt = 0, f[N][S], num[N];

int main()
{
	for (char ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) num[++cnt] = ch - '0';
	for (int i = 1; i <= cnt;)
	{
		if (num[i] == 0)
		{
			int c = 0;
			while (num[i] == 0 && i <= cnt)
			{ if (c < 3) num[++tot] = 0, c++; i++; }
		}
		else num[++tot] = num[i], i++;
	}
	scanf("%d", &s);
	memset(f, 0x3f, sizeof(f));
	for (int i = 0, sum = 0; i <= tot; i++)
	{
		sum = sum * 10 + num[i]; if (sum > s) break;
		if (sum <= s) f[i][sum] = 0;
	}
	for (int i = 1; i <= tot; i++)
		for (int j = 0; j <= s; j++)
		{
			int sum = 0, mi = 1;
			for (int k = i; k >= 1; k--, mi *= 10)
			{
				sum = sum + num[k] * mi; if (sum > j) break;
				if (f[k - 1][j - sum] + 1 < f[i][j]) f[i][j] = f[k - 1][j - sum] + 1;
			}
		}
	printf("%d\n", f[tot][s]);
	return 0;
}
