#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 1e5 + 7;

int root, tot, p, q, np, nq, last, n;
int son[LEN << 1][55], fa[LEN << 1], len[LEN << 1], siz[LEN << 1];
char str[LEN];

inline int ord(char ch)
{
	if (ch >= 'a' && ch <= 'z') return ch - 'a';
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
	if (ch == ',') return 52;
	if (ch == '.') return 53;
	if (ch == '!') return 54;
}

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, siz[np]++;
	while (p && !son[p][ord(ch)]) son[p][ord(ch)] = np, p = fa[p];
	if (!p) fa[np] = root;
	else
	{
		q = son[p][ord(ch)];
		if (len[p] + 1 == len[q]) fa[np] = q;
		else
		{
			nq = ++tot, len[nq] = len[p] + 1;
			memcpy(son[nq], son[q], sizeof(son[q]));
			fa[nq] = fa[q], siz[nq] = siz[q];
			fa[np] = fa[q] = nq;
			while (son[p][ord(ch)] == q) son[p][ord(ch)] = nq, p = fa[p];
		}
	}
}
int top, sta[LEN << 1], arr[LEN << 1], rd[LEN << 1];
void topo()
{
	for (int i = 1; i <= tot; i++) for (int j = 0; j < 55; j++) if (son[i][j]) rd[son[i][j]]++;
	for (int i = 1; i <= tot; i++) if (!rd[i]) sta[++top] = i;
	while (top)
	{
		int x = sta[top--];
		arr[++arr[0]] = x;
		for (int i = 0; i < 55; i++)
			if (son[x][i])
			{
				rd[son[x][i]]--;
				if (!rd[son[x][i]]) sta[++top] = son[x][i];
			}
	}
	for (int i = arr[0]; i; i--) siz[fa[arr[i]]] += siz[arr[i]];
}
void solve()
{
	long long ans = 0;
	for (int i = root + 1; i <= tot; i++) if (siz[i] >= 2) ans += len[i] - len[fa[i]];
	printf("%lld\n", ans);
}

int main()
{
	root = last = ++tot;
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) extend(str[i]);
	topo(), solve();
	return 0;
}
