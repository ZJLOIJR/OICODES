#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

int n, full, a[20], ans[20];
char str[20];
ll f[1 << 17][20], k;

int bit(int x) { return 1 << (x - 1); }

ll dfs(int S, int mo, int zero)
{
	if (S == full) return (!zero && !mo) ? 1 : 0;
	if (f[S][mo] && !zero) return f[S][mo];
	ll ret = 0;
	for (int i = 1, last = 0; i <= n; i++)
		if (!(bit(i) & S) && (a[i] != a[last]) && (!zero || a[i]))
			last = i, ret += dfs(S | bit(i), (mo * 10 + a[i]) % 17, (zero && !a[i]));
	if (!zero) f[S][mo] = ret;
	return ret;
}

void solve(int len, int S, int mo, int zero)
{
	if (!len) return;
	for (int i = 1, last = 0; i <= n; i++)
		if (!(bit(i) & S) && (a[i] != a[last]) && (!zero || a[i]))
		{
			ll tmp = dfs(S | bit(i), (mo * 10 + a[i]) % 17, (zero && !a[i]));
			if (k > tmp) k -= tmp, last = i;
			else
			{
				putchar(a[i] + '0');
				solve(len - 1, S | bit(i), (mo * 10 + a[i]) % 17, (zero && !a[i]));
				break;
			}
		}
}


int main()
{
	scanf("%s%lld", str + 1, &k);
	n = strlen(str + 1);
	for (int i = 1; i <= n; i++) a[i] = str[i] - '0';
	sort(a + 1, a + n + 1), a[0] = -1;
	full = (1 << n) - 1;
	solve(n, 0, 0, 1);
	putchar('\n');
	return 0;
}
