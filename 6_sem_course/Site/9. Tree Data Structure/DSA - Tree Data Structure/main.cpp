#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct node {
   int data;
   struct node *parent;
   struct node *leftChild;
   struct node *rightChild;
};

struct node *root = NULL;

void insert(int data) {
   struct node *tempNode = new node;
   struct node *current;
   struct node *parent;

   tempNode->data = data;
   tempNode->parent = NULL;
   tempNode->leftChild = NULL;
   tempNode->rightChild = NULL;

   //if tree is empty
   if(root == NULL) {
      root = tempNode;
   } else {
      current = root;
      parent = NULL;

      while(1) {
         parent = current;

         //go to left of the tree
         if(data < parent->data) {
            current = current->leftChild;

            //insert to the left
            if(current == NULL) {
               parent->leftChild = tempNode;
               tempNode->parent = parent;
               return;
            }
         }  //go to right of the tree
         else {
            current = current->rightChild;

            //insert to the right
            if(current == NULL) {
               parent->rightChild = tempNode;
               tempNode->parent = parent;
               return;
            }
         }
      }
   }
}

struct node* search(int data) {
   struct node *current = root;
   printf("Visiting elements: ");

   while(current != NULL && current->data != data) {
      printf("%d ",current->data);

      //go to left tree
      if(current->data > data) {
         current = current->leftChild;
      }
      //else go to right tree
      else {
         current = current->rightChild;
      }
   }

   return current;
}

struct node* min_node(struct node* root){
    while(root != NULL && root->leftChild != NULL)
        root = root->leftChild;
    return root;
}

struct node* max_node(struct node* root){
    while(root != NULL && root->rightChild != NULL)
        root = root->rightChild;
    return root;
}

void delete_(struct node* target){
    if(target->leftChild != NULL && target->rightChild != NULL){
        struct node* local_max = max_node(target->leftChild);
        target->data = local_max->data;
        delete_(local_max);
        return;
    }
    else if(target->leftChild != NULL){
        if(target == target->parent->leftChild)
            target->parent->leftChild = target->leftChild;
        else
            target->parent->rightChild = target->leftChild;
    }
    else if(target->rightChild != NULL){
        if(target == target->parent->leftChild)
            target->parent->leftChild = target->rightChild;
        else
            target->parent->rightChild = target->rightChild;
    }
    else{
        if(target == target->parent->leftChild)
            target->parent->leftChild = NULL;
        else
            target->parent->rightChild = NULL;
    }
    delete target;
}

void delete_(int data){
    struct node* target = search(data);
    if(target != NULL)
        delete_(target);
}

void pre_order_traversal(struct node* root) {
   if(root != NULL) {
      printf("%d ",root->data);
      pre_order_traversal(root->leftChild);
      pre_order_traversal(root->rightChild);
   }
}

void inorder_traversal(struct node* root) {
   if(root != NULL) {
      inorder_traversal(root->leftChild);
      printf("%d ",root->data);
      inorder_traversal(root->rightChild);
   }
}

void post_order_traversal(struct node* root) {
   if(root != NULL) {
      post_order_traversal(root->leftChild);
      post_order_traversal(root->rightChild);
      printf("%d ", root->data);
   }
}

int main() {
   int i;
   int array[7] = { 27, 14, 35, 10, 19, 31, 42 };

//   struct node * temp = search(31);

   for(i = 0; i < 7; i++)
      insert(array[i]);

   struct node* t = min_node(root);
   if(t)
       std::cout << "Min element is: " << t->data << std::endl;

   t = max_node(root->leftChild);
   if(t)
       std::cout << "Max element is: " << t->data << std::endl;


   i = 31;
   struct node* temp = search(i);

   if(temp != NULL) {
      printf("[%d] Element found.", temp->data);
      printf("\n");
   }else {
      printf("[ x ] Element not found (%d).\n", i);
   }

   i = 15;
   temp = search(i);

   if(temp != NULL) {
      printf("[%d] Element found.", temp->data);
      printf("\n");
   }else {
      printf("[ x ] Element not found (%d).\n", i);
   }

   printf("\nPreorder traversal: ");
   pre_order_traversal(root);

   printf("\nInorder traversal: ");
   inorder_traversal(root);

   printf("\nPost order traversal: ");
   post_order_traversal(root);

   i = 14;
   std::cout << "\n\nDelete " << i << std::endl;
//   delete_(root->leftChild->rightChild);
   delete_(14);
   printf("\nPreorder traversal: ");
   pre_order_traversal(root);

   return 0;
}
