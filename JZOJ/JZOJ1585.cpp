#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 20;
typedef long long ll;

int len = 0;
ll n, l, r, arr[LEN], f[LEN][LEN][2];

ll solve(int length, int flag, int cnt, int zero, int match)
{
	if (!length) return cnt;
	if (!flag && ~f[length][cnt][zero]) return f[length][cnt][zero];
	int maxx = flag ? arr[length] : 9;
	ll ret = 0;
	for (int i = 0; i <= maxx; i++)
		ret += solve(length - 1, (flag && i == maxx), cnt + ((!zero || i) && i == match), (zero && !i), match);
	if (!flag) f[length][cnt][zero] = ret;
	return ret;
}

ll get(ll num, int match)
{
	memset(f, 0xff, sizeof(f));
	len = 0;
	while (num)
	{
		arr[++len] = num % 10;
		num /= 10;
	}
	return solve(len, 1, 0, 1, match);
}

int main()
{
	scanf("%lld%lld", &l, &r);
	for (int i = 0; i < 10; i++)
		printf("%lld ", get(r, i) - get(l - 1, i));
	return 0;
}
