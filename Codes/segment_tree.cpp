//vector<int> seg;
// void build(const vector<int> &a, int ind, int tl, int tr)
// {
// 	if(tl==tr)
// 	{
// 		seg[ind] = a[tl];
// 		return;
// 	}
// 	else
// 	{
// 		int tm = (tl+tr)/2;
// 		build(a, 2*ind + 1, tl, tm);
// 		build(a, 2*ind + 2, tm+1, tr);
// 		seg[ind] = max(seg[2*ind + 1], seg[2*ind + 2]);
// 	}
// }

// int query(int ind, int tl, int tr, int l, int r)
// {
// 	if(tl>=l && tr<=r) return seg[ind];
// 	if(tl>r || tr<l) return LLONG_MIN;
// 	else
// 	{
// 		int tm = (tl+tr)/2;
// 		int left = query(2*ind + 1, tl, tm, l, r);
// 		int right = query(2*ind + 2, tm+1, tr, l, r);
// 		return max(left, right);
// 	}
// }


// int log(int n)
// {
//     int k = 0;
//     while (n >= 3) { n /= 3; ++k; }
//     return k;
// }

// int pw(int n)
// {
// 	int k = 1;
// 	while(n--) k *= 3;
// 	return k;
// }
