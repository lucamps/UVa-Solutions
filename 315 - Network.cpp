#include <iostream>
#include <string>
#include <sstream> 
#include <algorithm>
#include <vector>
using namespace std;

//Tarjan function used by my teacher in the Graphs discipline, 
//which was adapted from a book I don't remember the name
void tarjan(int u, const vector<vector<int> > &adj, vector<int> &dfsParent, vector<int> &dfsNum,
					 vector<int> &dfsLow, vector<bool> &isArticulation,vector<pair<int,int> > &bridges, 
						int &dfsCount, int &rootChildren, int dfsRoot) {
	dfsLow[u] = dfsNum[u] = ++dfsCount; 
	for(int v:adj[u]) {
		if (dfsNum[v] == 0) { 
				dfsParent[v] = u; 
			if (u == dfsRoot) 
				rootChildren++; 

			tarjan(v,adj,dfsParent,dfsNum,dfsLow,isArticulation,bridges,dfsCount,rootChildren,dfsRoot);

			if (dfsLow[v] >= dfsNum[u]) 
				isArticulation[u] = true; 
			if (dfsLow[v] > dfsNum[u]) 
				bridges.push_back(make_pair(u,v));
			dfsLow[u] = min(dfsLow[u], dfsLow[v]); 
		}
		else if (v != dfsParent[u]) 
			dfsLow[u] = min(dfsLow[u], dfsNum[v]); 
	}
}

void tarjan(const vector<vector<int> > &adj, 
						vector<bool> &isArticulation,vector<pair<int,int> > &bridges) {
	int nv = adj.size();
	isArticulation = vector<bool>(nv,false);
	bridges.resize(0);

	vector<int> dfsParent(nv,-1);
	vector<int> dfsLow(nv,0);
	vector<int> dfsNum(nv,0);	
	int dfsCount = 0;

	//for multiple CCs...
	for(int i=0;i<nv;i++) {
		if(dfsNum[i]==0) {
			int rootChildren = 0; 
			tarjan(i,adj,dfsParent,dfsNum,dfsLow,isArticulation,bridges,dfsCount,rootChildren,i);
			isArticulation[i] = rootChildren>1;
		}
	}
}


int main(){
    int n; //no_of_places 
    string aux;

    int v = 0, u = 0;

    while(cin >> n){
        if(n==0) break;
        vector<vector<int> > adj(n); //adjacency list
        cin >> v;
        while(v != 0){
            getline(cin,aux);
            for(int i=0;i<aux.size();i++){
                if (aux[i]>=48 && aux[i]<=57){ //checking if it's a number
                    u = aux[i]-48;
                    //if u occupies more than 1 char, we have to 'concatenate' u with the next aux position
                    while(aux[i+1] != ' ' && i+1<aux.size()){ 
                        i++;
                        u *= 10;
                        u += aux[i]-48; 
                    }
                    adj[v-1].push_back(u-1);
                    adj[u-1].push_back(v-1);
                }
            }
            cin >> v;
        }
        vector<bool> joints;
        vector< pair<int,int> > bridges;
		tarjan(adj,joints,bridges);
        
        int numjoints = 0;
        for(int i=0;i<joints.size();i++)
            if(joints[i])
               numjoints++;

        cout << numjoints << "\n";
    }
    return 0;
}