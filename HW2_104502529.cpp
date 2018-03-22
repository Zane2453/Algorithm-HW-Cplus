#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

string LCS(string const& X, string const& Y, int m, int n);

int main() {
    int time,m,n;
    cin>>time;
    while(time--){
        string X,Y;
        cin>>X>>Y;
        m=X.length();
        n=Y.length();

        cout<<LCS(X,Y,m,n);

        if(time==0)
            continue;
        else
            cout<<endl;
    }
    return 0;
}

string LCS(string const& X, string const& Y, int m, int n){
    //if Y's length is 0
    if(n==0)
        return "";
    //if X's length is 1
    else if(m==1){
        for(int i=0;i<n;i++){
            if(Y[i]==X[0])
                return X;
        }
        return "";
    }
    //if Y's length is 1
    else if(n==1){
        for(int i=0;i<m;i++){
            if(X[i]==Y[0])
                return Y;
        }
        return "";
    }
    //if X's and Y's length is larger than 1
    else {
        int mid,k=0,LCS_leng;
        mid=m/2;
        LCS_leng=-10000;

        string X_reverse=X.substr(mid,m-mid);
        string Y_reverse=Y;

        int* line_1=new int[n+1];
        int* line_2=new int[n+2];
        int* line_3=new int[n+1];

        reverse(X_reverse.begin(), X_reverse.end());
        reverse(Y_reverse.begin(), Y_reverse.end());

        memset(line_1, 0, sizeof(int)*(n+1));
        memset(line_2, 0, sizeof(int)*(n+2));
        memset(line_3, 0, sizeof(int)*(n+1));

        //calculate the LCS's length in upper part
        for(int i=1;i<=mid;i++){
            for(int j=0;j<=n;j++)
                line_3[j]=line_1[j];
            for(int j=1;j<=n;j++){
                if(X[i-1]==Y[j-1])
                    line_1[j]=line_3[j-1]+1;
                else
                    line_1[j]=max(line_1[j-1],line_3[j]);
            }
        }

        //calculate the LCS's length in lower part
        for(int i=1;i<=X_reverse.length();i++){
            for(int j=0;j<=n;j++)
                line_3[j]=line_2[j];
            for(int j=1;j<=n;j++){
                if(X_reverse[i-1]==Y_reverse[j-1])
                    line_2[j]=line_3[j-1]+1;
                else
                    line_2[j]=max(line_2[j-1],line_3[j]);
            }
        }

        delete [] line_3;

        reverse(line_2,line_2+(n+1));
        for(int i=n;i>0;i--)
            line_2[i]=line_2[i-1];

        for(int i=n;i>=0;i--){
            if(LCS_leng<line_1[i]+line_2[i+1]){
                LCS_leng=line_1[i]+line_2[i+1];
                //k is the point to cut
                k=i;
            }
        }

        delete [] line_1;
        delete [] line_2;

        return LCS((X.substr(0,mid)),(Y.substr(0,k)),mid,k) + LCS((X.substr(mid,m-mid)),(Y.substr(k,n-k)),m-mid,n-k);
    }
}
