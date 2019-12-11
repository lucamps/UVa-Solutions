#include <iostream>
#include <vector>
using namespace std;

bool incidence(const vector<vector<int>> &matrix, const int n, const int m){
    int cont = 0; //auxiliary counter

    //checking if there are two vertices with more than one edge in common
    for(int i=0; i<n-1; i++) 
        for(int i2 = i+1; i2<n;i2++){
            for(int j=0; j<m; j++){
                if(matrix[i][j] == 1 && matrix[i2][j] == 1) 
                    cont++;
                if(cont>1)
                    return false;    
            } 
            cont = 0;
        } 
        
    //checking if there is an edge that is incident to more than 2 vertices
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(matrix[j][i] > 1) //checking loops
                return false;

            cont += matrix[j][i]; //increment cont

            if(cont>2){           //cont>2 -> multiple edges
                return false;
            }
        }
        if(cont!=2){ //cont>2 -> multiple edges, cont=(1 or 0) -> irregular edge
            return false;
        }
        cont = 0;
    }
    //if none of the above conditions are accepted, then the matrix is valid
    return true; 
}

int main(){
    int numEntries, n, m;

    cin >> numEntries;

    for(int k=0; k< numEntries; k++){
        cin >> n >> m;

        //initializing the matrix with the right size
        vector<vector<int>> matrix(n, vector<int>(m)); 

        //reading the matrix
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cin >> matrix[i][j];

        //checking if it's incident to a simple undirected graph
        if(incidence(matrix,n,m))
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
} 
