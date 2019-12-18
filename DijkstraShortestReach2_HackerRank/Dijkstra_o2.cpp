/*rathoreanirudh*/
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<queue>
#define lli long long int
using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vi;
struct comp {
    bool operator() (const ii &a, const ii &b) {
        return a.second > b.second;
    }
};
int main()
{
    int test;
    cin>>test;
    while(test--)
    {
        int v,k,a,b,c,d,e,w,temp1,temp2;
        cin>>v>>k;
        vi arr[v];
        for(int i=0; i<k; i++)
        {
            cin>>temp1>>temp2>>c;
            arr[temp1-1].push_back(make_pair((temp2-1),c));
            arr[temp2-1].push_back(make_pair((temp1-1),c));
        }
        cin>>a;
        a--;
        int dist[v],temp,visited[v];
        fill(visited,visited+v,0);
        fill(dist, dist + v, 1000000007);
        dist[a]=0;
        priority_queue< ii , vector<ii> , comp > myqueue;
        myqueue.push(make_pair(a,0));
        while(!myqueue.empty())
        {
            d=myqueue.top().first;
            e=myqueue.top().second;
            myqueue.pop();
            if(visited[d]==0)
            {
                for(int i=0;i<arr[d].size();i++)
                {
                    e=arr[d][i].first;
                    w=arr[d][i].second;
                    if(visited[e]==0)
                    {
                        dist[e]=min(dist[e],dist[d]+w);
                        myqueue.push(make_pair(e,dist[e]));
                    }
                }
                visited[d]=1;
            }
        }
        
        for(int i=0;i<v;i++)
        {
            if(dist[i]!=0)
            {
                if(dist[i]==1000000007)
                    cout<<-1<<" ";
                else
                    cout<<dist[i]<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}