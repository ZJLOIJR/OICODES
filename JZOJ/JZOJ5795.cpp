#include <cstdio>
#include <cstring>
#include <cstdlib>

inline int max(int a, int b) { return a > b ? a : b; }
const int LEN = 5e6 + 7;

int n, m, len;
int root, tot, son[LEN][3], mx[LEN], ans[LEN];
char str[LEN];

void insert(int ind)
{
	int now = root;
	for (int i = 1; i <= len; i++)
	{
		if (!son[now][str[i] - 'a']) son[now][str[i] - 'a'] = ++tot;
		now = son[now][str[i] - 'a'];
		ans[now] = max(ans[now], ind - mx[now] - 1);
		mx[now] = max(mx[now], ind);
	}
}
int getans()
{
	int now = root;
	for (int i = 1; i <= len; i++)
	{
		if (!son[now][str[i] - 'a']) return n;
		now = son[now][str[i] - 'a'];
	}
	if (mx[now] == n) return ans[now];
	else return max(ans[now], n - mx[now]);
}

int main()
{
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);

	root = ++tot;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", str + 1), len = strlen(str + 1), insert(i);
	for (int i = 1; i <= m; i++) scanf("%s", str + 1), len = strlen(str + 1), printf("%d\n", getans());

	fclose(stdin);
	fclose(stdout);
	return 0;
}
