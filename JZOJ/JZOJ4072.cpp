#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 5e5 + 7;

char str[LEN];
int t, k, n;

int root, tot, p, q, np, nq, last;
int son[LEN << 1][26], fa[LEN << 1], len[LEN << 1], sum[LEN << 1], siz[LEN << 1];

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, siz[np]++, sum[np]++;
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
			fa[nq] = fa[q], siz[nq] = siz[q];
			fa[np] = fa[q] = nq;
			while (p && son[p][ch - 'a'] == q) son[p][ch - 'a'] = nq, p = fa[p];
		}
	}
}
int buc[LEN], arr[LEN << 1];
int main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);

	root = last = ++tot;
	scanf("%s%d%d", str + 1, &t, &k);
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) extend(str[i]);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--)
		if (t) sum[fa[arr[i]]] += sum[arr[i]];
		else sum[arr[i]] = 1;
	sum[1] = 0;
	for (int i = tot; i; i--)
	{
		siz[arr[i]] = sum[arr[i]];
		for (int j = 0; j < 26; j++)
			siz[arr[i]] += siz[son[arr[i]][j]];
	}
	if (k > siz[root]) printf("-1");
	else
	{
		int x = root;
		while (k > sum[x])
		{
			k -= sum[x];
			for (int i = 0; i < 26; i++)
				if (son[x][i])
				{
					if (k > siz[son[x][i]]) k -= siz[son[x][i]];
					else { putchar(i + 'a'), x = son[x][i]; break; }
				}
		}
	}
	putchar('\n');

	fclose(stdin);
	fclose(stdout);
	return 0;
}
