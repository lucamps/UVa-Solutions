#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <algorithm>
#include <string.h>
using namespace std;

void print(list<int> degrees){
    for (list<int>::iterator it=degrees.begin(); it != degrees.end(); it++){
        cout << *it << ' ';
    }
    cout << endl << endl;
}

int main(){
    int nVer;
    int aux;
    
    while(cin >> nVer){
        if(nVer == 0)
            break;

        list<int> degrees;

        for(int i=0; i<nVer; i++){
            cin >> aux;
            degrees.push_back(aux);
        }

        bool possible = true;
       
        while(!degrees.empty()){
            degrees.sort();
            degrees.reverse();
            
            if(*degrees.begin() == 0)
                break;
            aux = *degrees.begin();
            
            degrees.pop_front();
            
            if (aux>degrees.size()){
                possible = false;
                break;
            }
            
            nVer--;
            int j=0;
            
            for (list<int>::iterator it=degrees.begin(); it != degrees.end(), j< aux; ++it, j++){
                (*it)--;
                if(*it<0){
                    possible = false;
                    break;
                }
            }
            if(!possible)
                break;
        }
        if(possible)
            cout << "Possible\n";
        else 
            cout << "Not possible\n";
    }
    
    return 0;
}