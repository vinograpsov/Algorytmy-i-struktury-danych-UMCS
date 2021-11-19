#include <iostream>


struct Vegetable
{
    std::string name;
    float param1;
    float param2;    
    float param3;
};

void sortVeg(Vegetable vegArray[], int start, int finish){
    int interationSum = 0 ;
    Vegetable temp2; 
    
    
    for (int j,i = start; i < finish; i++)
    {
        temp2 = vegArray[i];
        j = i - 1;
        while (j >= start && vegArray[j].param1 < temp2.param1)
        {
            vegArray[j + 1] = vegArray[j];
            j = j - 1;
        }
        vegArray[j + 1] = temp2;
    }
    
    
    for (int j,  i = start; i < finish; i++)
    {
        temp2 = vegArray[i];
        j = i - 1;
        while (j >= start && j >= start && vegArray[j].param1 == temp2.param1 && vegArray[j].param2 < temp2.param2)
        {
            vegArray[j + 1] = vegArray[j];
            j = j - 1;
        }
        vegArray[j + 1] = temp2;
    }
    
    
    for (int j, i = start; i < finish; i++)
    {
        temp2 = vegArray[i];
        j = i - 1;
        while (j >= start && j >= start && vegArray[j].param1 == temp2.param1 && vegArray[j].param2 == temp2.param2 && vegArray[j].param3 < temp2.param3)
        {
            vegArray[j + 1] = vegArray[j];
            j = j - 1;
        }
        vegArray[j + 1] = temp2;
    }
}


void printAnswer(Vegetable vegArray[], int numDoubleLines){
    for(int i = 0; i < numDoubleLines;i++){
        std::cout << vegArray[i].name << "-" << vegArray[i + numDoubleLines].name << " ";
    }
}


// void printArr(Vegetable arr[],int n){
//     for (int i = 0; i < n * 2; i++){
//         cout << arr[i].name << " " << arr[i].param1 << " " << arr[i].param2 << " " << arr[i].param3 << "\n";
//     }
// } 


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int numDoubleLines;
    std::cin >> numDoubleLines;
    int criteriumArr[3];
    for (int i = 0; i < 3; i++){
        std::cin >> criteriumArr[i];
    }
    Vegetable *vegArr = new Vegetable[numDoubleLines * 2];
    for(int i = 0; i < numDoubleLines * 2; i++){
        std::string name;
        float param1,param2,param3;
        std::cin >> name >> param1 >> param2 >> param3;
        switch(criteriumArr[0]){
            case 1:
                switch(criteriumArr[1]){
                    case 2:
                        vegArr[i].name = name;
                        vegArr[i].param1 = param1;
                        vegArr[i].param2 = param2;
                        vegArr[i].param3 = param3;
                        break;
                    default:
                        vegArr[i].name = name;
                        vegArr[i].param1 = param1;
                        vegArr[i].param2 = param3;
                        vegArr[i].param3 = param2;
                        break;
                }
                break;
            case 2:
                switch(criteriumArr[1]){
                    case 1:
                        vegArr[i].name = name;
                        vegArr[i].param1 = param2;
                        vegArr[i].param2 = param1;
                        vegArr[i].param3 = param3;
                        break;
                    default:
                        vegArr[i].name = name;
                        vegArr[i].param1 = param2;
                        vegArr[i].param2 = param3;
                        vegArr[i].param3 = param1;
                        break;
                }
                break;
            case 3:
                switch(criteriumArr[1]){
                    case 2:
                        vegArr[i].name = name;
                        vegArr[i].param1 = param3;
                        vegArr[i].param2 = param2;
                        vegArr[i].param3 = param1;
                        break;
                    default:
                        vegArr[i].name = name;
                        vegArr[i].param1 = param3;
                        vegArr[i].param2 = param1;
                        vegArr[i].param3 = param2;
                        break;
                }
                break;
        } 
    }
    sortVeg(vegArr,0,numDoubleLines);
    sortVeg(vegArr,numDoubleLines,numDoubleLines*2);
//    cout << "-------------------------------" << "\n";
//    printArr(vegArr,numDoubleLines);
    printAnswer(vegArr,numDoubleLines);
    

}