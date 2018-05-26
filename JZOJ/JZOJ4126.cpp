#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int LEN = 4e6 + 7;
const ll P = 163227661;

map<ll, int> buc, tmp;
int s, t, n, m, cnt = 0, len = 0, goal;
char st[LEN], str[LEN];
ll ans = 0, sum[LEN], pow[LEN];

inline ll hashval(int l, int r) { return (sum[r] - sum[l - 1] * pow[r - l + 1] % P + P) % P; }

int main()
{
	pow[0] = 1; for (int i = 1; i <= LEN - 7; i++) pow[i] = pow[i - 1] * 26 % P;
	scanf("%d%d%d%d", &s, &t, &n, &m); getchar();
	for (char ch = getchar(); ch != EOF; ch = getchar()) if (ch >= 'a' && ch <= 'z') st[++cnt] = ch;
	if (n < m)
	{
		for (int i = s * n + 1; i <= cnt; i++) str[++len] = st[i];
		for (int i = 1; i <= s * n; i++) str[++len] = st[i];
		n ^= m ^= n ^= m;
		s ^= t ^= s ^= t;
	}
	else for (int i = 1; i <= cnt; i++) str[++len] = st[i];
	for (int i = 1; i <= len; i++) sum[i] = (sum[i - 1] * 26 % P + str[i] - 'a') % P;
	for (int i = s * n + 1; i <= len; i += m) buc[hashval(i, i + m - 1)]++;
	goal = n + m >> 1;
	for (int i = 1; i <= s * n; i += n)
	{
		tmp.clear();
		for (int j = i; j <= i + n - 2 * goal; j++)
		{
			if (hashval(j, j + goal - 1) == hashval(i + goal, i + n - 1))
			{

			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
