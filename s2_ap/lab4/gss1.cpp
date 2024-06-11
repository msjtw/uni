#include <iostream>

using namespace std;

typedef long long int ll;

ll oo = __INT64_MAX__;

struct node{
    ll ssum = 0;
    ll prfx = 0;
    ll sufx = 0;
    ll tsum = 0;
};

node merge(node &l, node &r){
    node ret;
    ret.prfx = max(l.prfx, l.tsum+r.prfx);
    ret.sufx = max(r.sufx, r.tsum+l.sufx);
    ret.tsum = l.tsum + r.tsum;
    ret.ssum = max(max(l.ssum, r.ssum), l.sufx+r.prfx);

    return ret;
}

const int BASE = 1<<16;

int arr[BASE];
node arr2[BASE<<2];


void init(int index,int l,int r)
{
    if(l==r){
            arr2[index] = {arr[l], arr[l], arr[l], arr[l]};
            return;
        }
    else{
        int mid=(l+((r-l)/2));
        init(2*index,l,mid);
        init(2*index+1,mid+1,r);
        arr2[index] = merge(arr2[2*index],arr2[2*index+1]);
    }

}

void query(node& result,int l,int r,int u,int v,int index)
    {
        if(u==l && v==r)
            {
                result=arr2[index];
                return;
            }
        else
        {
           int mid=(l+((r-l)/2));
           if(mid>=v)
                query(result,l,mid,u,v,2*index);
            else if(mid<u)
                query(result,mid+1,r,u,v,2*index+1);
            else
            {
                node left,right;
                query(left,l,mid,u,mid,2*index);
                query(right,mid+1,r,mid+1,v,2*index+1);
                result = merge(left,right);
 
          	} 
         }
    } 

int main(){
    int n, nn;
    cin >> n;
    for(int i = 0 ; i < n; i++){
        cin >> arr[i];
    }
    init(1,0,n-1);
    int a, b;
    node ans;
    cin >> nn;
    while(nn --> 0){
        cin >> a >> b;
        query(ans,0,n-1,a-1,b-1,1);
        cout << ans.ssum << endl;
    }
}