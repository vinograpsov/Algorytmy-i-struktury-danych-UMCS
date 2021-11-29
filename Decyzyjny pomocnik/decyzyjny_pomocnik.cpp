#include<iostream>
using namespace std;

struct Sums
{
   int data;
   struct Sums *next;
};

bool hasElementsSumsBool(struct Sums *last)
{
   if (last == NULL) return false;
   return true;
}

struct Sums *insertSums(struct Sums *last, int new_data)
{
   if (last != NULL){
      struct Sums *temp = new Sums;
      temp -> data = new_data;
      temp -> next = last -> next;
      last -> next = temp;
      last = temp;
      return last;
   }
   else
   {
      struct Sums *temp = new Sums;
      temp -> data = new_data;
      last = temp;
      last->next = last;  
      return last;
   }  
}

Sums* deleteSum(Sums* head)
{
   if (head == NULL) return head;
   else if(head->next==head)
   {
       free(head);
       head = NULL;
       return head;
   }
   else
   {

      Sums *previous = head;
      while (previous->next != head)
      {
         previous = previous->next;
      }
      previous->next = head->next;
      delete head;
      head = previous;
      return head;
   }
}








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








struct  NodeOfNodes
{
   Node* dataNode;
   NodeOfNodes* next;
   NodeOfNodes* prev;
};

bool hasElementsNodeOfNodesBool(struct NodeOfNodes *last)
{  
   if (last == NULL) return false;
   return true;
}

struct NodeOfNodes *insertNodeOfNodes(struct NodeOfNodes *last, Node* new_data)
{
   if (last != NULL){
      struct NodeOfNodes *temp = new NodeOfNodes;
      temp -> dataNode = new_data;
      temp->next = last->next;
      last->next->prev = temp;
      last->next = temp;
      temp->prev = last;
      last = temp;
      return last; 

   }
   else
   {
      struct NodeOfNodes *temp = new NodeOfNodes;
      temp -> dataNode = new_data;
      last = temp;
      last->next = last;  
      temp->prev = last;
      return last;
   }  
}

NodeOfNodes *deleteNodeOfNodes(NodeOfNodes* head)
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
      NodeOfNodes *previous = head->next;
      head->prev->next = head->next;
      head->next->prev = head->prev;
      delete head; 
      head = previous;
      return head;
   }
}








struct NodeOfNodes *nodeOfNodesStep(NodeOfNodes* fullNode,int numOfSteps){
   if (numOfSteps >= 0){
      for(int j = 0;j < numOfSteps;j++){
         fullNode = fullNode->next;
      }
   }
   else
   {
      for(int j = 0;j < (numOfSteps * -1);j++){
         fullNode = fullNode->prev;
      }
   }
   return fullNode;
}

struct NodeOfNodes *nodeStep(NodeOfNodes* fullNode,int numOfSteps){
   if (numOfSteps >= 0){
      for(int j = 0;j < numOfSteps;j++){
         fullNode->dataNode = fullNode->dataNode->next;
      }
   }
   else
   {
      for(int j = 0;j < (numOfSteps * -1);j++){
          fullNode->dataNode = fullNode->dataNode->prev;
      }
   }
   return fullNode;
}

struct NodeOfNodes *prepareToOutput(NodeOfNodes* fullNode,int position){
   for(int i = 0;i < position;i++){
      fullNode = fullNode->prev;
   }
   return fullNode;
}

struct NodeOfNodes *backToNormalView(NodeOfNodes* fullNode,int position){
   for(int i = 0;i < position;i++){
      fullNode = fullNode->next;
   }
   return fullNode;
}

int currentSums(NodeOfNodes* fullNode,int *lengthOfNodeOfNodes ){
   int sums = 0;
   for(int i = 0;i < *lengthOfNodeOfNodes ;i++){
      sums += fullNode->dataNode->num;
      fullNode = fullNode->next;
   }
   return sums;
}

int placeOhHeadNode(int placeOfHead, int instruction, NodeOfNodes* fullNode,int *lengthOfNodeOfNodes ){
   placeOfHead += instruction;
   while (true){
      if(placeOfHead > *lengthOfNodeOfNodes ){
         placeOfHead -= *lengthOfNodeOfNodes ;
      }
      else break;       
   }
   return placeOfHead;
}


