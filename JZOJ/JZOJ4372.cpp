#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

inline int min(int a, int b) { return a < b ? a : b; }
const int N = 1e5 + 7;

int t0, tot, p, q, np, nq, last, length;
int link[N << 1], next[N << 1][26], len[N << 1], size[N << 1], right[N << 1];
char str[N];
int buc[N], arr[N << 1];

void extend(int pos)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, size[np] = 1, right[np] = pos;
	int num = str[pos] - 'a';
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
			link[nq] = link[q], len[nq] = len[p] + 1, size[nq] = size[q], right[nq] = right[q];
			link[np] = link[q] = nq;
			while (p && next[p][num] == q) next[p][num] = nq, p = link[p];
		}
	}
}

int tag[N << 2][2], mi[N << 2][2];
void down(int rt, int l, int r, int k)
{
	if (!tag[rt][k]) return;
	if (l != r)
	{
		if (tag[lson][k]) tag[lson][k] = min(tag[lson][k], tag[rt][k]);
		else tag[lson][k] = tag[rt][k];
		if (tag[rson][k]) tag[rson][k] = min(tag[rson][k], tag[rt][k]);
		else tag[rson][k] = tag[rt][k];
	}
	mi[rt][k] = min(mi[rt][k], tag[rt][k]), tag[rt][k] = 0;
}
void change(int rt, int l, int r, int ql, int qr, int val, int k)
{
	down(rt, l, r, k);
	if (ql <= l && r <= qr) { tag[rt][k] = val; return; }
	int mid = l + r >> 1;
	if (ql <= mid) change(lson, l, mid, ql, qr, val, k);
	if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr, val, k);
	down(lson, l, mid, k), down(rson, mid + 1, r, k);
	mi[rt][k] = min(mi[lson][k], mi[rson][k]);
}
void print(int rt, int l, int r)
{
	down(rt, l, r, 0), down(rt, l, r, 1);
	if (l == r)
	{
		printf("%d\n", min(mi[rt][0], mi[rt][1] - l));
		return;
	}
	int mid = l + r >> 1;
	print(lson, l, mid), print(rson, mid + 1, r);
}

int main()
{
	memset(mi, 0x3f, sizeof(mi));
	t0 = last = ++tot;
	scanf("%s", str + 1);
	length = strlen(str + 1);
	for (int i = 1; i <= length; i++) extend(i);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= length; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--) size[link[arr[i]]] += size[arr[i]];
	for (int i = 2; i <= tot; i++)
		if (size[i] == 1)
		{
			change(1, 1, length, right[i] - len[link[i]], right[i], len[link[i]] + 1, 0);
			if (right[i] - len[i] + 1 <= right[i] - len[link[i]] - 1)
				change(1, 1, length, right[i] - len[i] + 1, right[i] - len[link[i]] - 1, right[i] + 1, 1);
		}
	print(1, 1, length);
	return 0;
}
