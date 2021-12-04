#include <iostream>
#include <queue>
#include <cstring>



using namespace std;

struct Point 
{
    int x;
    int y;
};

struct ExitPoint
{
    Point exit;
    int manStepCount;
    int fireStepCount;
};

struct  queueNode
{
    Point pt;
    int dist; 
};


int codeType(char symbol){
    if (symbol == '.'){
        return 1;
    }
    else if(symbol == '#')
    {
        return 0;
    }
    else if(symbol == 'O')
    {
        return 3;
    }
    else if (symbol == 'M')
    {
        return 4;
    }
    else
    {
        return -1; //error code
    }
    
} 





void testInp(int** arr,int arrY, int arrX){
    for (int i = 0;i < arrY;i++){
        for(int j = 0;j < arrX;j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}  

void testBFS(bool** arr,int rows,int cols){
    for (int i = 0;i < rows;i++){
        for(int j = 0;j < cols;j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}



int main(){
    vector<int> answers;  
   
    // получаем количество тестов
    int numOfTests;
    cin >> numOfTests;
    
    // проверка на ошибки
    bool noErrors = true;

    // получаем одну таблицу
    for (int k = 0; k < numOfTests && noErrors; k++){
        //  получаем строки и столбцы тут может быть ошибка
        int arrY,arrX;
        cin >> arrY >> arrX;
        
        
        //создаем таблицу с выходными точками,позиция чела,таблица позиций огня
        vector<ExitPoint> exitPoints;
        int exitNum = 0;
        vector<Point> firePositions;
        int fireNum = 0;
        Point manPosition;
        
    
        //создание лабиринта 
        int** maze = new int* [arrY];
        for (int i = 0; i < arrY; i++){
            maze[i] = new int[arrX];;
        }



        //запись в лабиринт  
        for (int i = 0; i < arrY; i++){
            for(int j = 0; j < arrX; j++){
                char symbol;
                cin >> symbol;
                int intSymbol = codeType(symbol);
                
                //проверка входит ли символ
                if (intSymbol == -1) noErrors = false;

                //считаем и добавляем токи выхода
                if ((i == 0 || i == arrY - 1) && intSymbol == 1){
                    ExitPoint temp;
                    temp.exit.x = j;
                    temp.exit.y = i;
                    temp.fireStepCount = -1;
                    temp.manStepCount = -1;
                    exitPoints.insert(exitPoints.end(),temp);
                    exitNum++;
                }
                else if((j == 0 || j == arrX - 1) && intSymbol == 1){
                    ExitPoint temp;
                    temp.exit.x = j;
                    temp.exit.y = i;
                    temp.fireStepCount = -1;
                    temp.manStepCount = -1;
                    exitPoints.insert(exitPoints.end(),temp);
                    exitNum++; // ???
                }
                
                
                //заполняем хаш - 0, точка - 1
                if(intSymbol == 1 || intSymbol == 0) maze[i][j] = intSymbol;                
                
                // огонь будет равен хашу и добавляем огонь в свою точку 
                else if(intSymbol == 3){
                    Point temp;
                    temp.x = j;
                    temp.y = i;
                    firePositions.insert(firePositions.end(),temp);
                    fireNum++;
                    maze[i][j] = 0;
                }               
                
                // чувака записываем и принимает его положение за точку 
                else if(intSymbol == 4){
                    manPosition.x = j; // ??????
                    manPosition.y = i; // ??????
                    maze[i][j] = 1;
                }                 
                
   
            }   
        }
        testInp(maze,arrY,arrX);
        cout << manPosition.x << manPosition.y << "\n";
        
        cout << firePositions[0].x << firePositions[0].y << "\n";    
        cout << firePositions[1].x << firePositions[1].y << "\n";
    
        cout << exitPoints[0].exit.x << exitPoints[0].exit.y << "\n";
        cout << exitPoints[1].exit.x << exitPoints[1].exit.y << "\n";

    } 
}
    