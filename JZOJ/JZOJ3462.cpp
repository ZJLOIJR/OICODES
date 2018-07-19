#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 7;

int n, h[N], tmp[N];
ll ans = 0;

void msort(int l, int r)
{
	if (l >= r) return;
	int mid = l + r >> 1;
	msort(l, mid), msort(mid + 1, r);
	int p = l, q = mid + 1, len = 0;
	while (p <= mid && q <= r)
		if (h[p] <= h[q]) tmp[++len] = h[p++];
		else ans += mid - p + 1, tmp[++len] = h[q++];
	while (p <= mid) tmp[++len] = h[p++];
	while (q <= r) tmp[++len] = h[q++];
	for (int i = 1; i <= len; i++) h[l + i - 1] = tmp[i];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", h + i);
	h[0] = h[n + 1] = 666666666;
	for (int i = 1, las = 1; i <= n + 1; i++)
		if (h[i] > h[i - 1])
		{
			ans++;
			for (int j = las; j <= i - 1; j++) tmp[j] = h[j];
			for (int j = las; j <= i - 1; j++) h[j] = tmp[i + las - 1 - j];
			las = i;
		}
	msort(1, n);
	printf("%lld\n", ans);
	return 0;
}
