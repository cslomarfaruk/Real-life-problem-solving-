// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;
/* * * * * * * * * * * * * * 
 *                         *
 *    !(I hate Coding)     *
 *                         *
 * * * * * * * * * * * * * */
#define int long long
#define endl "\n"

pair<int,int> fun(int a[],int i,int n){
   pair<int,int> ans;
   if(i==n-1){
      ans={1,a[i]};
      return ans;
   }
   ans=fun(a,i+1,n);
   // cout << ans.first << ' ' << ans.second << endl;
   ans.first=ans.second*a[i]+ans.first;
   
   if(i)swap(ans.first,ans.second);
   return (ans);
}

void solve(){
   int i=0,n; cin >> n;
   int a[n]; for(int i=0; i<n; i++)cin >> a[i];
   pair<int,int>ans=fun(a,i,n);
   cout << ans.first << " / " << ans.second << endl;
}

int32_t main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int tc=1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
       //cout << "Case " << t << ": ";
      solve();
    }
    return 0;
}
