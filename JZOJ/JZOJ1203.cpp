#pragma GCC optimize(2)
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int pane[7][4] = {{0, 0, 0, 0}, {5, 3, 2, 4}, {1, 3, 6, 4}, {5, 6, 2, 1}, {5, 1, 2, 6}, {6, 3, 1, 4}, {2, 3, 5, 4}};

int n, tot, ans;
int col[100][100], tmpcol[100][100], cnt[10][100];
map<string, int> buc;
string str;

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

void dfs(int dep)
{
	if (dep > n)
	{
		int sum = 0;
		for (int i = 1; i <= 6; i++)
		{
			int mxcnt = 0;
			for (int j = 1; j <= n; j++) mxcnt = max(mxcnt, cnt[i][tmpcol[j][i]]);
			sum += n - mxcnt;
		}
		ans = min(ans, sum);
		return;
	}
	for (int i = 1; i <= 6; i++)
	{
		tmpcol[dep][1] = col[dep][i], tmpcol[dep][6] = col[dep][7 - i];
		cnt[1][col[dep][i]]++, cnt[6][col[dep][7 - i]]++;
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				tmpcol[dep][pane[1][k]] = col[dep][pane[i][(k + j) % 4]];
				cnt[pane[1][k]][col[dep][pane[i][(k + j) % 4]]]++;
			}
			dfs(dep + 1);
			for (int k = 0; k < 4; k++) cnt[pane[1][k]][col[dep][pane[i][(k + j) % 4]]]--;
		}
		cnt[1][col[dep][i]]--, cnt[6][col[dep][7 - i]]--;
	}
}

int main()
{
	while (1)
	{
		scanf("%d", &n);
		if (!n) break;
		buc.clear(), tot = 0, ans = 100000;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= 6; j++)
			{
				cin >> str;
				if (!buc[str]) buc[str] = ++tot;
				col[i][j] = buc[str];
			}
		memset(cnt, 0, sizeof(cnt));
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
