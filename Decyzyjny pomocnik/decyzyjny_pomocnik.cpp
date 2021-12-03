#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string name;
    int num;
    bool wasPrinted;
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
    new_node->wasPrinted = 0;

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
    while (tree->next != NULL && tree->num != i)
    {
        tree = tree->next;
    }
    return tree;
}


Node* backToStart(Node* tree){
    while(tree->father != NULL || tree->prev !=NULL){
        while (tree->prev != NULL){
            tree = tree->prev;
        }
        tree = tree->father;
    }
    return tree;
}

Node *makeTree(Node* tree, string name , int *instructuons, int numOfInstructions){
    int previousInstruction = instructuons[0];
    if(tree->num == 0 && tree->son != NULL) tree = tree->son; 
    else if(numOfInstructions == 1) tree = append(tree,name,instructuons[0],1);
    else tree = append(tree,"X",instructuons[0],1);


    for(int i = 0;i < numOfInstructions; i++){
        tree = find(tree,instructuons[i]);
        if(tree->num == instructuons[i]){
            if(numOfInstructions == i +1){
                tree->name = name;
                tree->num = instructuons[i];
            }
            else
            {
                if(tree->son != NULL){
                    tree = tree->son;
                }
                else{
                    tree = append(tree,"X",instructuons[i+1],1);
                }
            }
            
        }
        else{
            if(numOfInstructions == i + 1){
                tree = append(tree,name,instructuons[i],0);
            }
            else {
                tree = append(tree,"X",instructuons[i],0);
                tree = append(tree,"X",instructuons[i+1],1);
            }
        }
    }
    tree = backToStart(tree);
    return tree;
}



void postorder(Node* tree){
    if(tree->son != NULL) tree = tree->son;
    while (true) // pridumat uslowije
    {
        if(tree->son != NULL && tree->son->wasPrinted != 1) tree = tree->son; // tut mb lomajetsia 
        else if(tree->next == NULL && tree->wasPrinted == 1){
            while(tree->prev != NULL) tree = tree->prev;
            if(tree->father != 0 || tree->father != NULL) tree = tree->father; // mb tut lomajetsia 
        }
        else {
            cout << tree->name << "\n";
            tree->wasPrinted = 1;
            if(tree->next != NULL) tree = tree->next;
        }
        if(tree->num == 0){
            cout << "Stan spoczynku";
            break;
        }
    }
}


void preorder(Node* tree){
    cout << "Stan spoczynku" << "\n";
    if(tree->son != NULL) tree = tree->son;
    while (true)
    {
        if(tree->wasPrinted != 1) {
            cout << tree->name << "\n";
            tree->wasPrinted = 1;
        }
        if(tree->son != NULL && tree->son->wasPrinted != 1) tree = tree->son;

        else if(tree->next == NULL && tree->wasPrinted == 1){
            while(tree->prev != NULL) tree = tree->prev;
            if(tree->father != 0 || tree->father != NULL) tree = tree->father; // mb tut lomajetsia 
        }

        else {
            if(tree->next != NULL) tree = tree->next;
        }

        if(tree->num == 0){
            break;
        }
    }
    
}



int main(){
    Node *tree = new Node();
    tree->son = NULL;
    tree->father = NULL;
    tree->name = "Stan spoczynku";
    tree->next = NULL;
    tree->prev = NULL;
    tree->num = 0;
    string instruction;
    int numOfInstructions;

    cin >> numOfInstructions;
    for (int k = 0; k < numOfInstructions; k++){
        
        cin.ignore();
        getline(cin,instruction);

        int numOfTreeInstructions;
        cin >> numOfTreeInstructions;
        int* arrOfTreeInstructions = new int[numOfTreeInstructions];

        for(int l = 0; l < numOfTreeInstructions; l++){
            
            cin >> arrOfTreeInstructions[l];

        }
        tree = makeTree(tree,instruction,arrOfTreeInstructions,numOfTreeInstructions);
    }
    
    int outputType;
    cin >> outputType;
    if(outputType == 1){
        preorder(tree);
    }
    else if( outputType == 2){
        postorder(tree);
    }
}