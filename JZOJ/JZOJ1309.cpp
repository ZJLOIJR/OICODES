#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 2e5 + 7;

int n;
char str[LEN];

int root, tot, p, q, np, nq, last;
int son[LEN << 1][26], fa[LEN << 1], len[LEN << 1], sum[LEN << 1];

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, ++sum[np];
	while (p && !son[p][ch - 'a']) son[p][ch - 'a'] = np, p = fa[p];
	if (!p) fa[np] = root;
	else
	{
		q = son[p]
	}
}

int main()
{
	root = last = ++tot;
	scanf("%d%s", &n, str + 1);
	for (int i = 1; i <= n; i++) extend(str[i]);
	return 0;
}
