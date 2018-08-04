#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
const int N = 1e5 + 7;
 
inline int read()
{
    int x = 0, f = 0;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
    return f ? -x : x;
}
 
int n, lenq = 0, query = 0, maxtim = 0;
struct ques { int typ, x, y, z, z1, tim, val, pos; } q[N * 10], tmp1[N * 10], tmp2[N * 10];
int ans[N * 10], arrz[N * 10], maxz, top, sta[N * 10][3];
 
int tot = 0, root[N * 10], lson[N * 100], rson[N * 100], sum[N * 100];
void insert(int &rt, int l, int r, int po, int val)
{
    if (!rt) rt = ++tot;
    if (l == r) { sum[rt] += val; return; }
    int mid = l + r >> 1;
    if (po <= mid) insert(lson[rt], l, mid, po, val);
    else insert(rson[rt], mid + 1, r, po, val);
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
int qrysum(int rt, int l, int r, int ql, int qr)
{
    if (!rt) return 0;
    if (ql <= l && r <= qr) return sum[rt];
    int mid = l + r >> 1, ret = 0;
    if (ql <= mid) ret += qrysum(lson[rt], l, mid, ql, qr);
    if (mid + 1 <= qr) ret += qrysum(rson[rt], mid + 1, r, ql, qr);
    return ret;
}
void add(int z, int tim, int val) { for (; z <= maxz; z += (z & (-z))) insert(root[z], 1, maxtim, tim, val); }
int getsum(int z, int tim)
{
    int ret = 0;
    for (; z; z -= (z & (-z))) ret += qrysum(root[z], 1, maxtim, 1, tim);
    return ret;
}
 
int cmp(ques p, ques q) { return p.x == q.x ? p.tim < q.tim : p.x < q.x; }
int cmp1(ques p, ques q) { return p.y == q.y ? p.x < q.x : p.y < q.y; }
 
void cdq(int l, int r)
{
	if (l >= r) return;
	int mid = l + r >> 1;
	cdq(l, mid);
	int len1 = 0, len2 = 0;
	for (int i = l; i <= mid; i++) tmp1[++len1] = q[i];
	for (int i = mid + 1; i <= r; i++) tmp2[++len2] = q[i];
	sort(tmp1 + 1, tmp1 + len1 + 1, cmp1);
	sort(tmp2 + 1, tmp2 + len2 + 1, cmp1);
	int p1 = 1, p2 = 1;
	while (p2 <= len2)
	{
		while (p1 <= len1 && tmp1[p1].y <= tmp2[p2].y)
		{
			if (!tmp1[p1].typ) add(tmp1[p1].z, tmp1[p1].tim, tmp1[p1].val);
			p1++;
		}
		if (tmp2[p2].typ) ans[tmp2[p2].pos] += tmp2[p2].val * (getsum(tmp2[p2].z1, tmp2[p2].tim) - getsum(tmp2[p2].z, tmp2[p2].tim));
		p2++;
	}
	for (int i = 1; i <= p1 - 1; i++) add(tmp1[i].z, tmp1[i].tim, -tmp1[i].val);
	cdq(mid + 1, r);
}
 
int main()
{
	//freopen("input", "r", stdin);
	n = read();
	while (n--)
	{
		maxtim++;
		int x = read(), y = read(), z = read();
		arrz[++maxz] = z;
		q[++lenq] = (ques){0, x, y, z, 0, maxtim, 1, 0};
	}
	n = read();
	while (n--)
	{
		maxtim++;
		char str[10];
		scanf("%s", str);
		if (str[0] == 'Q')
		{
			int x = read(), y = read(), z = read(), r = read();
			arrz[++maxz] = z - 1, arrz[++maxz] = z + r;
			q[++lenq] = (ques){1, x + r, y + r, z - 1, z + r, maxtim, 1, ++query};
			q[++lenq] = (ques){1, x + r, y - 1, z - 1, z + r, maxtim, -1, query};
			q[++lenq] = (ques){1, x - 1, y + r, z - 1, z + r, maxtim, -1, query};
			q[++lenq] = (ques){1, x - 1, y - 1, z - 1, z + r, maxtim, 1, query};
		}
		else if (str[0] == 'A')
		{
			int x = read(), y = read(), z = read();
			arrz[++maxz] = z;
			sta[++top][0] = x, sta[top][1] = y, sta[top][2] = z;
			q[++lenq] = (ques){0, x, y, z, 0, maxtim, 1, 0};
		}
		else
		{
			int x = sta[top][0], y = sta[top][1], z = sta[top][2];
			top--, q[++lenq] = (ques){0, x, y, z, 0, maxtim, -1, 0};
		}
	}
	sort(arrz + 1, arrz + maxz + 1);
	for (int i = 1; i <= lenq; i++)
	{
		q[i].z = lower_bound(arrz + 1, arrz + maxz + 1, q[i].z) - arrz;
		if (q[i].z1) q[i].z1 = lower_bound(arrz + 1, arrz + maxz + 1, q[i].z1) - arrz;
	}
	sort(q + 1, q + lenq + 1, cmp);
	cdq(1, lenq);
	for (int i = 1; i <= query; i++) printf("%d\n", ans[i]);
    return 0;
}
