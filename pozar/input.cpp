#include <iostream>
// typedef unsigned un;
using namespace std;
// redo to unsigned short int 


int codeType(char symbol){
    if (symbol == '.'){
        return 1000001;
    }
    else if(symbol == '#')
    {
        return 1000002;
    }
    else if(symbol == 'O')
    {
        return 1000003;
    }
    else if (symbol == 'M')
    {
        return 1000004;
    }
    else
    {
        return 1000005; //error code
    }
    
} 

int makeStepArr(int arrKind, int* arr,int value){
    if(arrKind == 1){
        if (value != 1000004){
            return value;
        }
        else
        {
            return 1000001;
        }
        
    }
    else
    {
        if (value != 1000003){
            return value;
        }
        else
        {
            return 1000001;
        }
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
        int *fireArr = new int[n*m];
        int *manStepArr = new int [n*m]; 
        for (int i = 0; i< n*m;i++){
            char symbol;
            cin >> symbol;
            fireArr[i] = makeStepArr(0,fireArr,codeType(symbol));
            manStepArr[i] = makeStepArr(1,manStepArr,codeType(symbol));
        }
        cout << "\n";
        testInp(fireArr,n,m);
        cout << "\n";
        cout << "\n";
        testInp(manStepArr,n,m);
        cout << "\n";
    } 


}
    