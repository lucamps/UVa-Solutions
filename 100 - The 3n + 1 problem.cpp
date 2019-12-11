#include <iostream>
using namespace std;

int cycleLength(int n){
    int cont = 0;
    while(true){
        cont ++;
        if(n == 1)
            break;
        if(n%2 != 0) //is odd
            n = 3*n + 1;
        else
            n /= 2; 
    }
    return cont;
}

int main(){
    int i, j;
    int s, h; //smallest, higher
    int max;
    int temp;

    while (cin >> i){
        cin >> j;
        max = 0;

        //checking which number is higher
        if (i<=j){
            s = i;
            h = j;
        }
        else{
            s = j;
            h = i;
        }
        
        //assigning the maximum cycle length to "max"
        for(int k=s; k<=h; k++){
            temp = cycleLength(k);
            if(temp > max)
                max = temp;
        }

        //printing the answer
        cout << i << " " << j << " " << max << "\n";
    }
    return 0;
}
