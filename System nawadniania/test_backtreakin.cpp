#include <iostream>
using namespace std;

void printArr(int arr[4]){
    for(int i = 0; i < 4; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void backTreaking(int arr[4],int size, int currentPos, int currentEstetics,bool & tempFound, int currentAttempt){
    int ecteticsSum = 0;
    if ((ecteticsSum == currentEstetics) && (currentAttempt != 0)){
        tempFound = true;
    }

    for(int i = currentPos;i < size;i++){
        currentAttempt += 1;
        if(currentEstetics + arr[i] <= ecteticsSum){
            currentEstetics += arr[i];  
            backTreaking(arr,4,currentPos,currentEstetics,tempFound,currentAttempt);
            currentEstetics -= arr[i];
        }
    }
}



int main(){
    int arr[4] = {-10,3,10,7};
    bool f = false;
    backTreaking(arr,4,0,0,f,0);
            if (f)
           cout << "subset with the given sum found" << endl;
        else
           cout << "no required subset found" << endl;   
        return 0;

}