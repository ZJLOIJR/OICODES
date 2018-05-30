#include <queue>
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 1e5 + 7;

int n, tot = 0, st[N], to[N << 1], nx[N << 1], siz[N];
ll ans = 0, f[N];
priority_queue<ll> que;

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

ll huffman()
{
	ll ret = 0;
	while (que.size() > 1)
	{
		ll a = -que.top(); que.pop();
		ll b = -que.top(); que.pop();
		ret += a + b;
		que.push(-(a + b));
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	for (int i = 2, f; i <= n; i++) scanf("%d", &f), add(f, i);
	for (int i = n; i >= 1; i--)
	{
		while (!que.empty()) que.pop();
		siz[i] = 1;
		for (int j = st[i]; j; j = nx[j]) siz[i] += siz[to[j]], f[i] += f[to[j]], que.push(-siz[to[j]]);
		f[i] += huffman();
	}
	printf("%lld\n", f[1]);
	return 0;
}
