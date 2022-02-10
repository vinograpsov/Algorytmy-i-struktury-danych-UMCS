#include <iostream>
using namespace std;

struct Point
{
    int s;
    int c;
};

void backTreaking(Point* arr, int currentPos, int currentEstetics, int size,int & money,int temp_money, bool currentAttempt){
        
    if (((money > temp_money) || (money == -1)) && (currentAttempt != 0) && (0 == currentEstetics) ){
        money = temp_money;
    }
    for (int i = currentPos; (i < size) && ((money == -1)||(money > temp_money)); i++){
        if (temp_money + arr[i].c <= money || money == -1){
            backTreaking(arr, i + 1, currentEstetics + arr[i].s, size,money,temp_money + arr[i].c,true);
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
        
        Point* inputArr = new Point[rowNum];

        int s,c,minSize = 0;
        for(int j = 0; j < rowNum;j++){
            cin >> s >> c;
            if(s != 0 || c != 0){
                inputArr[j].s = s;
                inputArr[j].c = c;
            }
            else{
                minSize +=1;
            }
        }

        int money = -1;
        backTreaking(inputArr,0,0,rowNum - minSize,money,0,false);
        
        if (money == -1){
            cout << "NIE"<< "\n";
        }
        else{
            cout << money << "\n";
        }
    }

}