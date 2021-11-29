#include <iostream>
using namespace std;

struct Node
{
    string name;
    int num;
    Node *next = NULL;
    Node *prev = NULL;
    Node *son = NULL;
    Node *father = NULL;
};


Node *append(Node* head_ref, string name, int num, int mode) // with son - 1, without - 0
{
    Node* new_node = new Node();
    

    Node* last = head_ref;

    new_node->name = name;
    new_node->num = num;
    

    if(mode){
        last->son = new_node;

        new_node->father = last;

        return new_node;
    }
    else if(!mode){
        if (head_ref == NULL){
            
            return new_node;
        
        }
        
        else
        {
            
            while (last->next != NULL) last = last->next;

            last->next = new_node;

            new_node->prev = last;

            return new_node;    
        }
        
    }
}


Node *backToStartPos(struct Node *node,int num){
    for(int i = 0; i < num;i++){
        node = node->prev;
    }
    return node;
}



int main(){
    // int numOfInstructions;
    // cin >> numOfInstructions;
    // for (int k = 0; k < numOfInstructions; k++){
        
    //     string instruction;
    //     cin >> instruction;

    //     int numOfTreeInstructions;
    //     cin >> numOfTreeInstructions;
    //     int* arrOfTreeInstructions = new int[numOfTreeInstructions];

    //     for(int l = 0; l < numOfTreeInstructions; l++){
            
    //         cin >> arrOfTreeInstructions[l];

    //     }
    // }
    
    Node* tree = NULL;
    tree = append(tree,"nic",0,0);
    tree = append(tree,"firest son",1,1);
    tree = append(tree,"brother",2,0);
    tree = append(tree,"second son som",3,1);
    tree = tree->father;
    tree = tree->prev;
    tree = append(tree,"firest son som",4,1);
    cout << "ku";
}