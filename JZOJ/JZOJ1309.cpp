#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 2e5 + 7;

int root, tot, p, q, np, nq, last, n;
int son[LEN << 1][26], fa[LEN << 1], len[LEN << 1], siz[LEN << 1];
char str[LEN];

inline int max(int a, int b) { return a > b ? a : b; }

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, siz[np]++;
	while (p && !son[p][ch - 'a']) son[p][ch - 'a'] = np, p = fa[p];
	if (!p) fa[np] = root;
	else
	{
		q = son[p][ch - 'a'];
		if (len[p] + 1 == len[q]) fa[np] = q;
		else
		{
			nq = ++tot, len[nq] = len[p] + 1;
			memcpy(son[nq], son[q], sizeof(son[q]));
			fa[nq] = fa[q];
			fa[np] = fa[q] = nq;
			while (son[p][ch - 'a'] == q) son[p][ch - 'a'] = nq, p = fa[p];
		}
	}
}
int buc[LEN << 1], arr[LEN << 1];
void topo()
{
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
	for (int i = tot; i; i--) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--) siz[fa[arr[i]]] += siz[arr[i]];
}
void solve()
{
	int ans = 0;
	for (int i = root + 1; i <= tot; i++) if (siz[i] >= 2) ans = max(ans, len[i]);
	printf("%d\n", ans);
}

int main()
{
	root = last = ++tot;
	scanf("%d%s", &n, str + 1);
	for (int i = 1; i <= n; i++) extend(str[i]);
	topo(), solve();
	return 0;
}
