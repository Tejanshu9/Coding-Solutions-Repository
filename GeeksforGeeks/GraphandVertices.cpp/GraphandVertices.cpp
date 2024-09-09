//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
class Solution {
  public:
  long long nCr(int n, int r)
{
    return fact(n) / (fact(r) * fact(n - r));
}
  long long fact(int n)
{
      if(n==0)
      return 1;
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}
    long long count(int n) {
           long long cou;
        // your code here
        cou=pow(2,nCr(n,2));
        return cou;
        
    }
    
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Solution ob;
        cout << ob.count(n) << "\n";
    }

    return 0;
}

// } Driver Code Ends