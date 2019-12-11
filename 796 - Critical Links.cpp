#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

//Tarjan function used by my teacher in the Graphs discipline, 
//which was adapted from a book I don't remember the name
void tarjan(int u, const vector<vector<int> > &adj, vector<int> &dfsParent, vector<int> &dfsNum,
					 vector<int> &dfsLow,vector<pair<int,int> > &bridges, 
						int &dfsCount, int &rootChildren, int dfsRoot) {
	dfsLow[u] = dfsNum[u] = dfsCount++; 
	for(int v:adj[u]) {
		if (dfsNum[v] == 0) { 
				dfsParent[v] = u; 
			if (u == dfsRoot) 
				rootChildren++; 

			tarjan(v,adj,dfsParent,dfsNum,dfsLow,bridges,dfsCount,rootChildren,dfsRoot);

			if (dfsLow[v] > dfsNum[u]) {
				if(u<v)
                    bridges.push_back(make_pair(u,v));
                else
                    bridges.push_back(make_pair(v,u));   
            }
            
			dfsLow[u] = min(dfsLow[u], dfsLow[v]); 
		}
		else if (v != dfsParent[u]) 
			dfsLow[u] = min(dfsLow[u], dfsNum[v]); 
	}
}

void tarjan(const vector<vector<int> > &adj, vector<pair<int,int> > &bridges) {
	int nv = adj.size();
	
	bridges.resize(0);

	vector<int> dfsParent(nv,-1);
	vector<int> dfsLow(nv,0);
	vector<int> dfsNum(nv,0);	
	int dfsCount = 0;

	//for multiple CCs...
	for(int i=0;i<nv;i++) {
		if(dfsNum[i]==0) {
			int rootChildren = 0;  
			tarjan(i,adj,dfsParent,dfsNum,dfsLow,bridges,dfsCount,rootChildren,i);
		}
	}
}

int main(){
    int n; //no_of_servers 
    string aux; 

    while(cin >> n){
        vector<vector<int> > adj(n); //adjacency list
        for(int i=0; i<n; i++){
            int u, v; //vertices
            int numE; //number of edges incident to u
            
            cin >> u;
            getline(cin,aux, '(');
            cin >> numE;
            getline(cin,aux, ')');

            for(int j=0; j< numE; j++){ //filling adjacency matrix
                cin >> v;
                adj[u].push_back(v);
            }  
        }

		vector< pair<int,int> > bridges;
		tarjan(adj,bridges);
        sort(bridges.begin(),bridges.end());

        cout << bridges.size() << " critical links\n";
        for(auto a:bridges){
            cout << a.first << " - " << a.second << "\n";
        }
        cout << endl;
    }
 
    return 0;
}