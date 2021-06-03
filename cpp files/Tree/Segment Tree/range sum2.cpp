#include<iostream>
using namespace std;

int BSgnt(int S[], int i, int A[], int l, int r)
{
    if(l == r)
    {
        S[i] = A[l];
        return S[i];
    }

    int mid = (l+r)/2;
    S[i] = BSgnt(S, 2*i+1, A, l, mid) + BSgnt(S, 2*i+2, A, mid+1, r);
    return S[i];
}

int getSum(int S[], int i, int sl, int sr, int ql, int qr)
{
    if(ql <= sl && qr >= sr) return S[i];
    if(ql>sr || qr<sl)  return 0;
    int mid = (sl + sr)/2;
    return getSum(S, 2*i+1, sl, mid, ql, qr) + getSum(S, 2*i+2, mid+1, sr, ql, qr) ;
}

int updateSumUtil(int S[], int pos, int val, int sl, int sr, int i )
{
    if(pos<sl || pos>sr) return S[i];

    if( sl == sr)
    {
        S[i] = val;
        return S[i];
    }
    int mid = (sl + sr)/2;
    S[i] = updateSumUtil(S, pos, val, sl, mid, 2*i+1) + updateSumUtil(S, pos, val, mid+1, sr, 2*i+2);
    return S[i];
}

void updateSum(int S[], int i, int A[], int val, int n)
{
    A[i] = val;
    updateSumUtil(S, i, val, 0, n-1, 0);
}
int main()
{
    int A[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(A)/sizeof(A[0]);
    int S[4*n + 1];
    BSgnt(S, 0, A, 0, n-1);
    cout<<getSum(S, 0, 0, n-1, 1, 3)<<endl;
    updateSum(S, 1, A, 10, n);
    cout<<getSum(S, 0, 0, n-1, 1, 3)<<endl;
    return 0;
}
