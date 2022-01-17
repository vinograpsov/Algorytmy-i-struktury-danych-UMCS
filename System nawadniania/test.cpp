#include<iostream>
    using namespace std;
    class Subset_Sum
    {
        public:
        void subsetsum_Backtracking(int* Set, int pos, int sum, int tmpsum, int size, bool & found, int currentAttempt)
        // subsetsum_Backtracking(a, 0, 0, 0, n, f);       
        {
            if ((sum == tmpsum) && (currentAttempt != 0))
                found = true;
            for (int i = pos; i < size; i++)
            {
                currentAttempt += 1;
             if (tmpsum + Set[i] <= sum)
               {
                  tmpsum += Set[i];   
                  // consider next level node (along depth)
                  subsetsum_Backtracking(Set, i + 1, sum, tmpsum, size, found,currentAttempt);
                  tmpsum -= Set[i];
                }
            }
        }
    };
    
    int main()
    {
        int i, n, sum;
        Subset_Sum S;
        cout << "Enter the number of elements in the set" << endl;
        cin >> n;
        int* a = new int[n];
        // int a[n];
        cout << "Enter the values" << endl;
        for(i=0;i<n;i++)
          cin>>a[i];
        cout << "Enter the value of sum" << endl;
        cin >> sum;
        bool f = false;
        S.subsetsum_Backtracking(a, 0, sum, 0, n, f,0);
        if (f)
           cout << "subset with the given sum found" << endl;
        else
           cout << "no required subset found" << endl;   
        return 0;
    }