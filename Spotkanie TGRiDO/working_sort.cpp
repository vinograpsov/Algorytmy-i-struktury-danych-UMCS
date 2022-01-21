#include <iostream>
using namespace std;


struct Person
{
    int num;
    int points;
};


void printArr(Person* arr,int length){
    for(int i = 0; i < length; i++){
        cout << arr[i].num << " "  << arr[i].points << "\n";
    }
    cout << "\n";
}

int _pow(int n, int k){ // need to test
    int temp = n;
    for (int i = 0; i < k - 1; i++){
        temp *= n;
    }
    return temp;
}

int findParent(int pos){
    if (pos == 1) return 0;
    else if (pos % 2 == 1){
        return (pos - 1) / 2;
    }
    return pos / 2 - 1;
}

bool sortOneEl(Person* arr, int pos){
    int ku = findParent(pos);
    if(pos != 0 && arr[pos].points > arr[ku].points){
        Person temp = arr[pos];
        arr[pos] = arr[ku];
        arr[ku] = temp;
                // printArr(arr,6);
        return true;
    }   
    return false;
}


Person* firstArrSort(Person* arr, int length){
    for (int i = 1; i < length; i++){
        bool contin = true;
        int temp_pos = i;
        while (contin)
        {
            contin = sortOneEl(arr,temp_pos);
            temp_pos = findParent(temp_pos);
        }
    }
    return arr;
}

int main(){
    int numOfPeople;
    cin >> numOfPeople;
    Person* arr = new Person[numOfPeople];
    Person temp;
    for (int j = 0; j < numOfPeople; j++){
        temp.num = j + 1;
        cin >> temp.points;
        arr[j] = temp;
    }

    printArr(arr,numOfPeople);
    arr = firstArrSort(arr,numOfPeople);
    printArr(arr,numOfPeople);


}