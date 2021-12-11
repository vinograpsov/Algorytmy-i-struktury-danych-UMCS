#include <iostream>
using namespace std;





int main(){
    unsigned short int arrX;
    unsigned short int arrY;
    cin >> arrY >> arrX;

    unsigned short int** appleTrees = new unsigned short int* [arrY];
    for (int i = 0; i < arrY; i++){
        appleTrees[i] = new unsigned short int[arrX];;
    }

    for(unsigned short int i = 0; i < arrY; i++){
        for(unsigned short int j = 0; j < arrX; j++){
            cin >> appleTrees[i][j]; 
        }
    }

    for(unsigned short int i = 1; i < arrY; i++){
        for(unsigned short int j = 0; j < arrX; j++){
            if(j == 0){
                unsigned short int temp = 0;
                for(unsigned short int k = j; k < 2;k++){
                    if(appleTrees[i-1][k] > temp) temp = appleTrees[i-1][k];
                }
                appleTrees[i][j] += temp;
            }

            else if(j == arrX - 1){
                unsigned short int temp = 0;
                for(unsigned short int k = j - 1 ; k < arrX;k++){
                    if(appleTrees[i-1][k] > temp) temp = appleTrees[i-1][k];
                }
                appleTrees[i][j] += temp;
            }
            else{
                unsigned short int temp = 0;
                for(unsigned short int k = j - 1; k < j + 2;k++){
                    if(appleTrees[i-1][k] > temp) temp = appleTrees[i-1][k];
                    
                }
                appleTrees[i][j] += temp;
            }
        }
    }

    unsigned short int answer[2];
    answer[0] = 0;
    answer[1] = 0;

    for(int i = 0; i < arrX; i++){
        if(appleTrees[arrY - 1][i] > answer[1]){
            answer[0] = i;
            answer[1] = appleTrees[arrY - 1][i];
        }    
    }
    

    for(unsigned short int i = 0; i < arrY; ++i) {
        delete[] appleTrees[i];   
    }
    delete[] appleTrees;


    cout << answer[0] << " " << answer[1];

}