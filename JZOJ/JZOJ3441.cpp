#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1
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
const int N = 1e5 + 7;

int n, m, k, r, s, t, cnt[N];
ll ans = 0;
struct note { int pos, value; };
vector<note> list[N << 1];

int siz[N << 2];
void insert(int rt, int l, int r, int po, int val)
{
	siz[rt] += val;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) insert(lson, l, mid, po, val);
	else insert(rson, mid + 1, r, po, val);
}
int getkth(int rt, int l, int r, int k)
{
	if (l == r) return l;
	int mid = l + r >> 1, tmp = siz[rson];
	if (k > tmp) return getkth(lson, l, mid, k - tmp);
	else return getkth(rson, mid + 1, r, k);
}

int main()
{
	n = read(), m = read(), k = read();
	while (n--)
	{
		r = read(), s = read() + m, t = read() + m;
		list[s].push_back((note){r, 1});
		list[t].push_back((note){r, -1});
		if (s > t) list[0].push_back((note){r, 1});
	}
	for (int i = 0; i <= 2 * m - 1; i++)
	{
		int len = list[i].size();
		for (int j = 0; j < len; j++) insert(1, 1, N - 7, list[i][j].pos, list[i][j].value);
		if (k > siz[1]) continue;
		int kth = getkth(1, 1, N - 7, k);
		ans += kth * 1LL * kth;
	}
	printf("%lld\n", ans);
	return 0;
}
