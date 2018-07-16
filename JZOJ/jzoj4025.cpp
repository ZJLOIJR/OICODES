#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int LEN = 2e5 + 7;

int n;
char str[LEN];
int son[LEN][52], fa[LEN], len[LEN];

inline int id(char c) { if (c >= 'A' && c <= 'Z') return c - 'A'; return c - 'a' + 26; }
inline char chr(int ord) { if (ord < 26) return ord + 'A'; return ord - 26 + 'a'; }

int root, tot, p, q, nq, np, last;
void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1;
	while (p && !son[p][id(ch)]) son[p][id(ch)] = np, p = fa[p];
	if (!p) fa[np] = root;
	else
	{
		q = son[p][id(ch)];
		if (len[p] + 1 == len[q]) fa[np] = q;
		else
		{
			nq = ++tot, len[nq] = len[p] + 1;
			memcpy(son[nq], son[q], sizeof(son[q]));
			fa[nq] = fa[q], fa[np] = fa[q] = nq;
			while (son[p][id(ch)] == q) son[p][id(ch)] = nq, p = fa[p];
		}
	}
}
int top, arr[LEN], sta[LEN], rd[LEN];
ll k, siz[LEN];
void topo()
{
	for (int x = 1; x <= tot; x++)
	{
		siz[x] = 1;
		for (int i = 0; i < 52; i++) if (son[x][i]) rd[son[x][i]]++;
	}
	for (int x = 1; x <= tot; x++) if (!rd[x]) sta[++top] = x;
	while (top)
	{
		int x = sta[top--];
		arr[++arr[0]] = x;
		for (int i = 0; i < 52; i++)
		{
			rd[son[x][i]]--;
			if (!rd[son[x][i]]) sta[++top] = son[x][i];
		}
	}
	for (int i = arr[0]; i; i--)
	{
		int x = arr[i];
		for (int j = 0; j < 52; j++) if (son[x][j]) siz[son[x][j]] += siz[x];
	}
}
void solve()
{
	if (k > siz[arr[arr[0]]]) k = siz[arr[arr[0]]];
	int x = root;
	while (k > 0)
	{
		int flag = 1;
		for (int i = 0; i < 52; i++)
			if (son[x][i])
			{
				flag = 0;
				if (k > siz[son[x][i]]) k -= siz[son[x][i]];
				else
				{
					putchar(chr(i)), x = son[x][i], k--;
					break;
				}
			}
		if (flag) --k;
	}
}
int main()
{
	root = last = ++tot;
	scanf("%s%lld", str + 1, &k);
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) extend(str[i]);
	topo();
	solve();
	putchar('\n');
	return 0;
}
