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


int leftC(int pos) {
    return (2*pos + 1);
}


int rightC(int pos) {
    return (2*pos + 2);
}

int findParent(int pos){
    return (pos - 1) / 2;
}


bool downToUp(vector<Person>& arr, int pos){
    int ku = findParent(pos);
    if((pos != 0 && arr[pos].points > arr[ku].points) || (arr[pos].points == arr[ku].points && arr[pos].num < arr[ku].num)){
        Person temp = arr[pos];
        arr[pos] = arr[ku];
        arr[ku] = temp;
        return true;
    }   
    return false;
}

bool upToDown(vector<Person>& arr, int& pos){
    int left = leftC(pos);
    int right = rightC(pos);
    if(left >= arr.size()) return false;
    
    int next = left; 
    if((arr[left].points < arr[right].points) || (arr[left].points == arr[right].points && arr[left].num > arr[right].num)) next = right;

    if((arr[pos].points < arr[next].points) || (arr[pos].points == arr[next].points && arr[pos].num > arr[next].num)){
        Person temp = arr[pos];
        arr[pos] = arr[next];
        arr[next] = temp;
        pos = next;
        return true;
    }   
    return false;
}


void arrDownToUpSort(vector<Person>& arr, int length, int pos){
    bool contin = false;
    int ku = findParent(pos);
    if((pos != 0 && arr[pos].points > arr[ku].points) || (arr[pos].points == arr[ku].points && arr[pos].num < arr[ku].num)){
        contin = true;
    }
    int temp_pos = pos;
    while (contin)
    {
        contin = downToUp(arr,temp_pos);
        temp_pos = findParent(temp_pos);
    }
}

void arrUpToDownSort(vector<Person>& arr, int length){
    bool contin = true;
    int left = leftC(0);
    int right = rightC(0);
    if(left >= arr.size()) contin = false;
    
    int next = left; // 0 left/1 right
    if((arr[left].points < arr[right].points) || (arr[left].points == arr[right].points && arr[left].num > arr[right].num)) next = right;
    if((arr[0].points > arr[next].points) || (arr[0].points == arr[next].points && arr[0].num < arr[next].num))contin = false;

    int i = 0;
    while (contin)
    {
        contin = upToDown(arr,i);
    }
}

bool check_if_work(vector<Person>& arr){
    int length = arr.size();
    if (length == 1 || length == 0) return false;
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
    bool ku = check_if_work(arr);
    while (ku)
    {
        Person first;
        Person second;
        
        first = arr[0];
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        arrUpToDownSort(arr,arr.size());

        second = arr[0];
        if(arr.size() == 1){
            arr.pop_back();
        }
        else{
            arr[0] = arr[arr.size() - 1];
            arr.pop_back();
            arrUpToDownSort(arr,arr.size());
        }

        Point temp;
        temp.first = first.num;
        temp.second = second.num;
        answers.push_back(temp);

        first.points -= 1;
        second.points -= 1;

        arr.push_back(first);
        delLastZeros(arr);
        arrDownToUpSort(arr,arr.size(),arr.size() - 1);
        
        
        arr.push_back(second);
        delLastZeros(arr);
        arrDownToUpSort(arr,arr.size(),arr.size() - 1);
        ku = check_if_work(arr);

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
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
            arrDownToUpSort(arr,arr.size(),j);
        }

        delLastZeros(arr);
        kopiec(arr,numOfPeople);


    }
}