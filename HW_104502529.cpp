#include<iostream>
using namespace std;

void Merge(int* A,int* B,int *R,int *In,int p,int q,int r,int check);
void MergeSort(int* A,int* B,int *R,int *In,int p,int r,int check);
void Insertion(int* A,int* B,int *R,int *In,int p,int r,int check);


int main()
{
    int num,x[100000],y[100000],Rank[100000],index[100000];
    cin>>num;
    //do the loop until input num is 0
    while(1){
        if(num==0)
            break;
        for(int i=1;i<=num;i++){
            cin>>x[i]>>y[i];
            Rank[i]=0;
            index[i]=i;
        }
        //merge sort with x
        MergeSort(x,y,Rank,index,1,num,0);
        //merge sort with y
        //if we merge with y, check will be 1
        MergeSort(y,x,Rank,index,1,num,1);
        //merge sort with index
        MergeSort(index,x,y,Rank,1,num,0);
        for(int i=1;i<=num;i++){
            cout<<Rank[i]<<" ";
        }
        cout<<endl;
        cin>>num;
    }
}

void Merge(int* A,int* B,int *R,int *In,int p,int q,int r,int check) {
    int n1=q-p+1,n2=r-q;
    //built 8 array to store lest and right array of array A,B,R and In
    int L1[n1],L2[n1],L3[n1],L4[n1],
        R1[n2],R2[n2],R3[n2],R4[n2];
    for(int i=0; i<n1; i++){
            L1[i]=A[p+i];
            L2[i]=B[p+i];
            L3[i]=R[p+i];
            L4[i]=In[p+i];
    }
    for(int j=0; j<n2; j++){
            R1[j]=A[q+1+j];
            R2[j]=B[q+1+j];
            R3[j]=R[q+1+j];
            R4[j]=In[q+1+j];
    }
    int i=0,j=0,n=0;
    //if left and right array not in the end
    while(i!=n1 && j!=n2) {
        //the element in L1 is bigger than R1
        if(L1[i]>R1[j]) {
            A[p+n]=R1[j];
            B[p+n]=R2[j];
            In[p+n]=R4[j];
            if(check==1)
                R3[j]+=i;
            R[p+n]=R3[j];
            j++;
        }
        //the element in L1 is smaller than R1
        else {
            A[p+n]=L1[i];
            B[p+n]=L2[i];
            In[p+n]=L4[i];
            //to amend the rank when x is the same
            if(check==1&&R2[j-1]==L2[i])
                L3[i]+=j;
            R[p+n]=L3[i];
            //to amend the rank when x and y is the same
            if(check==1&&L1[i]==R1[j]&&L2[i]==R2[j])
                R[p+n]++;
            i++;
        }
        n++;
    }
    //the element in L1 is in the end
    while(j!=n2) {
        A[p+n]=R1[j];
        B[p+n]=R2[j];
        In[p+n]=R4[j];
        if(check==1)
            R3[j]+=i;
        R[p+n]=R3[j];
        j++;
        n++;
    }
    //the element in R1 is in the end
    while(i!=n1) {
        A[p+n]=L1[i];
        B[p+n]=L2[i];
        In[p+n]=L4[i];
        //to amend the rank when x is the same
        if(check==1&&R2[j-1]==L2[i])
            L3[i]+=n2;
        R[p+n]=L3[i];
        i++;
        n++;
    }
}
void MergeSort(int* A,int* B,int *R,int *In,int p,int r,int check) {
    //the optimal threshold is t=30
    int t=30;
    //if the length of array is bigger than threshold, do merge sort
    if(r-p>t) {
        int q;
        q=(p+r)/2;
        MergeSort(A,B,R,In,p,q,check);
        MergeSort(A,B,R,In,q+1,r,check);
        Merge(A,B,R,In,p,q,r,check);
    }
    //if the length of array is smaller than threshold, do insertion sort
    else{
        Insertion(A,B,R,In,p,r,check);
    }
}

void Insertion(int* A,int* B,int *R,int *In,int p,int r,int check){
    int temp1=0,temp2=0,temp3=0,temp4=0,j=0;
    for(int i=p;i<r+1;i++){
        temp1=A[i];
        temp2=B[i];
        temp3=R[i];
        temp4=In[i];
        j=i-1;
        //do the loop until element in A is located in correct place
        while(j>p-1&&temp1<A[j]){
            if(check==1&&temp2==B[j])
                R[j]++;
            A[j+1]=A[j];
            B[j+1]=B[j];
            R[j+1]=R[j];
            In[j+1]=In[j];
            j--;
        }
        A[j+1]=temp1;
        B[j+1]=temp2;
        R[j+1]=temp3;
        //the rank is decided by the element in the left side
        if(check==1)
            R[j+1]=j-p+1;
        In[j+1]=temp4;
    }
}
