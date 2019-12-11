#include <iostream>
#include <vector>
#include <string.h>
#include <list>
using namespace std;

int numAcorns(list<char> &vertices,vector <pair<char,char>> &edges, int numEdges) {
    int contA = 0;
    for(int i=0; i< numEdges; i++){
        vertices.remove(edges[i].first);
        vertices.remove(edges[i].second);
    }
    for (list<char>::iterator it = vertices.begin(); it != vertices.end(); it++){
        if(*it >= 'A' && *it <= 'Z')
            contA++;
    }
    return contA;
}
void calculate(list<char> &v,vector <pair<char,char>> &e, int numE, int numV, int &contT, int &contA){
    contT=0;
    contA=0;
    int CC = numV - numE; //number of connected components
    contA = numAcorns(v,e,numE);
    
    //As there are only trees and acorns in the problem, so non-acorn CCs are trees
    contT = CC-contA; 
}

int main(){
    int numEntries, i=0, j=0;
    cin >> numEntries;
    char aux = '*';  

    //vertices to store each input data
    vector<list<char>> vertices(numEntries); //list of vertices
    vector <vector<pair<char,char>>> edges(numEntries, vector<pair<char,char>> (1)); //edges(pair of vertices)
    vector<int> numEdges(numEntries); //number of edges
    vector<int> numVertices(numEntries); //number of vertices

    //******** Reading **********//
    int cont = 0;
    cin.ignore();
   
    for(i=0; i< numEntries; i++){
        while(cin >> aux){ // '*'or '(' or 1º vertex of an edge
            if(aux == '*'){
                numEdges[i] = j;
                j=0;
                break;
            }
            if(aux != '\n'){
                edges[i].resize(1+j);

                if(aux < 'A' || aux > 'Z')
                    cin >> aux; //1º element

                edges[i][j].first = aux;
                cin >> aux; // comma
                cin >> aux; //2º element

                edges[i][j].second = aux;
                cin >> aux; // )

                j++;                
            }
        }
        while(cin >> aux){
            if(aux != '*'){
                if(aux == '(')
                    break;
                string vLine; // line of vertices

                numVertices[i]++;
                vertices[i].resize(numVertices[i]);
                vertices[i].push_back(aux);
                getline(cin,vLine, '\n');
                for(int w=1; w<vLine.length();w+=2){
                    numVertices[i]++;
                    vertices[i].resize(numVertices[i]);
                    vertices[i].push_back(vLine[w]);          
                }
                break;
            }
        }
    }
    //***************************//

    int contT, contA; //counters for 'trees' and 'acorns'
   
    for(i=0;i<numEntries;i++){
        calculate(vertices[i],edges[i], numEdges[i],numVertices[i],contT, contA); 
        cout << "There are " << contT << " tree(s) and " << contA << " acorn(s).\n";
    }
        cout << flush;

    return 0;
}