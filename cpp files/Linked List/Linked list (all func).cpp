#include <iostream>
using namespace std;
typedef struct node  *lptr;

void insert(lptr &, int);       /// insert a element in last
void insertSorted(lptr &, lptr);/// insert element in sorted order
void takeInput(lptr &);         /// takes input while not -1
void print(lptr);               /// prints the list
void printReverse(lptr);        /// prints in reverse order
int getSize(lptr);              /// returns the size of list
int getMin(lptr);               /// returns minimum element
int getMax(lptr);               /// returns maximum element
int getMiddleValue(lptr);       /// returns value of middle node (odd len)
int getOddCount(lptr);          /// returns count of odd element
int getEvenCount(lptr);         /// returns count of even element
bool find(lptr, int);           /// checks whether ele is present or not
void addFront(lptr &, int);     /// add element in start of the list
void addBefore(lptr &, int, int);/// add before a certain element
void addAfter(lptr, int, int);  /// add after a certain element
void Delete(lptr &, int);       /// deletes the first occurrence of element
void DeleteLast(lptr &, int);   /// deletes the last occurrence of element
void deleteMin(lptr);           /// deletes the minimum element
void deleteMax(lptr);           /// deletes the maximum element
lptr Union(lptr, lptr);         /// returns union of two SORTED list
lptr Intersection(lptr, lptr);  /// returns intersection of two SORTED list
lptr diff(lptr, lptr);          /// returns diff of two SORTED list
lptr u_Union(lptr, lptr);       /// returns union of two UNSORTED list
lptr u_Intersection(lptr, lptr);/// returns intersection of two UNSORTED list
lptr u_diff(lptr, lptr);        /// returns diff of two SORTED list
void reverseList(lptr, lptr&);  /// reverse the list and stores in other
void reverseListInplace(lptr);  /// reverse the list in place
bool isPalindrome(lptr);        /// checks whether it is palindrome
void removeDuplicatesSorted(lptr);/// removes duplicates in SORTED list
void u_removeDuplicates(lptr);  /// removes duplicates in UNSORTED list
void DeleteAll(lptr &, int);    /// delete all occurrences of that element
void swap(lptr &, lptr &);      /// swaps the value of two node
void seprateOddEven(lptr);      /// separate odd and even value
void removeLastOccurances(lptr);/// if last occurrence of duplicates
void pushInLast(lptr);          /// push head element to last of list
void swapKth(lptr, int);        /// swap the kth element from start and end
bool isContains(lptr, lptr);    /// checks whether first list contains second or not
lptr mergeAlternate(lptr, lptr);/// merge two list with alternate node
void insertionSort(lptr);       /// insertion sort
void bubbleSort(lptr &);        /// bubble sort


struct node
{
    int data;
    struct node *next;
    node()
    {
        next=NULL;
    }
};

void insert(lptr &P, int x)
{
    lptr temp = new node;
    temp->data = x;

    if(P==NULL)
        P = temp;
    else
    {
        lptr T = P;
        while(T->next != NULL)
            T = T->next;
        T->next = temp;
    }

    return;
}

void takeInput(lptr &L)
{
    int n;
    cin>>n;
    while(n!=-1)
    {
        insert(L, n);
        cin>>n;
    }
    return;
}


void print(lptr L)
{
    while(L!=NULL)
    {
        cout<<L->data<<" ";
        L = L->next;
    }
    return;
}

void printReverse(lptr L)
{
    if(L==NULL)
        return;
    printReverse(L->next);
    cout<<L->data<<" ";
}

int getSize(lptr L)
{
    int count=0;
    while(L!=NULL)
    {
        count++;
        L = L->next;
    }
    return count;
}


int getMin(lptr L)
{
    if(L==NULL)
    {
        cout<<"List is empty"<<endl;
        return -1;
    }
    int mini = L->data;
    while(L!=NULL)
    {
        mini = min(L->data, mini);
        L = L->next;
    }
    return mini;
}


