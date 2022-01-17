#include <iostream>
using namespace std;

int countMoney(int** arr,int rowsNum){
    int minMoney = -1;
    for (int i = 0; i < rowsNum; i++){
                int currentPos;    
        
        if (i + 1 < rowsNum){
            currentPos = -1;
        }        
        
        else{
            currentPos = i + 1;
        }



    }
    return minMoney;
}


int main(){
    int testNum;
    cin >> testNum;
    int* answers = new int[testNum];

    for(int i = 0; i < testNum;i++){
        
        int rowsNum;
        cin >> rowsNum;
        int** esteticsAndPrice = new int*[rowsNum];
        
        for(int j = 0; j < rowsNum; ++j) esteticsAndPrice[j] = new int[2];
        for(int j = 0; j < rowsNum;j++){
            cin >> esteticsAndPrice[j][0] >> esteticsAndPrice[j][1];
        }

        cout << countMoney(esteticsAndPrice,rowsNum);
    }


}