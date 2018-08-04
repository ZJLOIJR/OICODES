#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 2e5 + 7;

int n, ans[N];
struct ques { int x, y, id; } q[N], tmp1[N], tmp2[N];

int cmp(ques a, ques b) { return a.y == b.y ? a.x < b.x : a.y < b.y; }
int cmp1(ques a, ques b) { return a.x == b.x ? a.id < b.id : a.x < b.x; }

int mx[N];
void add(int po, int val) { for (; po <= n; po += (po & (-po))) mx[po] = max(mx[po], val); }
void clear(int po) { for (; po <= n; po += (po & (-po))) mx[po] = 0; }
int getmax(int po)
{
	int ret = 0;
	for (; po; po -= (po & (-po))) ret = max(ret, mx[po]);
	return ret;
}

void cdq(int l, int r)
{
	if (l >= r) { ans[q[l].id] = max(ans[q[l].id], 1); return; }
	int mid = l + r >> 1;
	cdq(l, mid);
	int len1 = 0, len2 = 0;
	for (int i = l; i <= mid; i++) tmp1[++len1] = q[i];
	for (int i = mid + 1; i <= r; i++) tmp2[++len2] = q[i];
	sort(tmp1 + 1, tmp1 + len1 + 1, cmp);
	sort(tmp2 + 1, tmp2 + len2 + 1, cmp);
	int p1 = 1, p2 = 1;
	while (p2 <= len2)
	{
		while (p1 <= len1 && tmp1[p1].y <= tmp2[p2].y) add(tmp1[p1].id, ans[tmp1[p1].id]), p1++;
		ans[tmp2[p2].id] = max(ans[tmp2[p2].id], getmax(tmp2[p2].id - 1) + 1), p2++;
	}
	for (int i = 1; i <= p1 - 1; i++) clear(tmp1[i].id);
	cdq(mid + 1, r);
}

int main()
{
	freopen("picks.in", "r", stdin);
	freopen("picks.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &q[i].x, &q[i].y), q[i].id = i;
	sort(q + 1, q + n + 1, cmp1);
	cdq(1, n);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
