#include <iostream>
#include <vector>
using namespace std;


struct Person
{
    int num;
    int points;
};

struct Point
{
    int first;
    int second;
};

int findParent(int pos){
    if (pos % 2 == 1){
        return (pos - 1) / 2;
    }
    else if (pos == 1) return 0;
    return pos / 2 - 1;
}

int getLeftChild(int pos){
    return pos * 2 + 1;
}

bool sortOneEl(vector<Person>& arr, int pos){
    int ku = findParent(pos);
    if((pos != 0 && arr[pos].points > arr[ku].points) || (arr[pos].points == arr[ku].points && arr[pos].num < arr[ku].num)){
        Person temp = arr[pos];
        arr[pos] = arr[ku];
        arr[ku] = temp;
        return true;
    }   
    return false;
}


void arrUpSort(vector<Person>& arr){
    int length = arr.size();
    for (int i = 1; i < length; i++){
        bool contin = true;
        int temp_pos = i;
        while (contin)
        {
            contin = sortOneEl(arr,temp_pos);
            temp_pos = findParent(temp_pos);
        }
    }
}


void arrUpElSort(vector<Person>& arr){ // up el
    int length = arr.size();
    bool contin = true;
    for (int i = 0; contin;){
        int leftC = getLeftChild(i);
        int rigthC = leftC + 1;
        if(leftC <= length - 1){
            if(rigthC <= length - 1){
                if((arr[leftC].points > arr[rigthC].points) || (arr[leftC].points == arr[rigthC].points && arr[leftC].num < arr[rigthC].num)){
                    contin = sortOneEl(arr,leftC);
                    i = leftC;
                }
                else{
                    contin = sortOneEl(arr,rigthC);
                    i = rigthC;
                }
            }
            else{
                contin = sortOneEl(arr,leftC);
                i = leftC;
            }
        }
        else{
            contin = false;
        }
    }
}

void arrDownSort(vector<Person>& arr){ // last el
    int length = arr.size();
    bool contin = true;
    for (int i = length - 1;contin;){
        contin = sortOneEl(arr,i);
        i = findParent(i);
    }
}


bool check_if_work(vector<Person>& arr){
    int length = arr.size();
    if (length == 1 || length == 0) return false;
    int tempNum = 0;
    for (int i = 0; i < arr.size(); i++){
        if(arr[i].points != 0) tempNum += 1;
    }
    if(tempNum == 1 || tempNum == 0) return false;
    return true;
}

void delLastZeros(vector<Person>& arr){
    int length = arr.size();
    for (int i = length - 1; i >= 0; i--){
        if (arr[i].points == 0) arr.pop_back();
        else i = -1;
    }
}



void kopiec(vector<Person> arr, int length){
    vector<Point> answers;

    vector<Person> tempA;
    for(int i = 0; i < length; i++){
        tempA.push_back(arr[i]);
        arrDownSort(tempA);
    }

    for(int i = 0; i < length;i++){
        arr[i] = tempA[i];
    }
    delLastZeros(arr);
    bool ku = check_if_work(arr);
    while (ku)
    {
        int length = arr.size();
        Person first;
        Person second;
        
        first = arr[0];
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        arrUpElSort(arr);
        length--;

        second = arr[0];
        if(length == 1){
            arr.pop_back();
            length--;
        }
        else{
            arr[0] = arr[length - 1];
            arr.pop_back();
            arrUpElSort(arr);
            length--;
        }

        Point temp;
        temp.first = first.num;
        temp.second = second.num;
        answers.push_back(temp);

        first.points -= 1;
        second.points -= 1;

        if(first.points == 0 && second.points == 0){
            delLastZeros(arr);
            ku = check_if_work(arr);
        }
        else if(first.points != 0 && second.points == 0){
            arr.push_back(first);
            arrDownSort(arr);
            delLastZeros(arr);
            ku = check_if_work(arr);
        }
        else if(first.points == 0 && second.points != 0){
            arr.push_back(second);
            arrDownSort(arr);
            delLastZeros(arr);
            ku = check_if_work(arr);
        }
        else{
            arr.push_back(first);
            arrDownSort(arr);
            delLastZeros(arr);

            arr.push_back(second);
            arrDownSort(arr);
            delLastZeros(arr);
            ku = check_if_work(arr);
        }

    }
    
    int lengthA = answers.size(); 
    cout << lengthA << "\n";
    for(int i = 0; i < lengthA; i++){
        if( answers[i].first > answers[i].second){
            cout << answers[i].second << " " <<answers[i].first << "\n";
        }
        else{
            cout << answers[i].first << " " <<answers[i].second << "\n";
        }
    }

}

int main(){
    int testNum;
    cin >> testNum;
    for(int i = 0; i < testNum; i++){
        int numOfPeople;
        cin >> numOfPeople;
        vector<Person> arr;
        Person temp;
        for (int j = 0; j < numOfPeople; j++){
            temp.num = j + 1;
            cin >> temp.points;
            arr.push_back(temp);
        }
        kopiec(arr,numOfPeople);
    }
}