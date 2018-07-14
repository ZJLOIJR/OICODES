#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 3e5 + 7, M = 5e3 + 7, L = 807;

int root, tot, fail[M * L], son[M * L][26];
short data[M * L], dep[M * L], mx[M * L];

int n, m, c[N];
char str[N], str1[M];

void insert(char *s)
{
	int now = root;
	while (*s != '\0')
	{
		if (!son[now][*s - 'a']) son[now][*s - 'a'] = ++tot;
		now = son[now][*s - 'a'], s++;
	}
	data[now]++;
}
queue<int> que;
void getfail()
{
	que.push(root);
	while (!que.empty())
	{
		int x = que.front(); que.pop();
		for (int i = 0; i < 26; i++)
			if (son[x][i])
			{
				dep[son[x][i]] = dep[x] + 1;
				if (x == root)
					fail[son[x][i]] = root, mx[son[x][i]] = data[son[x][i]] ? 1 : 0;
				else
				{
					int tmp = fail[x];
					while (tmp)
					{
						if (son[tmp][i]) { fail[son[x][i]] = son[tmp][i]; break; }
						tmp = fail[tmp];
					}
					if (!tmp) fail[son[x][i]] = root;
					if (data[son[x][i]]) mx[son[x][i]] = dep[son[x][i]];
					else mx[son[x][i]] = mx[fail[son[x][i]]];
				}
				que.push(son[x][i]);
			}
	}
}
void match()
{
	int now = 1;
	for (int i = 1; i <= n; i++)
	{
		while (!son[now][str[i] - 'a'] && now != root) now = fail[now];
		now = son[now][str[i] - 'a'];
		if (!now) now = root;
		c[i + 1]--, c[i - (mx[now]) + 1]++;
	}
}

int main()
{
	root = tot = 1;
	scanf("%d%s%d", &n, str + 1, &m);
	while (m--) scanf("%s", str1), insert(str1);
	getfail(), match();
	int ans = 0;
	for (int i = 1, sum = 0; i <= n; i++) { sum += c[i]; if (sum <= 0) ans++; }
	printf("%d\n", ans);
	return 0;
}
