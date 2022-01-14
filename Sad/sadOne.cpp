#include <iostream>
using namespace std;





int main(){
    unsigned short int arrX;
    unsigned short int arrY;
    cin >> arrY >> arrX;
    unsigned int globalTemp;


    unsigned short int* appleTrees = new unsigned short int[arrY];

    for(int i = 0; i < arrX; i++){
        cin >> appleTrees[i];
    }

    for(int i = 1; i < arrY; i++){
        for(int j = 0; j < arrX; j++){
            unsigned int localTemp;
            cin >> localTemp;

            if(arrX == 1){
                appleTrees[j] += localTemp;
            }
            else if(j == 0){
                unsigned short int temp = 0;
                for(int k = 0; k < 2; k++){
                    if(temp < appleTrees[k]) temp = appleTrees[k];
                }
                globalTemp = temp + localTemp;

            }
            else if(j == arrX - 1){
                unsigned short int temp = 0;
                for(int k = arrX - 2 ; k < arrX; k++){
                    if(temp < appleTrees[k]) temp = appleTrees[k];                       
                }
                appleTrees[j-1] = globalTemp;
                appleTrees[j] = temp + localTemp;
            }
            else{
                unsigned short int temp = 0;
                for(int k = j - 1; k < j + 2; k++){
                    if(temp < appleTrees[k]) temp = appleTrees[k];
                }
                appleTrees[j-1] = globalTemp;
                globalTemp = temp + localTemp;
            }
            cout << globalTemp << " ";

        }
        cout << "\n";
    }
    
    
    unsigned short int answer[2];
    answer[0] = 0;
    answer[1] = 0;

    for(int i = 0; i < arrX; i++){
        if(appleTrees[i] > answer[1]){
            answer[0] = i;
            answer[1] = appleTrees[i];
        }    
    }
    cout << answer[0] << " " << answer[1];
}