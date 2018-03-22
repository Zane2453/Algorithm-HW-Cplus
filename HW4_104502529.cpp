#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

//use disjoint set
int parent [10000];
int Union (int,int);
int Find (int);

int main() {
    int v_num,e_num,t1,t2,count=0;
    int total[20];
    for(int i=0;i<20;i++)
        total[i]=0;
    cin>>v_num>>e_num;
    while(v_num!=0&&e_num!=0){
        //pair'first store edge's weight
        //pair's second's first store edge's source
        //pair's second's second store edge's destination
        pair < int,pair<int,int> > edge[e_num];
        for(int i=0;i<e_num;i++)
            cin>>edge[i].second.first>>edge[i].second.second>>edge[i].first;
        //sorting according to its edge's weight
        sort(edge,edge+e_num);
        for(int i=0;i<v_num;i++)
            parent[i]=-1;
        for(int i=0;i<e_num;i++){
            t1=Find(edge[i].second.first);
            t2=Find(edge[i].second.second);
            if(t1!=t2){
                total[count]=total[count]+edge[i].first;
                Union(t1,t2);
            }
        }
        cin>>v_num>>e_num;
        if(v_num!=0&&e_num!=0)
            count++;
    }
    for(int i=0;i<=count;i++){
        if(i!=count)
            cout<<total[i]<<endl;
        else
            cout<<total[i];
    }
    return 0;
}

int Union(int X, int Y){
    if(parent[X]<=parent[Y]){
        parent[X]=parent[X]+parent[Y];
        parent[Y]=X;
    }
    else{
        parent[Y]=parent[Y]+parent[X];
        parent[X]=Y;
    }
}

int Find(int X){
    int i,j,k;
    i=X;
    while(parent[i]>=0){
        k=parent[i];
        i=k;
    }
    j=X;
    while(parent[j]>=0){
        k=parent[j];
        parent[j]=i;
        j=k;
    }
    return i;
}
