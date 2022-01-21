//  O(log n) 
#include <iostream>
#include <vector> // ??????
using namespace std;



struct Person
{
    int num;
    int points;
};

struct Answer
{
    int first;
    int second;
};


void printArr(Person* arr,int length){
    for(int i = 0; i < length; i++){
        cout << arr[i].points << " "  << arr[i].num << "\n";
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
                printArr(arr,6);
        return true;
    }   
    return false;
}

Person* copyArr(Person* arrForCopy, Person* arr, int length){
    for(int i = 0; i < length;i++){
        arr[i] = arrForCopy[i];
    }
}

bool check_for_zeros(Person* arr, int length){
    if (length == 1) return false;
    int zerosNum = 0;
    for (int i = 0; i < length; i++){
        if (arr[i].points == 0)  zerosNum += 1;
    }
    if (zerosNum == length || zerosNum == length - 1) return false;
    return true;
}

Person* arrSort(Person* arr, int length){
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




void kopiec(Person* arr, int length){
    vector<Answer> answers;
    arr = arrSort(arr,length);

    bool work = check_for_zeros(arr,length);
    
    while (work){
        Person firstPerson, secondPerson;
        firstPerson = arr[0];
        int startLength = length;
        if (length != 2){
            Person* newArr = new Person[length - 1];
            newArr = copyArr(arr, newArr, length - 1);
            delete[] arr;
            length -= 1;
            newArr = arrSort(newArr, length);
            
            secondPerson = arr[0];
            Person* arr = new Person[length - 1];
            arr = copyArr(newArr, arr, length - 1);
            delete[] newArr;
            length -= 1;
            arr = arrSort(arr,length);
        }
    
        else{
            secondPerson = arr[1];
        }

        if (firstPerson.num > secondPerson.num){
            Answer pForAdd;
            pForAdd.first = secondPerson.num;
            pForAdd.second = firstPerson.num;
            answers.push_back(pForAdd);
        }
        else{
            Answer pForAdd;
            pForAdd.second = secondPerson.num;
            pForAdd.first = firstPerson.num;
            answers.push_back(pForAdd);
        }

        firstPerson.points -= 1;
        secondPerson.points -= 1;

        int howToAdd;
        if (firstPerson.points != 0) howToAdd++;
        if(secondPerson.points != 0) howToAdd++;

        if (howToAdd == 1 && startLength != 2){
            Person* newArr = new Person[length + 1];
            newArr = copyArr(arr, newArr, length + 1);
            newArr = arrSort(newArr,length + 1);
            delete[] arr;
            length += 1;
            
            Person* arr = new Person[length];
            arr = copyArr(newArr, arr, length);
            delete[] newArr;
        }
        else if(howToAdd == 2 && startLength != 2){
            Person* newArr = new Person[length + 1];
            newArr = copyArr(arr, newArr, length + 1);
            newArr = arrSort(newArr,length + 1);
            delete[] arr;
            length += 1;


            Person* arr = new Person[length + 1 ];
            arr = copyArr(newArr, arr, length + 1);
            arr = arrSort(arr,length + 1);
            delete[] newArr;
            length += 1;
        }  
    }

    int tmpSize = answers.size();
    cout << tmpSize << "\n";
    for (int i = 0; i < tmpSize; i++){
        cout << answers[i].first << answers[i].second << "\n";
    }



}


int main(){
    int testNum;
    cin >> testNum;
    for(int i = 0; i < testNum; i++){
        int numOfPeople;
        cin >> numOfPeople;

        Person* arr = new Person[numOfPeople];
        Person temp;
        for (int j = 0; j < numOfPeople; j++){
            temp.num = j + 1;
            cin >> temp.points;
            arr[j] = temp;
        }


        kopiec(arr,numOfPeople);


    }
}



























       // int* arr = new int[numOfPeople];
        // for (int j = 0; j < numOfPeople; j++){
        //     cin >> arr[j];
        // } 
