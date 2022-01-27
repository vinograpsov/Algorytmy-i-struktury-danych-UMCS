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

void printA(vector<Person> arr){
    cout << "--------------------" << "\n";
    for (int i = 0 ; i < arr.size(); i++){
        cout << arr[i].num << " " << arr[i].points << "\n";
    }
    cout << "--------------------" << "\n";
}

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

void upS(vector<Person>& arr, int pos){
    int par = findParent(pos);
    if((pos != 0 && arr[pos].points > arr[par].points) || (arr[pos].points == arr[par].points && arr[pos].num < arr[par].num)){
        Person temp = arr[pos];
        arr[pos] = arr[par];
        arr[par] = temp;
        upS(arr,par);
    }   
}

void downS(vector<Person>& arr, int pos){
    int leftC = getLeftChild(pos);
    int rightC = leftC + 1;
    int length = arr.size();
    if(rightC == length){
        if((arr[pos].points < arr[leftC].points) || (arr[pos].points == arr[leftC].points && arr[pos].num > arr[leftC].num)){
            Person temp = arr[pos];
            arr[pos] = arr[leftC];
            arr[leftC] = temp;
        }
    }

    else if(rightC <= length - 1){
        bool is_left = true;
        if (((arr[leftC].num > arr[rightC].num) && arr[leftC].points == arr[rightC].points) || (arr[leftC].points < arr[rightC].points) ) is_left = false; // ??????
        if(((arr[pos].points < arr[leftC].points) || (arr[pos].points == arr[leftC].points && arr[pos].num > arr[leftC].num)) && is_left){
            Person temp = arr[pos];
            arr[pos] = arr[leftC];
            arr[leftC] = temp;
            downS(arr,leftC);
        }
        
        else if((arr[pos].points < arr[rightC].points) || (arr[pos].points == arr[rightC].points && arr[pos].num > arr[rightC].num)){
            Person temp = arr[pos];
            arr[pos] = arr[rightC];
            arr[rightC] = temp;
            downS(arr,rightC);
        }
    }
}




void kopiec(vector<Person> arr, int length){
    
    vector<Point> answers;
    vector<Person> tempA;

    for(int i = 0; i < length; i++){
        tempA.push_back(arr[i]);
        upS(tempA,i);
    }

    for(int i = 0; i < length; i++){
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
        downS(arr,0);
        length--;
    
        second = arr[0];
        if(length == 1){
            arr.pop_back();
            length--;
        }
        else{
            arr[0] = arr[length - 1];
            arr.pop_back();
            downS(arr,0);
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
            upS(arr,length);
            delLastZeros(arr);
            ku = check_if_work(arr);
        }
        else if(first.points == 0 && second.points != 0){
            arr.push_back(second);
            upS(arr,length);
            delLastZeros(arr);
            ku = check_if_work(arr);
        }
        else{
            arr.push_back(first);
            upS(arr,length);
            delLastZeros(arr);

            arr.push_back(second);
            upS(arr,length + 1);
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