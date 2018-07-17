#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int ord(char ch) { return ch >= '0' && ch <= '9' ? ch - '0' : ch - 'a' + 10; }
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 107, LEN = 107, MAX = 50007, INF = 0x3f3f3f3f;

int T, n, mi, id, cnt;
char str[N][LEN], len[N];
//神奇的分类讨论
int next[N][LEN][36];
int f[LEN][LEN], dp[LEN][LEN][LEN];
char tmp[LEN];

int check()
{
	for (int i = 1; i <= n; i++)
	{
		int flag = 1;
		if (i == id) continue;
		int now = 0;
		for (int j = 1; j <= cnt; j++)
		{
			if (next[i][now][ord(tmp[j])] == INF) { flag = 0; break; }
			now = next[i][now][ord(tmp[j])] + 1;
		}
		if (!flag) return 0;
	}
	return 1;
}

void solve1()
{
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= len[1]; i++)
		for (int j = 1; j <= len[2]; j++)
		{
			if (str[1][i] == str[2][j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
			f[i][j] = max(f[i][j], max(f[i - 1][j], f[i][j - 1]));
		}
	printf("%d\n", f[len[1]][len[2]]);
}
void solve2()
{
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= len[1]; i++)
		for (int j = 1; j <= len[2]; j++)
			for (int k = 1; k <= len[3]; k++)
			{
				if (str[1][i] == str[2][j] && str[2][j] == str[3][k]) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - 1] + 1);
				dp[i][j][k] = max(dp[i][j][k], max(dp[i - 1][j][k], max(dp[i][j - 1][k], dp[i][j][k - 1])));
			}
	printf("%d\n", dp[len[1]][len[2]][len[3]]);
}
void solve3()
{
	memset(next, 0x3f, sizeof(next));
	mi = LEN, id;
	for (int i = 1; i <= n; i++)
	{
		if (len[i] < mi) mi = len[i], id = i;
		for (int j = 1; j <= len[i]; j++) next[i][j][ord(str[i][j])] = j;
		for (int j = len[i] - 1; j >= 0; j--)
			for (int k = 0; k < 36; k++)
				next[i][j][k] = min(next[i][j][k], next[i][j + 1][k]);
	}
	int full = (1 << len[id]) - 1, ans = 0;
	for (int s = 0, temp, index; s <= full; s++)
	{
		cnt = 0, temp = s, index = 0;
		while (temp)
		{
			++index;
			if (temp & 1) tmp[++cnt] = str[id][index];
			temp >>= 1;
		}
		if (cnt <= ans) continue;
		if (check()) ans = max(ans, cnt);
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%s", str[i] + 1), len[i] = strlen(str[i] + 1);
		if (n == 2) solve1();
		else if (n == 3) solve2();
		else solve3();
	}
	return 0;
}
