#include <iostream>
#include <vector>
#include <queue>
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



int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};
 

int BFS(int** mat, Point src, Point dest, int ROW, int COL)
{
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
        return -1;
 
    bool** visited = new bool* [ROW];
        for (int i = 0; i < ROW; i++){
            visited[i] = new bool[COL];;
        }
    
    memset(visited, false, sizeof visited);
     
    visited[src.x][src.y] = true;

    queue<queueNode> q;
     
    queueNode s = {src, 0};
    q.push(s); 
 
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;
 
        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;
 
        q.pop();
 
        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];
             
            if (mat[row][col] && !visited[row][col])
            {
                visited[row][col] = true;
                queueNode Adjcell = { {row, col},curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }

    return -1;
}

// int shortestWay(int** mat, ExitPoint destenation,Point start, int ROW, int COL, bool enterType){
//     if(enterType == 0){
//         int shortest = BFS(mat,start,destenation.exit,ROW,COL);
//     }
//     else
//     {
//         int shortest = BFS(mat,start,destenation.exit,ROW,COL);
//     }
// }



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
                    temp.fireStepCount = -1;
                    temp.manStepCount = -1;
                    exitPoints.insert(exitPoints.end(),temp);
                    exitNum++;
                }
                else if((j == 0 || j == cols - 1) && intSymbol == 1){
                    ExitPoint temp;
                    temp.exit.x = j;
                    temp.exit.y = i;
                    temp.fireStepCount = -1;
                    temp.manStepCount = -1;
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
        
        
        // считаем количество ходов на выход
        for(int i = 0; i < exitNum; i++){
            int manWayLength = BFS(maze,manPosition,exitPoints[i].exit,rows,cols);
            if (exitPoints[i].manStepCount < manWayLength) exitPoints[i].manStepCount = manWayLength;
        }
        for(int exitN = 0; exitN < exitNum; exitN++){
            for (int fireN = 0;fireN < fireNum;fireN++){
                int fireWayLength = BFS(maze,firePositions[fireN],exitPoints[exitN].exit,rows,cols);
                if (exitPoints[exitN].fireStepCount < fireWayLength) exitPoints[exitN].manStepCount = fireWayLength;
            } 
        }


        // находим из всех выходов самый короткий и переписываем в число , число изначально -1
        // переписываем число в ответ 
        


    } 
    // петля которая выводит ответы ечли -1 выписывает нет 
    
}
    