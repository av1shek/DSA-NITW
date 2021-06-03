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
    S[i] = min(BSgnt(S, 2*i+1, A, l, mid), BSgnt(S, 2*i+2, A, mid+1, r));
    return S[i];
}

int getMin(int S[], int i, int sl, int sr, int ql, int qr)
{
    if(ql <= sl && qr >= sr) return S[i];
    if(ql>sr || qr<sl)  return INT_MAX;
    int mid = (sl + sr)/2;
    return min(getMin(S, 2*i+1, sl, mid, ql, qr), getMin(S, 2*i+2, mid+1, sr, ql, qr) ) ;
}

int updateMinUtil(int S[], int pos, int val, int sl, int sr, int i )
{
    if(pos<sl || pos>sr) return S[i];

    if( sl == sr)
    {
        S[i] = val;
        return S[i];
    }
    int mid = (sl + sr)/2;
    S[i] = min(updateMinUtil(S, pos, val, sl, mid, 2*i+1), updateMinUtil(S, pos, val, mid+1, sr, 2*i+2) );
    return S[i];
}

void updateMin(int S[], int i, int A[], int val, int n)
{
    A[i] = val;
    updateMinUtil(S, i, val, 0, n-1, 0);
}
int main()
{
    int A[] = {1, 3, 5, 9, 7, 11};
    int n = sizeof(A)/sizeof(A[0]);
    int S[4*n + 1];
    BSgnt(S, 0, A, 0, n-1);
    cout<<getMin(S, 0, 0, n-1, 3, 5)<<endl;
    updateMin(S, 5, A, -10, n);
    cout<<getMin(S, 0, 0, n-1, 3, 5)<<endl;
    return 0;
}
