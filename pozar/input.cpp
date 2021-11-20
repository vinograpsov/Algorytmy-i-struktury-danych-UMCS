#include <iostream>
// typedef unsigned un;
using namespace std;
// redo to unsigned short int 


int codeType(char symbol){
    if (symbol == '.'){
        return 1001;
    }
    else if(symbol == '#')
    {
        return 1002;
    }
    else if(symbol == 'O')
    {
        return 1003;
    }
    else if (symbol == 'M')
    {
        return 1004;
    }
    else
    {
        return 1005; //error code
    }
    
} 



void testInp(int* arr,int n, int m){
    for (int i = 0; i< n * m;i++){
        if (i % n == 0 && i != 0){
            cout << "\n";
        }
        
        cout << arr[i] << " ";
        
    }
}  





int main(){
    int numOfTests;
    //Node *labirints = NULL;
    cin >> numOfTests;
    
    
    for (int k = 0; k < numOfTests; k++){
        int m,n;
        cin >> n >> m;
        int *arr = new int[n*m];
        for (int i = 0; i< n*m;i++){
            char symbol;
            cin >> symbol;
            arr[i] = codeType(symbol);
        }
        testInp(arr,n,m);
        cout << "\n";
    } 


}
    