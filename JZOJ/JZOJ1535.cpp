#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 12;
typedef long long ll;

int n, len = 0;
ll arr[LEN], f[LEN][LEN][2];

ll solve(int length, int flag, int cnt ,int zero)
{
	if (!length) return cnt;
	if (!flag && ~f[length][cnt][zero]) return f[length][cnt][zero];
	int maxx = flag ? arr[length] : 9;
	ll ret = 0;
	for (int i = 0; i <= maxx; i++)
		ret += solve(length - 1, (flag && i == maxx), cnt + ((!flag || i) && i == 1), (zero && !i));
	if (!flag) f[length][cnt][zero] = ret;
	return ret;
}

int main()
{
	memset(f, 0xff, sizeof(f));
	scanf("%d", &n);
	while (n)
	{
		arr[++len] = n % 10;
		n /= 10;
	}
	printf("%lld\n", solve(len, 1, 0, 1));
	return 0;
}
