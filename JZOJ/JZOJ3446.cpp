#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 37;
const char set[3] = {'T', 'L', 'R'};

int n, po;
char str1[N], str2[N], tri;

ll min(ll a, ll b) { return a < b ? a : b; }

ll move(char *s, char ch)
{
	ll ret = 0;
	for (int i = po + 1; i <= n; i++) if (s[i] != ch) ret += (1LL << (n - i));
	return ret;
}

int main()
{
	freopen("tri.in", "r", stdin);
	freopen("tri.out", "w", stdout);

	scanf("%d%s%s", &n, str1 + 1, str2 + 1);
	po = 1;
	while (str1[po] == str2[po] && po <= n) po++;
	if (po == n + 1) { printf("0\n"); return 0; }
	for (int i = 0; i < 3; i++) if (set[i] != str1[po] && set[i] != str2[po]) tri = set[i];
	printf("%lld\n", min(move(str1, str2[po]) + move(str2, str1[po]) + 1, move(str1, tri) + move(str2, tri) + (1LL << (n - po)) + 1));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
