#include <iostream>
using namespace std;

int countMoney(int** arr,int rowsNum){
    int minMoney = -1;
    


    for (int i = 0; i < rowsNum;i++){
        int currentPos;    
        
        if (i + 1 < rowsNum){
            currentPos = -1;
        }        
        
        else{
            currentPos = i + 1;
        }
        
        for (int j = currentPos; j < rowsNum;j++){
            int tempMoney = arr[i][1];
            int countEstetics = arr[i][0];
            
            if (countEstetics + arr[j][0] < 0){
                countEstetics += arr[j][0];
                tempMoney += arr[j][1];
            }
            
            else if (countEstetics + arr[j][0] > 0){

                if ((currentPos + 1 != rowsNum) && (j != rowsNum - 1)){ // (j != rowsNum - 1)
                    continue;
                }
                
                else if((currentPos + 1 != rowsNum) && (j == rowsNum - 1)){
                    currentPos += 1;
                    j = currentPos - 1;
                }

                else{
                    break;
                }

            }

            else{
                if (minMoney > tempMoney) minMoney = tempMoney;
            }
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