#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 7 + 200;

int n, length;
char str[N];
int p, q, np, nq, last, tot, t0;
int next[N << 1][27], link[N << 1], len[N << 1], size[N << 1];
int buc[N], arr[N << 1];

void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, size[np] = 1;
	int num = ch - 'a';
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
	scanf("%d", &n); getchar();
	while (n--)
	{
		for(char ch = getchar(); ch >= 'a' && ch <= 'z'; ch = getchar()) str[++length] = ch;
		str[++length] = '{';
	}
	for (int i = 1; i <= length; i++) extend(str[i]);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= length; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--) size[link[arr[i]]] += size[arr[i]];
	int i = 1, now = t0;
	while (i <= length)
	{
		while (str[i] != '{') now = next[now][str[i] - 'a'], i++; i = i + 1;
		printf("%d\n", size[now]);
		now = t0;
	}
	return 0;
}
