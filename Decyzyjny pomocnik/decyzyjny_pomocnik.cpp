#include <iostream>
#include <string>
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

Node* find(Node* tree, int i){
    while (tree->next != NULL && tree->next->num != i)
        {
            tree = tree->next;
        }
    return tree;
}


Node* backToStart(Node* tree, int num){
    for(int i = 0; i < num; i++){
        while (tree->prev != NULL){
            tree = tree->prev;
        }
        tree = tree->father;
    }
    return tree;
}

Node *makeTree(Node* tree, string name , int *instructuons, int numOfInstructions){
    int stepDown;
    int i = 0;
    // if(tree->son == NULL){
    //     tree = append(tree,name,num,1);
    //     tree = tree->father;
    // } // доделать 
    

    
    for(i; i < numOfInstructions; i++){
        if(tree->num == 0){
            if(tree->son != NULL) tree = tree->son;
            else {
                if(numOfInstructions == i + 1){
                    tree = append(tree,name,instructuons[i],1);
                    break;
                }
                else
                {
                    tree = append(tree,"X",instructuons[i],1);
                    // i++;
                }
                
            }
        }
        // bool hasSon = false;
        // if(tree->son != NULL && !has) {
        //     tree = tree->son;
        //     hasSon = true;
        // }

        // смотрим код отсюда
        tree = find(tree,instructuons[i]);
            
        
        
        
        
        
        if(tree->next == NULL){
            if(i + 1 == numOfInstructions){
                tree = append(tree,name,instructuons[i],0);
            }
            else{
                // tree = append(tree,"X",instructuons[i],0);
                i++;
                for(;i < numOfInstructions - 2;i++){
                    tree = append(tree,"X",instructuons[i],1);
                    i++;
                }
                tree = append(tree,name,instructuons[i],1);
                i++;
            }
        }
        else{
            tree = tree->next;
            if(i + 1 == numOfInstructions){
                tree->name = name;
                tree->num = instructuons[i];
            }
            else{
                if(tree->son != NULL){
                    tree = tree->son;
                    // i++;
                    // if(i + 1 == numOfInstructions){
                    //     tree->name = name;
                    //     tree->num = instructuons[i];
                    // }
                }
                else{
                    tree = append(tree,"X",instructuons[i+1],1);
                    //i++ ?
                }
            } 
        }
        
    }
    tree = backToStart(tree,numOfInstructions);
    return tree;
}


Node *backToStartPos(struct Node *node,int num){
    for(int i = 0; i < num;i++){
        node = node->prev;
    }
    return node;
}



int main(){
    Node *tree = new Node();
    tree->son = NULL;
    tree->father = NULL;
    tree->name = "start";
    tree->next = NULL;
    tree->prev = NULL;
    tree->num = 0;
    
    int numOfInstructions;
    cin >> numOfInstructions;
    for (int k = 0; k < numOfInstructions; k++){
        
        string instruction;
        cin >> instruction;
        // getline(cin,instruction);

        int numOfTreeInstructions;
        cin >> numOfTreeInstructions;
        int* arrOfTreeInstructions = new int[numOfTreeInstructions];

        for(int l = 0; l < numOfTreeInstructions; l++){
            
            cin >> arrOfTreeInstructions[l];

        }

        tree = makeTree(tree,instruction,arrOfTreeInstructions,numOfTreeInstructions);
    }
    cout << 1;
    

}