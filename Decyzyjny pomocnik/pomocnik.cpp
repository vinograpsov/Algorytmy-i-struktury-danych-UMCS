#include <iostream> 
using namespace std;

class commandClass{
    public:
    int num;
    string nameOfCommand;
    commandClass(int n,string c){
        num = n;
        nameOfCommand = c;
    }
    commandClass(int n){
        num = n;
        nameOfCommand = "X";
    }
};

struct  Node
{
   string name;
   int num;
   Node* next;
   Node* prev;
};

bool hasElementsNodeBool(struct Node *last)
{  
   if (last == NULL) return false;
   return true;
}

struct Node *insertNode(struct Node *last,string name,int num)
{
   if (last != NULL){
      struct Node *temp = new Node;
      temp->name = name;
      temp->num = num;
      temp->next = last->next;
      last->next->prev = temp;
      last->next = temp;
      temp->prev =last;
      last = temp;
      return last;
   }
   else
   {
      struct Node *temp = new Node;
      temp->name = name;
      temp->num = num;last = temp;
      last->next = last;  
      temp->prev = last;
      return last;
   }  
}

Node *deleteNode(Node* head)
{
   if (head == NULL) return head;
   else if(head->next==head)
   {
       delete head;
       head=NULL;
       return head;
   }
   else
   {

      Node *previous = head->next;
      head->prev->next = head->next;
      head->next->prev = head->prev;
      delete head; 
      head = previous;
      return head;
   }
}

// 0 is dad of everething 
// dad must point to brother and first cild  

int main(){
    int numOfCom;
    cin >> numOfCom;
    for(int i = 0; i < numOfCom;i++){
        string command;
        cin >> command;
        int countOfChildren;
        cin >> countOfChildren;
        // возможная имплементация текущего элемента дерева 
        for (int j = 0; j < countOfChildren; j++){
            // make treee and add to lastd child
            int numOfClild;
            cin >> numOfClild; 
            // проверить на то существует ли он или нет 
            // если да и не последний перескочить, если нет и не последний через второй конструктор
            // если да и последний переписать данные, если нет и поелдний создать и переписать через первый конструктор
            // пороверять п овсем элементам 
            
            
            
            
            
            
            
            
            // if (j == countOfChildren - 1){
            //     commandClass lastEl(numOfClild,command);
            // } 

        }
    }
    int kindOfDisplay;
    cin >> kindOfDisplay;
    // show 
}