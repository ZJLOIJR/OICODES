#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 2e7 + 7;

int n, k, P, A, B, C, D;
int S[N], pre[N], suf[N];
ll ans;

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
	
	scanf("%d%d%d%d%d%d%d", &n, &k, &P, &A, &B, &C, &D);
	S[1] = A;
	for (int i = 2; i <= n; i++) S[i] = (S[i - 1] * 1LL * B + C) % D;
	for (int l = 1; l <= n; l += k)
	{
		int r = min(l + k - 1, n);
		pre[l] = S[l];
		for (int j = l + 1; j <= r; j++) pre[j] = pre[j - 1] * 1LL * S[j] % P;
		suf[r] = S[r];
		for (int j = r - 1; j >= l; j--) suf[j] = suf[j + 1] * 1LL * S[j] % P;
	}
	for (int l = 1; l <= n - k + 1; l++)
	{
		int r = min(l + k - 1, n);
		if (pre[l] == S[l]) ans ^= pre[r];
		else ans ^= (suf[l] * 1LL * pre[r] % P);
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
