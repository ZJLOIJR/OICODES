#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e6 + 7;
const ll INF = 1LL << 62;

multiset<ll> set1, set2;
multiset<ll>::iterator it;

int n, l, r, a[N];
ll suf, pre, ans;

void del(ll val)
{
	it = set1.find(val);
	suf = *(++it); it--;
	pre = *(--it); it++;
	set2.insert(suf - pre);
	set2.erase(set2.find(suf - val));
	set2.erase(set2.find(val - pre));
	set1.erase(it);
}

void add(ll val)
{
	it = set1.insert(val);
	suf = *(++it); it--;
	pre = *(--it); it++;
	set2.erase(set2.find(suf - pre));
	set2.insert(suf - val);
	set2.insert(val - pre);
}

int main()
{
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	set1.insert(-INF), set1.insert(INF), set2.insert(INF << 1), add(a[1]), add(a[2]);
	l = 1, r = 2, ans = 1e9;
	while (r <= n)
	{
		ans = min(ans, max(*set2.begin(), r - l + 1LL));
		if (r - l + 1 <= *set2.begin() || r - l + 1 <= 2) add(a[++r]);
		else del(a[l++]);
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