NodeOfNodes *deleteNullNode(NodeOfNodes* fullNode, int* placeOhHead,int *lengthOfNodeOfNodes ){
   int delNums = 0;
   for(int j = 0; j < *lengthOfNodeOfNodes;j++){
      if(hasElementsNodeBool(fullNode->dataNode) == false){
         if (j < *placeOhHead){

            *placeOhHead = *placeOhHead - 1;
         }
         fullNode = deleteNodeOfNodes(fullNode); 
         delNums++;
         continue;
      }
      fullNode = fullNode->next;  
   }
   *lengthOfNodeOfNodes = *lengthOfNodeOfNodes - delNums;
   return fullNode;
}

bool outputInstruction(NodeOfNodes* fullNode, Sums* sumy, int* placeOhHead,int *lengthOfSums,int *lengthOfNodeOfNodes ){
   int sumNodeEls = currentSums(fullNode,lengthOfNodeOfNodes);
   
   for(int i = 0; i < *lengthOfSums;i++){
      if(sumNodeEls == sumy->data){
         
         cout << sumy->data << " ";
         sumy = deleteSum(sumy);
         *lengthOfSums = *lengthOfSums - 1;
         for(int j = 0; j < *lengthOfNodeOfNodes;j++){
            cout << fullNode->dataNode->name << " ";
            fullNode->dataNode = deleteNode(fullNode->dataNode);
            fullNode = fullNode->next;
         }

         cout << "\n";
         return true;
      }
   sumy = sumy->next;
   }
   return false;
}





void mechanicnyPomocnik(NodeOfNodes* fullNode,Sums* sumy,int numOfInstructions,int instructions[],int *lengthOfSums,int *lengthOfNodeOfNodes ){
   int placeOfHead = 0;
   for(int i = 0; i < numOfInstructions * 2;i++){

      if (hasElementsNodeOfNodesBool(fullNode) == false){
         break; // гдето тут ошиобчка 
      }
      else if(hasElementsSumsBool(sumy) == false)
      {
         break;
      }




      bool cont; 
      fullNode = prepareToOutput(fullNode,placeOfHead);
      cont = outputInstruction(fullNode,sumy,&placeOfHead,lengthOfSums,lengthOfNodeOfNodes);
      fullNode = deleteNullNode(fullNode,&placeOfHead,lengthOfNodeOfNodes);
      fullNode = backToNormalView(fullNode,placeOfHead);
      
      
      fullNode = nodeOfNodesStep(fullNode,instructions[i]);

      placeOfHead = placeOhHeadNode(placeOfHead,instructions[i],fullNode,lengthOfNodeOfNodes);

      i++;
      fullNode = nodeStep(fullNode,instructions[i]); 



      
      fullNode = prepareToOutput(fullNode,placeOfHead);


      while(cont) {
      cont = outputInstruction(fullNode,sumy,&placeOfHead,lengthOfSums,lengthOfNodeOfNodes);
      fullNode = deleteNullNode(fullNode,&placeOfHead,lengthOfNodeOfNodes);
      if(hasElementsNodeOfNodesBool(fullNode) == false) break;
      }
      
      fullNode = backToNormalView(fullNode,placeOfHead);

   }

}



int main()
{
   NodeOfNodes *fullNode = NULL;
   int numOfNodes;
   cin >> numOfNodes;
   for(int i = 0; i < numOfNodes;i++){
      Node *plantNode = NULL;
      int numOfObjInPlantNode;
      cin >> numOfObjInPlantNode;
      string name;
      int num;
      for (int j = 0; j < numOfObjInPlantNode;j++){
         cin >> name >> num;
         plantNode = insertNode(plantNode,name,num);
      }
      plantNode = plantNode->next;
      fullNode = insertNodeOfNodes(fullNode,plantNode);
   }
   fullNode = fullNode->next;
   int numOfSums;
   cin >> numOfSums;
   Sums *sumy = NULL;
   for(int i = 0; i < numOfSums;i++){
      int resultFinal;
      cin >> resultFinal;
      sumy = insertSums(sumy,resultFinal); 
   } 
   sumy = sumy->next;



   int numOfinstructions;
   cin >> numOfinstructions;
   int* instructions = new int[numOfinstructions*2];
   for(int i = 0;i < numOfinstructions*2;i++){
      cin >> instructions[i];
   }
   

   mechanicnyPomocnik(fullNode,sumy,numOfinstructions,instructions,&numOfSums,&numOfNodes);

}
