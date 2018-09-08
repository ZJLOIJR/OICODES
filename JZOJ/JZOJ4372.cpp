#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int LEN = 1e5 + 7;

int t0, tot, p, q, np, nq, last;
int link[LEN << 1], next[LEN << 1][26], len[LEN << 1], size[LEN << 1], endpos[LEN << 1];
char length, str[LEN];
int buc[LEN], arr[LEN << 1];

inline int min(int a, int b) { return a < b ? a : b; }

void extend(int pos)
{
	p = last, np = ++tot, last = np;
	len[np] = len[p] + 1, endpos[np] = pos, size[np] = 1;
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
			link[nq] = link[q], size[nq] = size[q], endpos[nq] = endpos[q], len[nq] = len[p] + 1;
			link[q] = link[np] = nq;
			while (p && next[p][num] == q) next[p][num] = nq, p = link[p];
		}
	}
}

int tag[LEN << 1][2], mi[LEN << 1][2];
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
	freopen("input", "r", stdin);
	t0 = last = ++tot;
	scanf("%s", str + 1);
	length = strlen(str + 1);
	for (int i = 1; i <= length; i++) extend(i);
	for (int i = 1; i <= tot; i++) buc[len[i]]++;
	for (int i = 1; i <= length; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[len[i]]--] = i;
	for (int i = tot; i; i--) size[link[i]] += size[i];
	for (int i = 1; i <= tot; i++)
		if (size[i] == 1)
		{
			change(1, 1, length, endpos[i] - len[link[i]], endpos[i], len[link[i]] + 1, 0);
			if (endpos[i] - len[link[i]] - 1 > 0) change(1, 1, length, endpos[i] - len[link[i]] - 1, endpos[i] - len[i], endpos[i] + 1, 1);
		}
	print(1, 1, length);
	return 0;
}
