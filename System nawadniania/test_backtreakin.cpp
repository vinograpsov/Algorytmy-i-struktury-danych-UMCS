#include <iostream>
using namespace std;

void printArr(int arr[4]){
    for(int i = 0; i < 4; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void backTreaking(int** arr, int currentPos, int esteticsWeNeed, int currentEstetics, int size,int & money,int temp_money, int currentAttempt){
        
    if ((esteticsWeNeed == currentEstetics) && (currentAttempt != 0)){
        if ((money > temp_money) || (money == -1)){
            money = temp_money;
        }
    }
    for (int i = currentPos; i < size; i++)
    {
        currentAttempt += 1;
        if (currentEstetics + arr[0][i] <= esteticsWeNeed)
        {
            currentEstetics += arr[0][i];
            temp_money += arr[1][i];   
            backTreaking(arr, i + 1, esteticsWeNeed, currentEstetics, size,money,temp_money,currentAttempt);
            temp_money -= arr[1][i];
            currentEstetics -= arr[0][i];
        }
    }
}


int main(){

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
        backTreaking(inputArr,0,0,0,4,money,0,0);
        answers[t] = money;
    }

    for (int i = 0; i < countTests;i++){
        if (answers[i] == -1){
            cout << "NIE"<< "\n";
        }
        else{
            cout << answers[i] << "\n";
        }
    }
}