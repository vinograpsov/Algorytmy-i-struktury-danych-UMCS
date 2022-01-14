#include <iostream>
using namespace std;

int pow(int num, int deg) {
    long result = 1;
    for(long i = 0; i < deg; i++) {
        result *= num;
    }
    return result;
}


int coutHardes(char* arr,int k){
    int result = 0; 
    for (int i = 0; i < k; i++){
        if (arr[i] == 'X'){
            result += pow(2,k-i-1);
        }
    }
    return result;
}


void printArr(char** arr,int n,int k){
    for (int i = 0; i < n;i++){
        for(int j = 0; j < k;j++){
            cout << arr[i][j] ;
        }
        cout << "\n";
    } 
}


void lineSort (char** arr,int n, int k){
    
    char** tempArr = new char*[n];
    for(int i = 0; i < n; ++i) tempArr[i] = new char[k];



    for (int i = k - 1;i >= 0; i--){
        
        int numX = 0 ,numO = 0;
        for (int j = n - 1;j >= 0; j--){
            char temp = arr[j][i];
            if (temp == 'X') numX += 1;
            else numO += 1;
        }
        numX += numO;

        cout << numX << " " <<numO << "\n"; 
    
    }


    tempArr = arr;
    printArr(tempArr,n,k);
}



int main(){
    int n,k,m;
    cin >> n >> k >> m;
    char** inputArr = new char*[n];
    for(int i = 0; i < n; ++i)
        inputArr[i] = new char[k];
    
    for (int i = 0; i < n;i++){
        for(int j = 0; j < k;j++){
            cin >> inputArr[i][j]; 
        }
    }


    int* tempArr = new int[n];
    for (int i = 0; i < n; i++){
        tempArr[i] = coutHardes(inputArr[i],k);
    }
    for (int i = 0; i < n;i++){
        cout << tempArr[i] << " ";
    }


    lineSort(inputArr,n,k);
}