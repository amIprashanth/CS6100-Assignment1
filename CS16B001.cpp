#include<iostream>
#include<vector>
#include<list>
#include<set>

using namespace std;

class tree{
  public:
  	int N;
  	vector<vector<int>> adj;
	vector<int> height;
	vector<int> indSize;
	vector<int> itself;
	vector<int> next1,next2;
	vector<int> visited;
	
	tree(int n){
		N=n;
		for(int i=0;i<N;i++){
			vector<int> v;
			adj.push_back(v);
			height.push_back(0);
			next1.push_back(-1);
			indSize.push_back(0);
			next2.push_back(-1);
			visited.push_back(0);
			itself.push_back(0);
		}
	
	}
	
	void setHeights(int u,int v){
		int max1=-1,max2=-1,nxt1=-1,nxt2=-1;
		
		for(int i=0;i<adj[v-1].size() ;i++){
			if(adj[v-1][i]!=u) setHeights(v,adj[v-1][i]);
		}
		for(int i=0;i<adj[v-1].size();i++){
			if(adj[v-1][i]!=u){
				if(height[adj[v-1][i]-1]>=max1){
					max2=max1;
					nxt2=nxt1;
					max1=height[adj[v-1][i]-1];
					nxt1=adj[v-1][i];
					
				}else if(height[adj[v-1][i]-1]>max2){
					max2=height[adj[v-1][i]-1];
					nxt2=adj[v-1][i];
				}
			}
		}
		height[v-1]=max1+1;
		next1[v-1]=nxt1;
		next2[v-1]=nxt2;
	
	}
	
	vector<int> longPath(){
		setHeights(1,1);
		int max=0,start=1;
		for(int i=0;i<N;i++){
			int l=1;
			if(next2[i]!=-1) 
				l+=height[next1[i]-1]+height[next2[i]-1];
			else if(next1[i]!=-1)
				l+=height[next1[i]-1];
			if(l>max) {
				max=l;
				start=i+1;
			}
		}
		int store=start;
		//cout<<start<<endl;
		vector<int> v;
		v.push_back(start);
		while(next1[start-1]!=-1){
			v.push_back(next1[start-1]);
			start=next1[start-1];
		}
		vector<int> v1=v;
		v.clear();
		for(int i=0;i<v1.size();i++){
			v.push_back(v1[v1.size()-i-1]);
		}
		if(next2[store-1]!=-1){
			v.push_back(next2[store-1]);
			store=next2[store-1];
		}
		while(next1[start-1]!=-1){
			v.push_back(next1[start-1]);
			start=next1[start-1];
		}
		return v;
	}
	
	void ind(int u,int v){
		int x=1,y=0;
		for(int i=0;i<adj[v-1].size();i++){
			if(adj[v-1][i]!=u) ind(v,adj[v-1][i]);
		}
		
		for(int i=0;i<adj[v-1].size();i++){
			if(adj[v-1][i]!=u) y+=indSize[adj[v-1][i]-1];
		}
		
		for(int i=0;i<adj[v-1].size();i++){
			if(adj[v-1][i]!=u){
				for(int j=0;j<adj[adj[v-1][i]-1].size();j++){
					x+=indSize[adj[adj[v-1][i]-1][j]-1];
				}
			
			}
		}
		
		indSize[v-1]=max(x,y);
		if(x>y) itself[v-1]=1; else itself[v-1]=0;
	
	}
	
	int indSet(){
		ind(1,1);
		return indSize[0];
	
	}
	void vertexCover(){
		/* itself[] array can be used directly to find the vertex cover*/
	}
};


int main(){
	int N;
	cout<<"Enter N, the number of vertices in the tree: ";
	cin >> N;
	tree T(N);
	cout<<"Enter N-1 edges as \"u v\": "<<endl;
	for(int i=0;i<N-1;i++){
		int u,v;
		cin >> u >> v;
		T.adj[u-1].push_back(v);
		T.adj[v-1].push_back(u);
	}
	vector<int> v=T.longPath();
	
	cout<<"Longest path: ";
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
	
	T.indSet();
	cout<<"Max. independent set: ";
	for(int i=0;i<N;i++){
		if(T.itself[i]==1) cout<<i+1<<" ";
	}
	cout<<endl;
	
	cout<<"Min. vertex cover: ";
	for(int i=0;i<N;i++){
		if(T.itself[i]==0) cout<<i+1<<" ";
	}
	cout<<endl;
	
	cout<<"Min. dominating set: <code not written>"<<endl;





}
