#include <iostream>
using namespace std;





string answerFunk(){

}



int main(){
    int numOfTests;
    int length;



    cin >> numOfTests;
    
    string* answers = new string[length];
    

    
    for(int d = 0; d < numOfTests;d++){
    
        
        cin >> length;
        int** areasArr = new int* [length];
        for (int i = 0; i < length; i++){
            areasArr[i] = new int [4];
        }



        answers[d] = answerFunk();
    }

    for(int i = 0; i < length; i++){
        cout << answers[i] << "\n";  
    }
}