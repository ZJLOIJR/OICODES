#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int LEN = 4e6 + 7;
const ll P = 1e7 + 9;

int tmp[P], buc[P];
int s, t, n, m, cnt = 0, len = 0, goal, arrlen = 0;
char st[LEN], str[LEN];
ll ans = 0, sum[LEN], pow[LEN], arr[LEN];

inline ll hashval(int l, int r) { return (sum[r] - sum[l - 1] * pow[r - l + 1] % P + P) % P; }
inline int insert(int hasharr[], ll x)
{
	for (int i = x % P; hasharr[i] != x && hasharr[i] != -1; ) i = (i == P) ? 0 : i + 1;
	hasharr[i]++;
	return i;
}

int main()
{
	pow[0] = 1; for (int i = 1; i <= LEN - 7; i++) pow[i] = pow[i - 1] * 29 % P;
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
	for (int i = 1; i <= len; i++) sum[i] = (sum[i - 1] * 29 % P + str[i] - 'a') % P;
	memset(buc, -1, sizeof(buc));
	for (int i = s * n + 1; i <= len; i += m) insert(buc, hashval(i, i + m - 1));
	sort(arr + 1, arr + arrlen + 1);
	goal = n + m >> 1;
	for (int i = 1; i <= s * n; i += n)
	{
		memset(tmp, 0, sizeof(tmp));
		ull goalval = hashval(i + goal, i + n - 1);
		for (int j = i; j <= i + m; j++)
			if (hashval(j, j + (n - goal) - 1) == goalval)
			{
				int l = j - 1, r = j + (n - goal);
				ull ret = (hashval(r, i + goal - 1) * pow[l - i + 1] % P + hashval(i, l)) % P;
				if (!tmp[ret]) ans += buc[insert()]
				tmp[ret] = 1;
			}
	}
	printf("%lld\n", ans);
	return 0;
}
