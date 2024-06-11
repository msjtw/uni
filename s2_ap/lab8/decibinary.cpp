#include<iostream>

using namespace std;

typedef long long int ll;

ll dp[30][300007] {};
ll arr[300007] {};

// ll num(int d, int s){
//     if(dp[d][s] != -1)
//         return dp[d][s];

//     if(d == -1 and s == 0)
//         return 0;
//     else if(d == -1)
//         return 0;
    
//     ll ret = 0;
//     for (int i = 0; i <= 9 && (1 << d)*i <= s; i++)
// 		dp[d][s] += num(d-1, s-((1 << d)*i));
//     dp[d][s] = ret;
//     return ret;
// }

long long int num(int d, int s)
{
	if (d == -1 && s == 0)
		return 1;
	else if (d == -1)
		return 0;
	else if (dp[d][s] == -1)
	{
		dp[d][s] = 0;
		for (int i = 0; i <= 9 && (1 << d)*i <= s; i++)
			dp[d][s] += num(d-1, s-((1 << d)*i));
	}
	return dp[d][s];
}

int main(){
    for(int i = 0 ; i < 30; i++){
        for(int k = 0; k < 300007; k++){
            dp[i][k] = -1;
        }
    }
    for (int i = 0; i < 300005; i++)
		arr[i] = num(24, i);
	for (int i = 1; i < 300005; i++)
		arr[i] += arr[i-1];

    int q, res;

	cin >> q;
	while (q --> 0){
        ll x;
		cin >> x;
		if (x == 1)
			cout << 0 << endl;
		else{
			int lo = 0;
			int hi = 300004;
			while (lo <= hi)
			{
				int mid = (lo+hi)/2;
				if (arr[mid] >= x)
				{
					res = mid;
					hi = mid-1;
				}
				else
					lo = mid+1;
			}

			ll g = x-arr[res-1];
			ll s = res;
			ll val;
			int d;

			for (int i = -1; num(i, s) < g; i++)
				d = i;

			d++;

			while (d >= 0){
				val = 0;
				for (int i = 0; i <= 9; i++){
					if ((s - (1 << d)*i) >= 0)
						val += num(d-1, s-(1 << d)*i);
					if (val >= g){
						cout << i;
						g -= val-num(d-1, s-(1 << d)*i);
						s -= (1 << d)*i;
						break;
					}
				}
				d--;
			}
		    cout << endl;
		}
	}

    return 0;
}