#include <iostream>
using namespace std;

void backTreaking(int** arr, int currentPos, int currentEstetics, int size,int & money,int temp_money, int currentAttempt){
        
    if ((0 == currentEstetics) && (currentAttempt != 0) && ((money > temp_money) || (money == -1))){
        money = temp_money;
        return;
    }

    currentAttempt += 1;
    for (int i = currentPos; i < size; i++)
    {
        if ((money == -1)||(money > temp_money))
        { 
            backTreaking(arr, i + 1, currentEstetics + arr[0][i], size,money,temp_money + arr[1][i],currentAttempt);
        }
    } 
}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int countTests;
    cin >> countTests;
    int* answers = new int[countTests];
    for (int t = 0; t < countTests;t++){
        int rowNum;
        cin >> rowNum;
        int** inputArr = new int*[2];
        for(int i = 0; i < 2; ++i)
            inputArr[i] = new int[rowNum];

        for(int j = 0; j < rowNum;j++){
            cin >> inputArr[0][j] >> inputArr[1][j];
        }

        int money = -1;
        backTreaking(inputArr,0,0,rowNum,money,0,0);
        if (money == -1){
            cout << "NIE"<< "\n";
        }
        else{
            cout << money << "\n";
        }
    }

}