struct SegmentTree
{
	ll sum[N << 2], mtp[N << 2], inc[N << 2];

	void down(int rt, int l, int r)
	{
		if (mtp[rt] == 1 && inc[rt] == 0) return;
		if (l != r)
			mtp[lson] = mtp[lson] * mtp[rt] % P,
			mtp[rson] = mtp[rson] * mtp[rt] % P, 
			inc[lson] = (inc[lson] * mtp[rt] % P + inc[rt]) % P;
			inc[rson] = (inc[rson] * mtp[rt] % P + inc[rt]) % P;
		sum[rt] = (sum[rt] * mtp[rt] % P + inc[rt] * (r - l + 1) % P) % P;
		mtp[rt] = 1, inc[rt] = 0;
	}

	void build(int rt, int l, int r)
	{
		mtp[rt] = 1, inc[rt] = 0;
		if (l == r) { sum[rt] = a[l]; return; }
		int mid = l + r >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		sum[rt] = sum[lson] + sum[rson];
	}
	
	ll qrysum(int rt, int l, int r)
	{
		down(rt, l, r);
		if (L <= l && r <= R) return sum[rt];
		ll ret = 0; int mid = l + r >> 1;
		if (L <= mid) ret = (ret + qrysum(lson, l, mid)) % P;
		if (mid + 1 <= R) ret = (ret + qrysum(rson, mid + 1, r)) % P;
		return ret;
	}

	void rangeplus(int rt, int l, int r)
	{
		down(rt, l, r);
		if (L <= l && r <= R) { inc[rt] = (inc[rt] + k) % P; return; }
		int mid = l + r >> 1;
		if (L <= mid) rangeplus(lson, l, mid);
		if (mid + 1 <= R) rangeplus(rson, mid + 1, r);
		down(lson, l, mid), down(rson, mid + 1, r);
		sum[rt] = (sum[lson] + sum[rson]) % P;
	}

	void rangemtp(int rt, int l, int r)
	{
		down(rt, l, r);
		if (L <= l && r <= R) { mtp[rt] = mtp[rt] * k % P, inc[rt] = inc[rt] * k % P; return; }
		int mid = l + r >> 1;
		if (L <= mid) rangemtp(lson, l, mid);
		if (mid + 1 <= R) rangemtp(rson, mid + 1, r);
		down(lson, l, mid), down(rson, mid + 1, r);
		sum[rt] = (sum[lson] + sum[rson]) % P;
	}
} tree;