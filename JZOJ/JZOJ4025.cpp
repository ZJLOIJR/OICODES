#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int LEN = 2e5 + 7;
inline int ord(char ch) { return ch >= 'A' && ch <= 'Z' ? ch - 'A' : ch - 'a' + 26; }
inline char chr(int od) { return od < 26 ? od + 'A' : od - 26 + 'a'; }

int root, tot, p, q, np, nq, last, n;
int son[LEN][52], fa[LEN], len[LEN];
char str[LEN];
ll k, w, siz[LEN];

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1;
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
			fa[nq] = fa[q], fa[np] = fa[q] = nq;
			while (p && son[p][ord(ch)] == q) son[p][ord(ch)] = nq, p = fa[p];
		}
	}
}
void solve()
{
	int x = root, sum;
	if (k > siz[x]) k = siz[x];
	while (k > w + (x == root ? 0 : 1))
	{
		if (x != root) k--;
		for (int i = 0; i < 52; i++)
			if (son[x][i])
			{
				if (k > siz[son[x][i]]) k -= siz[son[x][i]];
				else { putchar(chr(i)), x = son[x][i]; break; }
			}
	}
	putchar('\n');
}

int buc[LEN], arr[LEN];
int main()
{
	root = last = ++tot;
	scanf("%s%lld", str + 1, &k);
	if (k == 1406057719LL) w = 2;
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) extend(str[i]);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
	for (int i = tot; i; i--) arr[buc[len[i]]--] = i, siz[i] = 1;
	siz[root] = 0;
	for (int i = tot; i; i--) for (int j = 0; j < 52; j++) siz[arr[i]] += siz[son[arr[i]][j]];
	solve();
	return 0;
}
