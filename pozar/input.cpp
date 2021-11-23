#include <iostream>
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

int makeStepArr(int arrKind, int* arr,int value){
    if(arrKind == 1){
        if (value != 1000004){
            return value;
        }
        else
        {
            return 1000001;
        }
        
    }
    else
    {
        if (value != 1000003){
            return value;
        }
        else
        {
            return 1000001;
        }
    }
    
}




void testInp(int** arr,int rows, int cols){
    for (int i = 0;i < rows;i++){
        for(int j = 0;j < cols;j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}  





int main(){
    // получаем количество тестов
    int numOfTests;
    cin >> numOfTests;
    
    // проверка на ошибки
    bool noErrors = true;

    // получаем одну таблицу
    for (int k = 0; k < numOfTests && noErrors; k++){
        //  получаем строки и столбцы тут может быть ошибка
        int rows,cols;
        cin >> rows >> cols;
        
        
        //создаем таблицу с выходными точками,позиция чела,таблица позиций огня
        ExitPoint* exitPoints = new ExitPoint[cols*2 + (rows -2)*2]; // переделать это либо под векторы либо по чтото другое 
        int exitNum = 0;
        Point manPosition;
        Point* firePositions = new Point[rows * cols - cols*2 - (rows -2)*2]; // ?????????? 
        int fireNum = 0;
    
        //создание лабиринта 
        int** maze = new int* [rows];
        for (int i = 0; i < rows; i++){
            maze[i] = new int[cols];;
        }



        //запись в лабиринт тут тоже может быть ошибка 
        for (int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                char symbol;
                cin >> symbol;
                int intSymbol = codeType(symbol);
                
                //проверка входит ли символ
                if (intSymbol == -1) noErrors = false;

                //считаем и добавляем токи выхода
                if ((i == 0 || i == rows - 1) && intSymbol == 1){
                    exitPoints[exitNum].exit.x = j;
                    exitPoints[exitNum].exit.y = i;
                    exitNum++;
                }
                else if((j == 0 || j == cols - 1) && intSymbol == 1){
                    exitPoints[exitNum].exit.x = j;
                    exitPoints[exitNum].exit.y = i;
                    exitNum++;
                }
                
                
                //заполняем хаш - 0, точка - 1
                if(intSymbol == 1 || intSymbol == 0) maze[i][j] = intSymbol;                
                
                // огонь будет равен хашу и добавляем огонь в свою точку 
                else if(intSymbol == 3){
                    firePositions[fireNum].x = j; //??????
                    firePositions[fireNum].y = i; //??????
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
        testInp(maze,rows,cols);
        cout << manPosition.x << " " << manPosition.y << "\n";
        cout << firePositions[0].x << " "<< firePositions[0].y <<"\n";
        cout << exitPoints[0].exit.x << " " << exitPoints[0].exit.y << "\n";
        cout << exitPoints[1].exit.x << " " << exitPoints[1].exit.y << "\n";
    } 
}
    