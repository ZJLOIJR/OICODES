#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
const int LEN = 4e6 + 7;

map<ull, int> buc, tmp;
int s, t, n, m, cnt = 0, len = 0, goal;
char st[LEN], str[LEN];
ull sum[LEN], pow[LEN];
ll ans = 0;

inline ull hashval(int l, int r) { return sum[r] - sum[l - 1] * pow[r - l + 1]; }

int main()
{
	pow[0] = 1; for (int i = 1; i <= LEN - 7; i++) pow[i] = pow[i - 1] * 29;
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
	for (int i = 1; i <= len; i++) sum[i] = sum[i - 1] * 29 + str[i] - 'a';
	for (int i = s * n + 1; i <= len; i += m) buc[hashval(i, i + m - 1)]++;
	goal = n + m >> 1;
	for (int i = 1; i <= s * n; i += n)
	{
		tmp.clear();
		ull goalval = hashval(i + goal, i + n - 1);
		for (int j = i; j <= i + n - 2 * goal; j++)
			if (hashval(j, j + goal - 1) == goalval)
			{
				int l = j - 1, r = j + goal;
				ull ret = hashval(r, i + n - 1 - goal) * pow[j - 1] + hashval(1, l);
				//if (!tmp[ret]) ans += buc[ret];
				//tmp[ret] = 1;
				ans += buc[ret];
			}
	}
	printf("%lld\n", ans);
	return 0;
}
