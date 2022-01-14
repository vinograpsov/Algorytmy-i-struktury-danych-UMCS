#include <iostream>
using namespace std;





int main(){ 
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    unsigned short int arrX;
    unsigned short int arrY;
    cin >> arrY >> arrX;
    unsigned short int tempLocal;

    unsigned short int** appleTrees = new unsigned short int* [2];
    for (int i = 0; i < 2; i++){
        appleTrees[i] = new unsigned short int[arrX];;
    }


for(int i = 0; i < arrX;i++){
    cin >> appleTrees[0][i];
}


    for(unsigned short int i = 1; i < arrY; i++){
        for(unsigned short int j = 0; j < arrX; j++){
            cin >> appleTrees[0][j]; 
            if(arrX == 1){
                appleTrees[1][0] = tempLocal + appleTrees[0][0];
            }
            
            else if(j == 0){
                unsigned short int temp = 0;
                for(unsigned short int k = j; k < 2;k++){
                    if(appleTrees[0][k] > temp) temp = appleTrees[0][k];
                }
                appleTrees[1][j] = tempLocal + temp;
            }

            else if(j == arrX - 1){
                unsigned short int temp = 0;
                for(unsigned short int k = j - 1 ; k < arrX;k++){
                    if(appleTrees[0][k] > temp) temp = appleTrees[0][k];
                }
                appleTrees[1][j] = tempLocal + temp;
            }
            else{
                unsigned short int temp = 0;
                for(unsigned short int k = j - 1; k < j + 2;k++){
                    if(appleTrees[0][k] > temp) temp = appleTrees[0][k];
                    
                }
                appleTrees[1][j] = tempLocal + temp;
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
    

    cout << answer[0] << " " << answer[1];

}