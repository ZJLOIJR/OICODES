#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e4 + 7;

int n, m, lens, lent, ans;
int t0, tot, last, p, q, np, nq;
int next[N << 1][26], link[N << 1], len[N << 1];
char str[100];

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1;
	int num = ch - 'A';
	while (p && !next[p][num]) next[p][num] = np, p = link[p];
	if (!p) link[np] = t0;
	else
	{
		q = next[p][num];
		if (len[p] + 1 == len[q]) link[np] = q;
		else
		{
			nq = ++tot;
			memcpy(next[nq], next[q], sizeof(next[q]));
			link[nq] = link[q], len[nq] = len[p] + 1;
			link[np] = link[q] = nq;
			while (p && next[p][num] == q) next[p][num] = nq, p = link[p];
		}
	}
}

int main()
{
	t0 = last = ++tot;
	scanf("%d%d", &n, &m);
	while (lens < n)
	{
		scanf("%s", str);
		int len = strlen(str);
		for (int i = 0; i < len; i++) extend(str[i]), lens++;
	}
	int now = t0;
	while (lent < m)
	{
		scanf("%s", str);
		int len = strlen(str);
		for (int i = 0; i < len; i++)
		{
			if (!next[now][str[i] - 'A']) now = t0, ans++;
			now = next[now][str[i] - 'A'];
			lent++;
		}
	}
	printf("%d\n", ans + 1);
	return 0;
}
