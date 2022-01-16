#include <iostream>
using namespace std;

void lineSort (char** arr,int n, int k,int m){
    
    char** tempArr = new char*[n];
    // for(int i = 0; i < n; ++i) tempArr[i] = new char[k];



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

    // for(int i = 0; i < n; ++i) {
    //     delete[] tempArr[i];   
    // }
    // delete[] tempArr;

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

    lineSort(inputArr,n,k,m);

    // for(int i = 0; i < n; ++i) {
    //     delete[] inputArr[i];   
    // }
    // delete[] inputArr;
}