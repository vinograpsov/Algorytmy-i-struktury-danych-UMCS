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

void makeFireArr(int** arr,vector<Point> firePoints, int numFirePoints){
    for(int i = 0; i < numFirePoints; i++){
        arr[firePoints[i].y][firePoints[i].x] = 1;
    }
}



bool isValid(int row, int col,int arrY,int arrX)
{
    return (row >= 0) && (row < arrY) &&
           (col >= 0) && (col < arrX);
}
 

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};
 


int BFS(int** mat, Point src, Point dest, int arrY, int arrX)
{
    // check source and destination cell
    // of the matrix have value 1
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
        return -1;
 
    bool** visited = new bool* [arrY];
    for (int i = 0; i < arrY; i++){
        visited[i] = new bool[arrX];;
    }

    for(int i = 0;i < arrY; i++){
        for(int j = 0;j < arrX; j++){
            visited[i][j] = false;
        }
    }

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

            if (isValid(row, col,arrY,arrX) && mat[row][col] &&
               !visited[row][col])
            {
                visited[row][col] = true;
                queueNode Adjcell = { {row, col},curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }
    return -1;
}




void fireShortestWay(vector<Point> firePositions,vector<ExitPoint> exitPoints,int exitNum,int fireNum){

}

void mansShortestWay(Point manPosition,vector<ExitPoint> exitPoints,int exitNum, int** maze,int arrY,int arrX){
    for(int i = 0; i < exitNum; i++){
        exitPoints[i].manStepCount = BFS(maze,manPosition,exitPoints[i].exit,arrY,arrX);
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
                    temp.exit.x = i;
                    temp.exit.y = j;
                    temp.fireStepCount = -1;
                    temp.manStepCount = -1;
                    exitPoints.insert(exitPoints.end(),temp);
                    exitNum++;
                }
                else if((j == 0 || j == arrX - 1) && intSymbol == 1){
                    ExitPoint temp;
                    temp.exit.x = i;
                    temp.exit.y = j;
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
                    temp.x = i;
                    temp.y = j;
                    firePositions.insert(firePositions.end(),temp);
                    fireNum++;
                    maze[i][j] = 0;
                }               
                
                // чувака записываем и принимает его положение за точку 
                else if(intSymbol == 4){
                    manPosition.x = i; // ??????
                    manPosition.y = j; // ??????
                    maze[i][j] = 1;
                }                 
                
   
            }   
        }


        // считаем количество шагов мужика для каждаго выхода 
        for(int i = 0; i < exitNum; i++){
            exitPoints[i].manStepCount = BFS(maze,manPosition,exitPoints[i].exit,arrY,arrX);
        }

        // делаем табличку для огня 
        for(int i = 0;i < fireNum;i++){
            maze[firePositions[i].x][firePositions[i].y] = 1;
        }
        
        // считаем количество шагов для огня 
        for(int i = 0 ; i < exitNum; i++){
            for(int j = 0; j < fireNum; j++){
                int temp = BFS(maze,firePositions[j],exitPoints[i].exit,arrY,arrX);
                if((exitPoints[i].fireStepCount > temp && temp != 1) || exitPoints[i].fireStepCount == -1) exitPoints[i].fireStepCount = temp;
            }
        }
        
        // for(int i = 0; i < exitNum; i++){
        //     cout << exitPoints[i].fireStepCount << " " << exitPoints[i].manStepCount << "\n";
        // }

        int shotrestWay = -1;
        
        
        if(fireNum != 0){
            for(int i = 0; i < exitNum; i++){
                // cout << exitPoints[i].fireStepCount << " " << exitPoints[i].manStepCount << "\n";
                if((exitPoints[i].fireStepCount > exitPoints[i].manStepCount && exitPoints[i].manStepCount != -1 && shotrestWay > exitPoints[i].manStepCount) || (shotrestWay == -1 && exitPoints[i].fireStepCount > exitPoints[i].manStepCount)) shotrestWay = exitPoints[i].manStepCount;
                // cout << shotrestWay << "\n";
            }
        
            answers.insert(answers.end(),shotrestWay);
        }


        
    } 
    // петля которая выводит ответы ечли -1 выписывает нет 
    for(int i = 0; i < numOfTests;i++){
        if(answers[i] == -1) cout << "NIE" << "\n";
        else cout << answers[i] << "\n";
    }
}
    