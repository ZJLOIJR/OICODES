#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

int T, n, a, b, ans;
int t[20], f[25][25][25][25];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline int min(int a, int b) { return a < b ? a : b; }
inline void update(int &a, int b) { a = min(a, b); }

void dfs(int tot)
{
	int a, b, c, d; a = b = c = d = 0;
	for (int i = 3; i <= 16; i++)
		if (t[i] == 1) a++;
		else if (t[i] == 2) b++;
		else if (t[i] == 3) c++;
		else if (t[i] == 4) d++;
	ans = min(ans, f[a][b][c][d] + tot);
	for (int i = 1; i <= 3; i++)
	{
		int p = 5;
		if (i == 2) p = 3;
		if (i == 3) p = 2;
		for (int j = 3; j <= 14; j++)
		{
			if (t[j] < i) continue;
			for (int k = j + 1; k <= 14; k++)
			{
				if (t[k] < i) break;
				if (k - j + 1 >= p)
				{
					for (int l = j; l <= k; l++) t[l] -= i;
					dfs(tot + 1);
					for (int l = j; l <= k; l++) t[l] += i;
				}
			}
		}
	}
}

int main()
{
	freopen("landlords.in", "r", stdin);
	freopen("landlords.out", "w", stdout);
	
	memset(f, 0x3f, sizeof(f));
	f[0][0][0][0] = 0;
	for (int i = 0; i <= 23; i++)
		for (int j = 0; j <= 23; j++)
			for (int k = 0; k <= 23; k++)
				for (int l = 0; l <= 23; l++)
				{
					if (i >= 1) update(f[i][j][k][l], f[i - 1][j][k][l] + 1);
					if (i >= 1 && k >= 1) update(f[i][j][k][l], f[i - 1][j][k - 1][l] + 1);
					if (i >= 2 && l >= 1) update(f[i][j][k][l], f[i - 2][j][k][l - 1] + 1);
					if (l >= 1) update(f[i][j][k][l], f[i][j][k][l - 1] + 1);
					if (j >= 2 && l >= 1) update(f[i][j][k][l], f[i][j - 2][k][l - 1] + 1);
					if (j >= 1 && k >= 1) update(f[i][j][k][l], f[i][j - 1][k - 1][l] + 1);
					if (k >= 1) update(f[i][j][k][l], f[i][j][k - 1][l] + 1);
					if (j >= 1) update(f[i][j][k][l], f[i][j - 1][k][l] + 1);
				}
	T = read(), n = read();
	while (T--)
	{
		memset(t, 0, sizeof(t));
		for (int i = 1; i <= n; i++)
		{
			a = read(), b = read();
			if (a == 0) t[16]++;
			else if (a == 1) t[14]++;
			else if (a == 2) t[15]++;
			else t[a]++;
		}
		ans = 2333333;
		dfs(0);
		printf("%d\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}