#include <iostream>
#include <vector>
using namespace std;

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


bool downToUpSwap(int** arr, int pos){
    int ku = findParent(pos);
    if((pos != 0 && arr[pos][1] > arr[ku][1]) || (arr[pos][1] == arr[ku][1] && arr[pos][0] < arr[ku][0])){
        int* temp = arr[pos];
        arr[pos] = arr[ku];
        arr[ku] = temp;
        return true;
    }   
    return false;
}

bool upToDownSwap(int** arr, int& pos, int size){
    int left = leftC(pos);
    int right = rightC(pos);
    if(left >= size) return false;
    
    int next = left; 
    if((arr[left][1] < arr[right][1]) || (arr[left][1] == arr[right][1] && arr[left][0] > arr[right][0])) next = right;
    if((arr[pos][1] < arr[next][1]) || (arr[pos][1] == arr[next][1] && arr[pos][0] > arr[next][0])){
        int* temp = arr[pos];
        arr[pos] = arr[next];
        arr[next] = temp;
        pos = next;
        return true;
    }   
    return false;
}


void arrDownToUpSort(int** arr, int length, int pos){
    bool contin = false;
    int ku = findParent(pos);
    if((pos != 0 && arr[pos][1] > arr[ku][1]) || (arr[pos][1] == arr[ku][1] && arr[pos][0] < arr[ku][0])){
        contin = true;
    }
    int temp_pos = pos;
    while (contin)
    {
        contin = downToUpSwap(arr,temp_pos);
        temp_pos = findParent(temp_pos);
    }
}

void arrUpToDownSort(int** arr, int size){
    bool contin = true;
    int left = leftC(0);
    int right = rightC(0);
    if(left >= size) contin = false;
    
    int next = left; 
    if((arr[left][1] < arr[right][1]) || (arr[left][1] == arr[right][1] && arr[left][0] > arr[right][0])) next = right;
    if((arr[0][1] < arr[next][1]) || (arr[0][1] == arr[next][1] && arr[0][0] > arr[0][0]))contin = false;

    int i = 0;
    while (contin)
    {
        contin = upToDownSwap(arr,i,size);
    }
}

bool check_if_work(int** arr, int length){
    if (length == 1 || length == 0) return false;
    int notZeros;
    for(int i = 0; i < length;i++){
        if(arr[i][1] != 0) notZeros++;
    }
    if(notZeros <= 1) return false;
    return true;
}



void kopiec(int** arr, int length){
    vector<Point> answers;
    int first[2];
    int second[2];
    Point temp;
    bool ku = check_if_work(arr,length);
    int notZeros;
    for(int i = 0; i < length;i++){
        if(arr[i][1] != 0) notZeros++;
    }
    while (ku)
    {

        first[0] = arr[0][0];
        first[1] = arr[0][1];
        arr[0] = arr[length - 1];
        arr[length - 1][0] = 0;
        arr[length - 1][1] = 0;  
        arrUpToDownSort(arr,length);

        second[0] = arr[0][0];
        second[1] = arr[0][1];
        
        arr[0] = arr[length - 1];
        arrUpToDownSort(arr,length);
    
        arr[length - 1][0] = 0;
        arr[length - 1][1] = 0; 

        temp.first = first[0];
        temp.second = second[0];
        answers.push_back(temp);

        first[1] -= 1;
        second[1] -= 1;

        arr[length - 1][0] = first[0];
        arr[length - 1][1] = first[1];
        
        arrDownToUpSort(arr,length,length - 1);
        
        arr[length - 1][0] = second[0];
        arr[length - 1][1] = second[1];
        
        arrDownToUpSort(arr,length,length - 1);
        ku = check_if_work(arr,length);

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


        int **persons = new int*[numOfPeople];
        for(int j = 0; j < numOfPeople; j++) {
            persons[i] = new int[2];
        }
        for (int j = 0; j < numOfPeople; j++){
            persons[j][0] = j + 1;
            cin >> persons[j][1];
            arrDownToUpSort(persons,j + 1,j);
        }
        kopiec(persons,numOfPeople);


    }
}