int getMax(lptr L)
{
    if(L==NULL)
    {
        cout<<"List is empty"<<endl;
        return -1;
    }
    int maxx = L->data;
    while(L!=NULL)
    {
        maxx = max(L->data, maxx);
        L = L->next;
    }
    return maxx;
}


int getMiddleValue(lptr L)
{
    int len = getSize(L);
    int count=0;
    while( count!= (len/2) )
    {
        count++;
        L = L->next;
    }
    return L->data;
}


int getOddCount(lptr L)
{
    int count=0;
    while(L!=NULL)
    {
        if((L->data)%2 == 1)
            count++;
        L = L->next;
    }
    return count;
}


int getEvenCount(lptr L)
{
    int count=0;
    while(L!=NULL)
    {
        if((L->data)%2 == 0)
            count++;
        L = L->next;
    }
    return count;
}


bool find(lptr L, int x)
{
    if(L==NULL)
        return false;
    while(L!=NULL)
    {
        if(L->data == x)
            return true;
        L = L->next;
    }
    return false;
}

void addFront(lptr &L, int k)
{
    lptr T = new node;
    T->data = k;

    if(L==NULL)
        L = T;
    else
    {
        T->next = L;
        L = T;
    }
    return;
}

void addBefore(lptr &L, int x, int y)
{
    lptr T, temp = new node;
    temp->data = x;

    if(L->data == y)
        addFront(L, x);
    else
    {
        T = L;
        while( (T->next!=NULL) && (T->next->data!=y)   )
            T = T->next;
        if(T->next!=NULL)
        {
            temp->next = T->next;
            T->next = temp;
        }
    }
    return;
}

void addAfter(lptr L, int x, int y)
{
    lptr T, temp = new node;
    temp->data = x;

    while(L!=NULL)
    {
        if(L->data == y)
        {
            temp->next = L->next;
            L->next = temp;
        }
        L = L->next;
    }
    return;
}

void Delete(lptr &L, int k)
{
    lptr temp = L;
    if(L->data == k)
    {
        L = L->next;
        delete(temp);
    }
    else
    {
        while( (temp->next!=NULL) && (temp->next->data!=k) )
            temp = temp->next;
        if(temp->next!=NULL)
        {
            lptr T = temp->next;
            temp->next = temp->next->next;
            delete(T);
        }
    }
    return;
}

void deleteMin(lptr &L)
{
    int mini = getMin(L);
    Delete(L, mini);
    return;
}

void deleteMax(lptr &L)
{
    int maxx = getMax(L);
    Delete(L, maxx);
    return;
}

lptr Union(lptr L1, lptr L2)
{
    lptr L3 = NULL, T;
    T = L3;
    while(L1!=NULL && L2!=NULL)
    {
        if(L1->data < L2->data)
        {
            if(!find(L3, L1->data))
                insert(L3, L1->data);
            L1 = L1->next;
        }
        else if(L1->data > L2->data)
        {
            if(!find(L3, L2->data))
            insert(L3, L2->data);
            L2 = L2->next;
        }
        else
        {
            if(!find(L3, L2->data))
            insert(L3, L2->data);
            L2 = L2->next;
            L1 = L1->next;
        }
    }
    while(L1!=NULL)
    {
        insert(L3, L1->data);
        L1 = L1->next;
    }
    while(L2!=NULL)
    {
        insert(L3, L2->data);
        L2 = L2->next;
    }
    return L3;
}

lptr Intersection(lptr L1, lptr L2)
{
    lptr L3 = NULL;
    while(L1!=NULL && L2!=NULL)
    {
        if(L1->data < L2->data)
            L1 = L1->next;
        else if(L1->data > L2->data)
            L2 = L2->next;
        else
        {
            insert(L3, L1->data);
            L1 = L1->next;
            L2 = L2->next;
        }
    }
    return L3;
}


