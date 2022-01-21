#include <iostream>
using namespace std;

struct Point
{
    int s;
    int c;
};


void backTreaking(Point* arr, int currentPos, int currentEstetics, int size,int & money,int temp_money, int currentAttempt){
        
    if ((0 == currentEstetics) && (currentAttempt != 0) && ((money > temp_money) || (money == -1))){
        money = temp_money;
        return;
    }
   
    currentAttempt += 1;
    for (int i = currentPos; (i < size) && ((money == -1)||(money > temp_money)); i++){
        backTreaking(arr, i + 1, currentEstetics + arr[i].s, size,money,temp_money + arr[i].c,currentAttempt);
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
        
        Point* inputArr = new Point[rowNum];

        for(int j = 0; j < rowNum;j++){
            cin >> inputArr[j].s >> inputArr[j].c;
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