#include<iostream>
#include<stdlib.h>
#include<list>
#include<stack>
using namespace std;
class graph{
	int v;
	list<int> *adj;
	void fillOrder(int s , bool visited[] , stack<int> &stack);
	void dfs(int s,bool visited[]);
	graph transpose();
	public: graph(int v);
			void printSCC();
			void addEdge(int s , int d);
};
graph::graph(int v){
	this->v = v;
	adj = new list<int>[v];
}
void graph::addEdge(int s , int d){
	adj[s].push_back(d);
}
graph graph:: transpose(){
	graph g(v);
	for(int s = 0;s<v;s++){
		list<int>::iterator i;
		for(i = adj[s].begin();i != adj[s].end();++i)
			g.adj[*i].push_back(s);
	}
	return g;
}
void graph::printSCC(){
	bool *visited = new bool[v];
	for(int i = 0;i<v;i++)
		visited[i] = false;
	stack<int> stack;
	for(int i = 0;i<v;i++)
		if(!visited[i])
			fillOrder(i,visited,stack);
	graph gr = transpose();
	for(int i = 0;i<v;i++)
		visited[i] = false;
	while(!stack.empty()){
		int s = stack.top();
		stack.pop();
		if(!visited[s]){
			gr.dfs(s,visited);
			cout<<endl;
		}
	}
}
void graph::dfs(int s,bool visited[]){
	visited[s] = true;
	cout<<s<<" ";
	list<int>::iterator i;
	for(i = adj[s].begin();i != adj[s].end();++i)
		if(!visited[*i])
			dfs(*i,visited);
}
void graph::fillOrder(int s,bool visited[],stack<int>&stack){
	visited[s] = true;
	list<int>::iterator i;
	for(i = adj[s].begin();i != adj[s].end();++i)
		if(!visited[*i])
			fillOrder(*i , visited , stack);
	stack.push(s);
}
int main(){
	int n , from , to;
	char ch;
	cin>>n;
	graph g(n);
	do{
		cin>>from>>to;
		g.addEdge(from,to);
		cout<<"Y or N ? ";
		cin>>ch;
	}while(ch == 'y' || ch == 'Y');
	cout<<"The strongly connected components are ...\n";
	g.printSCC();
	return 0;
}
