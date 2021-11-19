#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct  TreeNode
{
    double data; // ключ/данные
    TreeNode *left; // указатель на левого потомка
    TreeNode *right; // указатель на правого потомка
};

void levelOrderPrint(TreeNode *root) {
    if (root == NULL)
    {
       return;
    }
    queue<TreeNode *> q; // Создаем очередь
    q.push(root); // Вставляем корень в очередь

    while (!q.empty() ) // пока очередь не пуста
    {
        TreeNode* temp = q.front(); // Берем первый элемент в очереди
        q.pop();  // Удаляем первый элемент в очереди
        cout << temp->data << " "; // Печатаем значение первого элемента в очереди

        if ( temp->left != NULL )
            q.push(temp->left);  // Вставляем  в очередь левого потомка

        if ( temp->right != NULL )
            q.push(temp->right);  // Вставляем  в очередь правого потомка
   }
}


void preorderPrint(TreeNode *root)
{
    if (root == NULL)   // Базовый случай
    {
       return;
    }
    cout << root->data << " ";
    preorderPrint(root->left);   //рекурсивный вызов левого поддерева
    preorderPrint(root->right);  //рекурсивный вызов правого поддерева
}
// Функция печатает значения бинарного дерева поиска в прямом порядке.
// Вместо печати первой инструкцией функции может быть любое действие
// с данным узлом

void inorderPrint(TreeNode *root)
{
    if (root == NULL)   // Базовый случай
    {
       return;
    }
    inorderPrint(root->left);   //рекурсивный вызов левого поддерева
    cout << root->data << " ";
    inorderPrint(root->right);  //рекурсивный вызов правого поддерева
}
// Функция печатает значения бинарного дерева поиска в симметричном порядке.
// То есть в отсортированном порядке

void postorderPrint(TreeNode *root)
{
    if (root == NULL)   // Базовый случай
    {
       return;
    }
    postorderPrint(root->left);   //рекурсивный вызов левого поддерева
    postorderPrint(root->right);  //рекурсивный вызов правого поддерева
    cout << root->data << " ";
}
// Функция печатает значения бинарного дерева поиска в обратном порядке.
// Не путайте обратный и обратноотсортированный (обратный симметричный).

void reverseInorderPrint(TreeNode *root)
{
    if (root == NULL)   // Базовый случай
    {
       return;
    }
    reverseInorderPrint(root->right);  //рекурсивный вызов правого поддерева
    cout << root->data << " ";
    reverseInorderPrint(root->left);   //рекурсивный вызов левого поддерева

}
// Функция печатает значения бинарного дерева поиска в обратном симметричном порядке.
// То есть в обратном отсортированном порядке

//void iterativePreorder(TreeNode *root)
//{
//    if (root == NULL)
//    {
//       return;
//    }
//    stack<TreeNode *> s;  // Создаем стек
//    s.push(root);  // Вставляем корень в стек
//    /* Извлекаем из стека один за другим все элементы.
//       Для каждого извлеченного делаем следующее
//       1) печатаем его
//       2) вставляем в стек правого! потомка
//          (Внимание! стек поменяет порядок выполнения на противоположный!)
//       3) вставляем в стек левого! потомка */
//    while (!s.empty())
//    {
//        // Извлекаем вершину стека и печатаем
//        TreeNode *temp = s.top();
//        s.pop();
//        cout << temp->data << " ";

//        if (temp->right != NULL)
//            s.push(temp->right); // Вставляем в стек правого потомка
//        if (temp->left != NULL)
//            s.push(temp->left);  // Вставляем в стек левого потомка
//    }
//}

void iterativePreorder(TreeNode* root){
    stack<TreeNode*> s;
    while(!s.empty() || root != NULL){
        if(root != NULL){
            cout << root->data << " ";
            if(root->right != NULL){
                s.push(root->right);
            }
            root = root->left;
        }
        else{
            root = s.top();
            s.pop();
        }
    }
}

void iterativeInorder(TreeNode* root){
    stack<TreeNode*> s;
    while(!s.empty() || root != NULL){
        if(root != NULL){
            s.push(root);
            root = root->left;
        }
        else{
            root = s.top();
            s.pop();
            cout << root->data << " ";
            root = root->right;
        }
    }
}

void iterativePostorder(TreeNode* root){
    stack<TreeNode*> s;
    TreeNode* lnp = NULL;
    TreeNode* top = NULL;
    while(!s.empty() || root != NULL){
        if(root != NULL){
            s.push(root);
            root = root->left;
        }
        else{
            top = s.top();
            if(top->right && lnp != top->right)
                root = top->right;
            else{
                s.pop();
                cout << top->data << " ";
                lnp = top;
            }
        }
    }
}

// В симметричном и обратном итеративном обходах просто меняем инструкции
// местами по аналогии с рекурсивными функциями.
int main()
{
    int n = 15;
    TreeNode** tree_array = new TreeNode*[n];
    for(int i = 0; i < n; i++){
        tree_array[i] = new TreeNode;
        tree_array[i]->data = i;
    }
    for(int i = 0; i < n / 2; i++){
        tree_array[i]->left = tree_array[i * 2 + 1];
        tree_array[i]->right = tree_array[i * 2 + 2];
    }
    for(int i = n / 2; i < n; i++){
        tree_array[i]->left = NULL;
        tree_array[i]->right = NULL;
    }

    TreeNode* root = tree_array[0];

    cout << "BFS:" << endl;
    levelOrderPrint(root);

    cout << endl << endl << "pre-order:" << endl;
    preorderPrint(root);

    cout << endl << endl << "in-order:" << endl;
    inorderPrint(root);

    cout << endl << endl << "post-order:" << endl;
    postorderPrint(root);

    cout << endl << endl << "reverse-in-order:" << endl;
    reverseInorderPrint(root);

    cout << endl << endl << "iterative pre-order:" << endl;
    iterativePreorder(root);

    cout << endl << endl << "iterative in-order:" << endl;
    iterativeInorder(root);

    cout << endl << endl << "iterative post-order:" << endl;
    iterativePostorder(root);

    return 0;
}
