#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 3e5 + 7, MAX = 1000000000;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, t, p;
char str[10];

int tot = 0, root[N], lson[N * 100], rson[N * 100], siz[N * 100];
ll ans, sum[N * 100];
void insert(int &rt, int l, int r, int po, int val)
{
	if (!rt) rt = ++tot;
	siz[rt] += val, sum[rt] += 1LL * po * val;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) insert(lson[rt], l, mid, po, val);
	else insert(rson[rt], mid + 1, r, po, val);
}
int getkth(int rt, int l, int r, int k)
{
	if (l == r)
	{
		ans += 1LL * min(siz[rt], k) * l;
		return l;
	}
	int mid = l + r >> 1;
	if (k <= siz[rson[rt]]) return getkth(rson[rt], mid + 1, r, k);
	else
	{
		ans += sum[rson[rt]];
		return getkth(lson[rt], l, mid, k - siz[rson[rt]]);
	}
}

int main()
{
	freopen("grimoire.in", "r", stdin);
	freopen("grimoire.out", "w", stdout);
	
	n = read(), m = read();
	while (m--)
	{
		scanf("%s", str);
		t = read(), p = read();
		if (str[0] == 'B')
		{
			int k = getkth(root[t], 0, MAX, t);
			insert(root[t], 0, MAX, p, 1);
			if (p >= k) insert(root[0], 0, MAX, p, 1), insert(root[0], 0, MAX, k, -1);
		}
		else
		{
			int k = getkth(root[t], 0, MAX, t + 1);
			insert(root[t], 0, MAX, p, -1);
			if (p >= k) insert(root[0], 0, MAX, p, -1), insert(root[0], 0, MAX, k, 1);
		}
		ans = 0;
		getkth(root[0], 0, MAX, n);
		printf("%lld\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
