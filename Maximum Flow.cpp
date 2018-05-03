///Maximum Flow(FordFulkerson Algorithm)
/* Accepted
   Indrojit Mondal
   Dept Of CSE, University Of Barisal
   Time Complexity O(V^2*E)
   */

#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
int StrCount=0;
string StringHome[100];

int G[100][100];
int R[100][100];
bool color[100];
int d[100];
int p[100];
int Vertex,Edge;
int CF[100][100];
vector< pair<int,int> > Pair;
queue<int>Path;
string Source;  string Dsn;
#define Inf 2147483647
int Search_Index(string s)
{
    for(int I=1; I<=StrCount; I++)
    {
        if(StringHome[I]==s)
        {
            return I;
        }
    }
    StrCount = StrCount +1;
    StringHome[StrCount] = s;
    return StrCount;
}

void BFS(int s)
{
     queue<int>q;
     color[s] =0;
     d[s]=0;
     p[s]=0;
     q.push(s);
    while(!q.empty()){

        int U = q.front();
        q.pop();

        for(int I=1; I<=Vertex; I++)
        {

           if((G[U][I]==1 && color[I]==0 && CF[U][I]>0) || (R[U][I]==1 && color[I]==0 && CF[U][I]>0)){

               color[I]=1;
               d[I] = d[U] + 1;
               p[I] =U;
               q.push(I);

           }
        }
       color[U]=2;
      }


}
int PathCk=1;
void PathPrint(int X, int Y)
{
    if(X==Y)
    {

          Path.push(X);
    }
    else if(p[Y]==0){ PathCk =0;
            //cout<<"No Path From Source To Destination "<<endl;
             }
    else{

       PathPrint(X,p[Y]);
        Path.push(Y);

    }
}

 void PathExcess()
 {
     if(PathCk==1){
    int X=Path.front();
    Path.pop();
    int  Y;
    ///Path Print
    while(!Path.empty())
    {
       Y=Path.front();
       Path.pop();
       Pair.push_back(make_pair(X,Y));
       X=Y;
    }
     }
 }
void ForFulkerson()
{
    int Total_Flow=0;
     BFS(Search_Index(Source));
     PathPrint(Search_Index(Source),Search_Index(Dsn));
     PathExcess();



      while(PathCk==1){


            int min_res_cap= 21567;
            int U,V;

        for(int I=0; I<Pair.size(); I++)
        {
            U=Pair[I].first;
            V=Pair[I].second;
            min_res_cap = min(min_res_cap,CF[U][V]);
        }


        for(int I=0; I<Pair.size(); I++)
        {
            U=Pair[I].first;
            V=Pair[I].second;
            CF[U][V]=CF[U][V]-min_res_cap;
            CF[V][U]=CF[V][U]+min_res_cap;
            if(CF[U][V]==0)  G[U][V] =0;
            if(CF[V][U]==0)  G[V][U]=0;

        }

        Total_Flow+=min_res_cap;
        Pair.clear();
    for(int I=1; I<=Vertex; I++)
    {
       color[I]=0;
       d[I]=Inf;
       p[I]=0;
    }

     BFS(Search_Index(Source));
     PathPrint(Search_Index(Source),Search_Index(Dsn));
     PathExcess();
      }
      cout<<"Maximum Flow = "<<Total_Flow<<endl;

}

int main()
{

    cin>>Vertex>>Edge;
    string s1,s2;
    int Node1, Node2,Cost;
    for(int I=1; I<=Edge; I++)
    {
        cin>>s1>>s2>>Cost;
        Node1 = Search_Index(s1);
        Node2 = Search_Index(s2);

        G[Node1][Node2]=1;
        R[Node2][Node1]=1;

        CF[Node1][Node2]=Cost;
        CF[Node2][Node1]=0;

    }
    for(int I=1; I<=Vertex; I++)
    {
       color[I]=0;
       d[I]=Inf;
       p[I]=0;
    }

    cout<<"Enter Source : ";
    cin>>Source;
    cout<<"Enter Destination : ";
    cin>>Dsn;
    //int MaxFlow =ForFulkerson();

   ForFulkerson();
   //cout<<"MaxFlow = "<<MaxFlow<<endl;

    return 0;
}



