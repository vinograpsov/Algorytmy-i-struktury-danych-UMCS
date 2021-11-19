#include <iostream> 
using namespace std;

class commandClass{
    public:
    int num;
    string nameOfCommand;
    commandClass(int n,string c){
        num = n;
        nameOfCommand = c;
    }
    commandClass(int n){
        num = n;
        nameOfCommand = "X";
    }
};


// 0 is dad of everething 
// dad must point to brother and first cild  

int main(){
    int numOfCom;
    cin >> numOfCom;
    for(int i = 0; i < numOfCom;i++){
        string command;
        cin >> command;
        int countOfChildren;
        cin >> countOfChildren;
        // возможная имплементация текущего элемента дерева 
        for (int j = 0; j < countOfChildren; j++){
            // make treee and add to lastd child
            int numOfClild;
            cin >> numOfClild; 
            // проверить на то существует ли он или нет 
            // если да и не последний перескочить, если нет и не последний через второй конструктор
            // если да и последний переписать данные, если нет и поелдний создать и переписать через первый конструктор
            // пороверять п овсем элементам 
            
            
            
            
            
            
            
            
            // if (j == countOfChildren - 1){
            //     commandClass lastEl(numOfClild,command);
            // } 

        }
    }
    int kindOfDisplay;
    cin >> kindOfDisplay;
    // show 
}