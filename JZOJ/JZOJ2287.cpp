#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

typedef long long ll;
const int N = 4e5 + 7;

int n, m, lenq = 0, query = 0;
struct ques { int typ, x, y, val, id, pos; } q[N], tmp[N];
int buc[N];
ll last, ans[N];

int sum[N];
void add(int po, int val) { for (; po <= n; po += (po & (-po))) sum[po] += val; }
int getsum(int po)
{
	int ret = 0;
	for (; po; po -= (po & (-po))) ret += sum[po];
	return ret;
}

int operator<(ques a, ques b) { return a.x == b.x ? a.id < b.id : a.x < b.x; }

void cdq(int l, int r)
{
	if (l >= r) return;
	int mid = l + r >> 1;
	cdq(l, mid), cdq(mid + 1, r);
	int len = 0, p1 = l, p2 = mid + 1;
	while (p1 <= mid && p2 <= r)
		if (q[p1] < q[p2])
		{
			if (!q[p1].typ) add(q[p1].y, q[p1].val);
			tmp[++len] = q[p1++];
		}
		else
		{
			if (q[p2].typ) ans[q[p2].pos] += q[p2].val * getsum(q[p2].y);
			tmp[++len] = q[p2++];
		}
	while (p1 <= mid)
	{
		if (!q[p1].typ) add(q[p1].y, q[p1].val);
		tmp[++len] = q[p1++];
	}
	while (p2 <= r)
	{
		if (q[p2].typ) ans[q[p2].pos] += q[p2].val * getsum(q[p2].y);
		tmp[++len] = q[p2++];
	}
	for (int i = l; i <= mid; i++) if (!q[i].typ) add(q[i].y, -q[i].val);
	for (int i = 1; i <= len; i++) q[l + i - 1] = tmp[i];
}

int main()
{
	n = read(), m = read();
	for (int i = 1, a; i <= n; i++)
	{
		a = read(), a = n - a + 1;
		buc[a] = i;
		last += getsum(a - 1), add(a, 1);
		q[++lenq] = (ques){0, i, a, 1, lenq, 0};
	}
	for (int i = 1, a; i <= m; i++)
	{
		a = read(), a = n - a + 1;
		q[++lenq] = (ques){1, n, n, 1, lenq, ++query};
		q[++lenq] = (ques){1, buc[a], n, -1, lenq, query};
		q[++lenq] = (ques){1, n, a, -1, lenq, query};
		q[++lenq] = (ques){1, buc[a], a, 1, lenq, query};
		if (buc[a] > 1 && a > 1) q[++lenq] = (ques){1, buc[a] - 1, a - 1, 1, lenq, query};
		q[++lenq] = (ques){0, buc[a], a, -1, lenq, 0};
	}
	memset(sum, 0, sizeof(sum));
	cdq(1, lenq);
	for (int i = 1; i <= query; i++)
	{
		printf("%lld\n", last);
		last -= ans[i];
	}
	return 0;
}
