#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 7;
inline ll max(ll a, ll b) { return a > b ? a : b; }

int n, len, num[70];
int tot = 1, son[N * 70][2];
ll a[N], ans = 0;

void insert()
{
	int now = 1;
	for (int i = 64; i >= 1; i--)
	{
		if (!son[now][num[i]]) son[now][num[i]] = ++tot;
		now = son[now][num[i]];
	}
}

ll getans()
{
	int now = 1; ll ret = 0;
	for (int i = 64; i >= 1; i--)
	{
		if (son[now][!num[i]]) now = son[now][!num[i]], ret += (1LL << (i - 1));
		else now = son[now][num[i]];
	}
	return ret;
}

int main()
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		len = 0; memset(num, 0, sizeof(num));
		ll tmp = a[i];
		while (tmp) num[++len] = tmp & 1, tmp >>= 1;
		insert();
	}
	for (int i = 1; i <= n; i++)
	{
		len = 0; memset(num, 0, sizeof(num));
		ll tmp = a[i];
		while (tmp) num[++len] = tmp & 1, tmp >>= 1;
		ans = max(ans, getans());
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
