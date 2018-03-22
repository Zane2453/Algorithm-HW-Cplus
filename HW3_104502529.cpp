#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

int heap[50001];
int Insert(int n,int &h_size);
int Delete(int &n,int &h_size);

int main() {
    int time,task_num,total_time=0,exe_task=0,more;
    pair <int, int> task[50000];
    cin>>time;
    while(1){
        cin>>task_num;
        //pair.first store deadline, pair.second store processing time
        for(int i=0; i<task_num; i++){
            cin >> task[i].second >> task[i].first;
            heap[i+1]=0;
        }
        sort(task, task + task_num);
        for(int i=0; i<task_num; i++){
            //total_time is time of all processing time in heap
            total_time=total_time+task[i].second;
            Insert(task[i].second, exe_task);
            if(total_time > task[i].first){
                //more is the task which has the maximal processing time
                Delete(more, exe_task);
                total_time=total_time-more;
            }
        }
        if(time>1)
            cout<<exe_task<<endl;
        else
            cout<<exe_task;
        total_time=0;
        exe_task=0;
        time--;
        if(time==0)
            break;
    }
    return 0;
}

int Insert(int n, int &h_size)
{
    int i;
    heap[i=++h_size]=n;
    while(i!=1){
        if(heap[i]<=heap[i/2])
            i=1;
        else{
            swap(heap[i],heap[i/2]);
            i/=2;
        }
    }
}

int Delete(int &n,int &h_size)
{
    int i,j;
    n=heap[1];
    heap[1]=heap[h_size--];
    i=1;
    j=2;
    while(j<=h_size){
        if(j<h_size){
            if(heap[j]<heap[j+1])
                j++;
        }
        if(heap[i]>=heap[j])
            j=h_size+1;
        else{
            swap(heap[i],heap[j]);
            i=j;
            j=2*j;
        }
    }
}
