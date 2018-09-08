#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 2e4 + 7;

int n, k, a;
int p, q, np, nq, tot, last, t0;
int len[N << 1], link[N << 1], size[N << 1];
map<int, int> next[N << 1];
int buc[N], arr[N << 1];

void extend(int num)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, size[np] = 1;
	while (p && !next[p][num]) next[p][num] = np, p = link[p];
	if (!p) link[np] = t0;
	else
	{
		q = next[p][num];
		if (len[p] + 1 == len[q]) link[np] = q;
		else
		{
			nq = ++tot;
			len[nq] = len[p] + 1, link[nq] = link[q], next[nq] = next[q];
			link[q] = link[np] = nq;
			while (p && next[p][num] == q) next[p][num] = nq, p = link[p];
		}
	}
}

int main()
{
	t0 = last = ++tot;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a), extend(a);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--) size[link[arr[i]]] += size[arr[i]];
	int ans = 0;
	for (int i = t0 + 1; i <= tot; i++) if (size[i] >= k && len[i] > ans) ans = len[i];
	printf("%d\n", ans);
	return 0;
}