lptr diff(lptr L1, lptr L2)
{
    lptr L3 = NULL;
    while(L1!=NULL && L2!=NULL)
    {
        if(L1->data < L2->data)
        {
            insert(L3, L1->data);
            L1 = L1->next;
        }
        else if(L1->data > L2->data)
            L2 = L2->next;
        else
        {
            L1 = L1->next;
            L2 = L2->next;
        }
    }
    while(L1!=NULL)
    {
        insert(L3, L1->data);
        L1 = L1->next;
    }
    return L3;
}

lptr u_Union(lptr L1, lptr L2)
{
    lptr L3 = NULL;

    while(L1!=NULL)
    {
        if(!find(L3, L1->data))
            insert(L3, L1->data);
        L1 = L1->next;
    }
    while(L2!=NULL)
    {
        if(!find(L3, L2->data))
        {
            insert(L3, L2->data);
        }
        L2 = L2->next;
    }
    return L3;
}

lptr u_Intersection(lptr L1, lptr L2)
{
    lptr L3 = NULL;
    while(L1!=NULL)
    {
        if(find(L2, L1->data))
            insert(L3, L1->data);
        L1 = L1->next;
    }
    return L3;
}

lptr u_diff(lptr L1, lptr L2)
{
    lptr L3 = NULL;

    while(L1!=NULL)
    {
        insert(L3, L1->data);
        L1 = L1->next;
    }

    while(L2!=NULL)
    {
        Delete(L3, L2->data);
        L2 = L2->next;
    }

    return L3;
}

void reverseList(lptr L, lptr &L2)
{
    if(L==NULL)
        return;
    reverseList(L->next, L2);
    insert(L2, L->data);
    return;
}

bool isPalindrome(lptr L)
{
    lptr L2 = NULL;
    reverseList(L, L2);

    while(L!=NULL)
    {
        if(L->data != L2->data)
            return false;
        L = L->next;
        L2 = L2->next;
    }
    return true;
}


void removeDuplicatesSorted(lptr L)
{
    if(L->next==NULL)
        return;

    lptr temp = NULL;
    if(L->next->data == L->data)
    {
        temp = L->next;
        L->next = L->next->next;
        delete(temp);
        removeDuplicatesSorted(L);
    }
    else
        removeDuplicatesSorted(L->next);
    return;
}


void DeleteAll(lptr &L, int x)
{
    if(L==NULL )
        return;

    while(L!=NULL && L->data == x)
        L = L->next;

    lptr T = L;
    while(T->next!=NULL)
        if(T->next->data == x)
            T->next = T->next->next;
        else
            T = T->next;

    return;
}


void u_removeDuplicates(lptr L)
{
    if(L->next==NULL)
        return;
    DeleteAll(L->next, L->data);
    u_removeDuplicates(L->next);
    return;
}

void swap(lptr &a, lptr &b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
    return;
}

void seprateOddEven(lptr L)
{
    lptr i=L, j;
    while(i!=NULL)
    {
        j = i;
        while(j->next!=NULL)
        {
            if( (j->data)%2==1 && (j->next->data)%2==0 )
                swap(j, j->next);
            j = j->next;
        }
        i = i->next;
    }
    return;
}

void DeleteLast(lptr &L, int k)
{
    if(L==NULL)
        return;
    lptr temp = L;
    if( (L->data == k) && ((!find(L->next, k)))  )
    {
        L = L->next;
        delete(temp);
    }
    else
    {
        DeleteLast(L->next, k);
    }
    return;
}

void removeLastOccurances(lptr L)
{
    lptr removedItem = NULL;
    while(L!=NULL)
    {
        if( (find(L->next, L->data)) && (!find(removedItem, L->data)) )
        {
            insert(removedItem, L->data);
            DeleteLast(L->next, L->data);
        }
        else
            L = L->next;
    }
   return;
}


