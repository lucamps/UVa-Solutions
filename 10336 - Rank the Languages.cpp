#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string.h>
using namespace std;

void paint(char letter, vector<string> &m, int numL, int numC, int l, int c){
    if (l<0 || c<0 || c>=numC || l>=numL || m[l][c]!=letter )
        return;
    else{
        m[l][c] = '#';
        paint(letter,m,numL,numC,l+1,c); //down 
        paint(letter,m,numL,numC,l,c+1); //right  
        paint(letter,m,numL,numC,l-1,c); //up
        paint(letter,m,numL,numC,l,c-1); //left
    }
    
}
void search(char letter,vector<string> &m,int numL, int numC,int &i,int &j){
    for(int l=0; l<numL; l++){
        for(int c=0; c<numC; c++){
            if(m[l][c] == letter){
                i = l;
                j = c;
                return;
            }
        }
    }
    i = -1;
    j = -1;
}
bool belongs(char letter, vector<pair<int,char>> difLetters, int dlSize){
    for(int c=0; c<dlSize-1; c++){
        if(letter == difLetters[c].second)
            return true;
    }
    return false;
}

bool auxSort (pair<int,char>i,pair<int,char>j) { //function to use as a parameter for the sort function
    return (i.first>j.first || (!(j.first>i.first) && i.second<j.second)); 
}

int main(){
    int entries;
    int numLin, numCol;

    //reading
    cin >> entries;
    for(int i=0; i< entries; i++){
        cin >> numLin >> numCol;
        vector<string> matrix(numLin);
        vector<pair<int,char>> difLetters(1,make_pair(0, ' '));
        int dlSize = 1;

        cin.ignore();
        for(int l=0; l<numLin; l++){            
            getline(cin,matrix[l], '\n'); 
            for(int c=0; c<numCol; c++){
                if(!belongs(matrix[l][c],difLetters,dlSize) && matrix[l][c]>='a' && matrix[l][c]<='z'){
                    difLetters.resize(dlSize+1);
                    difLetters[dlSize-1].second = matrix[l][c];
                    dlSize++;
                }
            }
        }

        //calculating
        for(int aux=0; aux< dlSize-1; aux ++){
            int k = 0, j =0; 
            while(k >=0){
                search(difLetters[aux].second, matrix,numLin, numCol,k,j);
                if(j>=0){
                    paint(difLetters[aux].second, matrix, numLin, numCol,  k,  j);
                    difLetters[aux].first++;
                }
            }
        }
        //sorting
        sort(difLetters.begin(),difLetters.end()-1,auxSort);

        //printing
        cout << "World #" << i+1 << "\n";
        for(int aux=0; aux< dlSize-1; aux ++){
            cout << difLetters[aux].second << ": " << difLetters[aux].first << "\n";
        }
    }

    return 0;
}
