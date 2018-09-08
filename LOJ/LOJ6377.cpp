#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

char str[N];
int n, length;

int t0, tot, p, q, np, nq, last;
int link[N << 1], next[N << 1][26], len[N << 1];
int buc[N], arr[N << 1], sg[N << 1], tmp[5];
void extend(char ch)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1;
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
void init()
{
	tot = 0;
	memset(link, 0, sizeof(link));
	memset(next, 0, sizeof(next));
	memset(len, 0, sizeof(len));
	memset(buc, 0, sizeof(buc));
	memset(arr, 0, sizeof(arr));
	memset(sg, 0, sizeof(sg));
	t0 = last = ++tot;
	length = strlen(str + 1);
	for (int i = 1; i <= length; i++) extend(str[i]);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= length; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--)
	{
		int x = arr[i];
		sg[x] = 0;
		memset(tmp, 0, sizeof(tmp));
		for (int j = 0; j < 26; j++) if (next[x][j]) tmp[sg[next[x][j]]]++;
		for (int i = 0; i < 5; i++) if (!tmp[i]) { sg[x] = i; break; }
	}
}
void solve()
{
	scanf("%d", &n);
	int ret = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str + 1);
		length = strlen(str + 1);
		int now = t0;
		for (int j = 1; j <= length; j++) now = next[now][str[j] - 'a'];
		ret ^= sg[now];
	}
	printf(ret ? "Alice\n" : "Bob\n");
}

int main()
{
	while (~scanf("%s", str + 1)) init(), solve();
	return 0;
}