void pushInLast(lptr L)
{
    if(L==NULL)
        return;

    while(L->next!=NULL)
    {
        swap(L, L->next);
        L = L->next;
    }
    return;
}


void reverseListInplace(lptr L)
{
    if(L==NULL || L->next==NULL)
        return;
    if(L->next->next==NULL)
    {
        swap(L, L->next);
        return;
    }
    reverseListInplace(L->next);
    pushInLast(L);
    return;
}

void swapKth(lptr L, int k)
{
    int len = getSize(L);
    lptr L1 = L, L2 = L;
    int cnt1=k-1, cnt2 = len-k;
    while(cnt1--)
        L1 = L1->next;
    while(cnt2--)
        L2 = L2->next;
    swap(L1, L2);
    return;
}

bool isContains(lptr L1, lptr L2)
{

    lptr i, j;
    while(L1!=NULL)
    {
        if(L2->data == L1->data)
        {
            i = L1;
            j = L2;
            while(i!=NULL && j!=NULL)
            {
                if(j->data != i->data)
                    break;
                i = i->next;
                j = j->next;
            }
            if(j==NULL)
                return true;
        }

        L1 = L1->next;
    }
    return false;
}

lptr mergeAlternate(lptr L1, lptr L2)
{
    lptr L3=NULL;
    int flag =1;
    while(L1!=NULL && L2!=NULL)
    {
        if(flag)
        {
            insert(L3, L1->data);
            L1 = L1->next;
        }
        else
        {
            insert(L3, L2->data);
            L2 = L2->next;
        }
        flag = 1 - flag;
    }
    while(L1 != NULL)
    {
        insert(L3, L1->data);
        L1 = L1->next;
    }

    while(L2 != NULL)
    {
        insert(L3, L2->data);
        L2 = L2->next;
    }

    return L3;
}

void insertionSort(lptr L)
{
    if(L==NULL || L->next==NULL)
        return;
    insertionSort(L->next);
    int temp = L->data;
    lptr cur = L, before = L;
    while(L->next!= NULL && (temp > L->next->data) )
    {
        L->data = L->next->data;
        L = L->next;
    }
    L->data = temp;
    return;
}

void bubbleSort(lptr &L)
{
    int n = getSize(L), j;
    lptr T, temp;
    for(T=L; (T->next!=NULL) && (--n); T=T->next)
    {
        for(temp=L, j=0; (temp->next!=NULL) && (j<n); temp=temp->next, j++)
        {
            if(temp->data > temp->next->data)
                swap(temp, temp->next);
        }
    }
    return;
}

void insertSorted(lptr &P, lptr x)
{
    lptr temp = new node;
    temp->data = x->data;
    if(P==NULL)
        P = temp;
    else if(P->data > temp->data)
    {
        temp->next = P;
        P = temp;
    }
    else if(P->next == NULL)
    {
        P->next = temp;
    }
    else
    {
        lptr T = P;
        while(T->next != NULL && (T->next->data < temp->data))
            T = T->next;
        if(T->next==NULL)
        {
            T->next = temp;
        }
        else
        {
            temp->next = T->next;
            T->next = temp;
        }
    }
    return;
}

int main()
{
    lptr L1 = NULL, L2 = NULL, L3=NULL;
    int k;

    takeInput(L1);
    cout<<isPalindrome(L1)<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    removeDuplicatesSorted(L1);
    print(L1);  cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    u_removeDuplicates(L1);
    print(L1); cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    removeLastOccurances(L1);
    print(L1); cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    seprateOddEven(L1);
    print(L1); cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    insertionSort(L1);
    print(L1); cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    reverseListInplace(L1);
    print(L1); cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    swapKth(L1, 3);
    print(L1); cout<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    takeInput(L2);
    cout<<isContains(L1, L2)<<endl;

    L1 = L2 = L3 = NULL;
    takeInput(L1);
    takeInput(L2);
    L3 = mergeAlternate(L1, L2);
    print(L3);

    return 0;
}


