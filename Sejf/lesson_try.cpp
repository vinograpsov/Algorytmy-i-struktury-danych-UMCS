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


void lineSort (char** arr,int n, int k,int m){
    
    char** tempArr = new char*[n];
    for(int i = 0; i < n; ++i) tempArr[i] = new char[k];



    for (int i = k - 1;i >= 0; i--){
        
        int numX = 0 ,numO = 0;
        for (int j = n - 1;j >= 0; j--){
            if (arr[j][i] == 'X') numX += 1;
            else numO += 1;
        }
        numX += numO;

        for (int j = n - 1;j >= 0; j--){
            if (arr[j][i] == 'X'){
                tempArr[numX -1] = arr[j];
                numX -=1;
            }
            else
            {
                tempArr[numO -1] = arr[j];
                numO -=1;
            }
            
            
        }
        // cout <<"-----------------\n";
        // printArr(tempArr,n,k);
        // cout <<"-----------------\n" ;
        // cout << numX << " " <<numO << "\n"; 
        for(int j = 0; j < n;j++){
            arr[j] = tempArr[j];
        }
        
        
    
    }

    for (int i = n - 1;i >= n - m;i--){
        for (int j = 0; j < k;j++){
            cout << arr[i][j];
        }
        cout << "\n";
    }
    // tempArr = arr;
    // printArr(tempArr,n,k);
}



int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
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


    // int* tempArr = new int[n];
    // for (int i = 0; i < n; i++){
    //     tempArr[i] = coutHardes(inputArr[i],k);
    // }
    // for (int i = 0; i < n;i++){
    //     cout << tempArr[i] << " ";
    // }


    lineSort(inputArr,n,k,m);
}