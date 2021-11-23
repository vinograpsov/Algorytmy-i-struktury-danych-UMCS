#include <iostream>
#include <vector>
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
        vector<ExitPoint> exitPoints;
        int exitNum = 0;
        Point manPosition;
        vector<Point> firePositions; 
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
                    ExitPoint temp;
                    temp.exit.x = j;
                    temp.exit.y = i;
                    exitPoints.insert(exitPoints.end(),temp);
                    exitNum++;
                }
                else if((j == 0 || j == cols - 1) && intSymbol == 1){
                    ExitPoint temp;
                    temp.exit.x = j;
                    temp.exit.y = i;
                    exitPoints.insert(exitPoints.end(),temp);
                    exitNum++;
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
        testInp(maze,rows,cols);
        cout << manPosition.x << " " << manPosition.y << "\n";
        cout << firePositions[0].x << " "<< firePositions[0].y <<"\n";
        for (int i = 0; i < exitNum;i++){
            cout << exitPoints[i].exit.x << " " << exitPoints[i].exit.y << "\n";
        }
    } 
}
    