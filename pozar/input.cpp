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

void testBFS(bool** arr,int rows,int cols){
    for (int i = 0;i < rows;i++){
        for(int j = 0;j < cols;j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}



bool isValid(int row, int col, int ROW, int COL)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};
 

int BFS(/*int mat[][COL]*/ int** mat, Point start, Point exit, int arrRow, int arrCol)
{

    bool** visited = new bool* [arrRow];
    for (int i = 0; i < arrRow; i++){
        visited[i] = new bool[arrCol];;
    }

    for(int i = 0;i < arrRow; i++){
        for(int j = 0;j < arrCol; j++){
            visited[i][j] = false;
        }
    }
 
    visited[start.x][start.y] = true;
    
    queue<queueNode> q;
    
    queueNode s = {start, 0};
    
    q.push(s);  
   
   
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;
        
        if (pt.x == exit.y && pt.y == exit.x) //??????? тут ошибочка поправил но выглядит оч тупо 
            return curr.dist;
  
        q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];
             
            if (isValid(row, col, arrRow,arrCol) && mat[row][col] &&
               !visited[row][col])
            {
                visited[row][col] = true;
                queueNode Adjcell = { {row, col},curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }
    testBFS(visited,arrRow,arrCol);
    return -1;
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

        //записываем все кротчайшие пути мужива
        for (int i = 0; i < exitNum; i++){
            exitPoints[i].manStepCount = BFS(maze,manPosition,exitPoints[i].exit,rows,cols) + 1 ;
        }

        //делаем лабириинт для огня mb errorHere
        for(int i = 0;i < fireNum;i++){
            maze[firePositions[i].x][firePositions[i].y] = 1;
        }

        //записываем все кротчайшие пути огня 
        for(int i = 0;i < exitNum;i++){
            for(int j = 0 ; j < fireNum;j++){
                int temp = BFS(maze,firePositions[j],exitPoints[i].exit,rows,cols) + 1;
                if(exitPoints[i].fireStepCount > temp || exitPoints[i].fireStepCount == -1) exitPoints[i].fireStepCount = temp;
            }
        }

        int shortestWay = -1;
        for(int i = 0; i < exitNum;i++){
            if(exitPoints[i].fireStepCount > exitPoints[i].manStepCount || shortestWay == -1) shortestWay = exitPoints[i].manStepCount;
        }

        answers.insert(answers.end(),shortestWay);

    } 
    // петля которая выводит ответы ечли -1 выписывает нет 
    for(int i = 0; i < numOfTests;i++){
        if(answers[i] == -1) cout << "NIE" << "\n";
        else cout << answers[i] << "\n";
    }
}
    