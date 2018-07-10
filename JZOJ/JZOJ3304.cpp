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
 
int n, lenq = 0, query = 0;
struct ques { int typ, x, y, z, y1, z1, id, val, pos; } q[N * 10], tmp[N * 10];
int ans[N * 10], arrx[N * 10], maxx, arry[N * 10], maxy, arrz[N * 10], maxz, top, sta[N * 10][3];
 
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
void add(int y, int z, int val) { for (; y <= maxy; y += (y & (-y))) insert(root[y], 1, maxz, z, val); }
int getsum(int y, int z1, int z2)
{
    int ret = 0;
    for (; y; y -= (y & (-y))) ret += qrysum(root[y], 1, maxz, z1, z2);
    return ret;
}
 
int cmp(ques p, ques q) { return p.x == q.x ? p.typ < q.typ : p.x < q.x; }
 
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    for (int i = l; i <= r; i++)
    {
        if (q[i].id <= mid && !q[i].typ) add(q[i].y, q[i].z, q[i].val);
        if (q[i].id > mid && q[i].typ) ans[q[i].pos] += q[i].val * (getsum(q[i].y1, q[i].z, q[i].z1) - getsum(q[i].y - 1, q[i].z, q[i].z1));
    }
    for (int i = l; i <= r; i++) if (q[i].id <= mid && !q[i].typ) add(q[i].y, q[i].z, -q[i].val);
    int p1 = l, p2 = mid + 1;
    for (int i = l; i <= r; i++)
        if (q[i].id <= mid) tmp[p1++] = q[i];
        else tmp[p2++] = q[i];
    for (int i = l; i <= r; i++) q[i] = tmp[i];
    cdq(l, mid), cdq(mid + 1, r);
}
 
int main()
{
    n = read();
    while (n--)
    {
        int x = read(), y = read(), z = read();
        q[++lenq] = (ques){0, x, y, z, 0, 0, lenq, 1, 0};
    }
    n = read();
    while (n--)
    {
        char str[10]; scanf("%s", str);
        if (str[0] == 'A')
        {
            int x = read(), y = read(), z = read();
            q[++lenq] = (ques){0, x, y, z, 0, 0, lenq, 1, 0};
			sta[++top][0] = x, sta[top][1] = y, sta[top][2] = z;
        }
        else if (str[0] == 'C')
		{
            q[++lenq] = (ques){0, sta[top][0], sta[top][1], sta[top][2], 0, 0, lenq, -1, 0};
			top--;
		}
        else
        {
            int x = read(), y = read(), z = read(), r = read();
            q[++lenq] = (ques){1, x + r, y, z, y + r, z + r, lenq, 1, ++query};
            q[++lenq] = (ques){1, x - 1, y, z, y + r, z + r, lenq, -1, query};
        }
    }
    for (int i = 1; i <= lenq; i++) arrx[++maxx] = q[i].x, arry[++maxy] = q[i].y, arrz[++maxz] = q[i].z;
    sort(arrx + 1, arrx + maxx + 1);
    maxx = unique(arrx + 1, arrx + maxx + 1) - arrx - 1;
    sort(arry + 1, arry + maxy + 1);
    maxy = unique(arry + 1, arry + maxy + 1) - arry - 1;
    sort(arrz + 1, arrz + maxz + 1);
    maxz = unique(arrz + 1, arrz + maxz + 1) - arrz - 1;
    for (int i = 1; i <= lenq; i++)
    {
        q[i].x = lower_bound(arrx + 1, arrx + maxx + 1, q[i].x) - arrx;
        q[i].y = lower_bound(arry + 1, arry + maxy + 1, q[i].y) - arry;
        q[i].z = lower_bound(arrz + 1, arrz + maxz + 1, q[i].z) - arrz;
    }
    sort(q + 1, q + lenq + 1, cmp);
    cdq(1, lenq);
    for (int i = 1; i <= query; i++) printf("%d\n", ans[i]);
    return 0;
}
