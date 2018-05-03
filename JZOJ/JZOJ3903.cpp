#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
using namespace std;

typedef long long ll;
const short pane[7][4] = {{0, 0, 0, 0}, {5, 3, 2, 4}, {1, 3, 6, 4}, {5, 6, 2, 1}, {5, 1, 2, 6}, {6, 3, 1, 4}, {2, 3, 5, 4}};
const int P = 233317;

int n, ans, tot, len;
short flag, col[5][7], tmpcol[5][7], cnt[7][25];
int buc[P];
ll sum;
char str[100];

void dfs(short dep)
{
	if (dep > n)
	{
		register short sum = 0;
		for (register short i = 1; i <= 6; ++i)
		{
			int mxcnt = 0;
			for (register short j = 1; j <= n; ++j) mxcnt = max(mxcnt, cnt[i][tmpcol[j][i]]);
			sum += n - mxcnt;
		}
		ans = min(ans, sum);
		if (ans == 0) flag = 1;
		return;
	}
	if (flag) return;
	for (register short i = 1; i <= 6; ++i)
	{
		tmpcol[dep][1] = col[dep][i], tmpcol[dep][6] = col[dep][7 - i], ++cnt[1][col[dep][i]], ++cnt[6][col[dep][7 - i]];
		for (register short j = 0; j < 4; ++j)
		{
			for (register short k = 0; k < 4; ++k)
				tmpcol[dep][pane[1][k]] = col[dep][pane[i][k + j >= 4 ? k + j - 4 : k + j]], ++cnt[pane[1][k]][col[dep][pane[i][k + j >= 4 ? k + j - 4 : k + j]]];
			dfs(dep + 1);
			for (register short k = 0; k < 4; ++k) --cnt[pane[1][k]][col[dep][pane[i][k + j >= 4 ? k + j - 4 : k + j]]];
		}
		--cnt[1][col[dep][i]], --cnt[6][col[dep][7 - i]];
	}
}

int main()
{
	while (1)
	{
		scanf("%d", &n);
		if (!n) break;
		memset(buc, 0, sizeof(buc));
		tot = 0, ans = 100000, flag = 0;
		for (register short i = 1; i <= n; ++i)
			for (register short j = 1; j <= 6; ++j)
			{
				scanf("%s", str);
				len = strlen(str), sum = 0;
				for (int i = 0; i < len; i++) sum = (sum * 256 % P + str[i]) % P;
				if (!buc[sum]) buc[sum] = ++tot;
				col[i][j] = buc[sum];
			}
		memset(cnt, 0, sizeof(cnt));
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
