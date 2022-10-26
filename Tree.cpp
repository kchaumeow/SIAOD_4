#include <iostream>
#include <vector>
#include <climits>
#include <time.h>
using namespace std;
struct Node{
    int key; // данные узла
    Node *L_node, *R_node;
    Node(int key);
};
Node::Node(int key){
    this->key = key;
    L_node = nullptr;
    R_node = nullptr;
}
class TREE{
    public:
    Node *root; // указатель на вершину дерева
    Node* find_max(Node*curr, int& max, Node* max_node);
    int find_min(Node*curr, int& min);
    Node* Tree(int, Node**);
    void print_tree(Node *w,int l);
    void print_tree_reverse(Node *w,int l);
    int levels(Node* curr, int m);
};
// Построение дерева
Node* TREE::Tree(int n, Node **p){ // p - указатель на корень дерева
    Node* newNode;
    int x, nL, nR;
    newNode = *p;
    if (n == 0) {*p = NULL;}
    else{
        nL = n/2;
        nR = n - nL - 1;
        x = rand() % 51;
        newNode = new Node(x);
        Tree(nL,&((*newNode).L_node));
        Tree(nR,&((*newNode).R_node));
        *p = newNode;
    }
}
int main(){
    setlocale(0,"");
    TREE A;
    int n;
    srand(time(0));
    cout << "Количество вершин: ";
    cin >> n;
    A.Tree(n,&A.root);
    A.print_tree(A.root,0);
    cout << endl << "Количество уровней: " << A.levels(A.root,0) << endl;
    cout << "==============================" << endl;
    A.print_tree_reverse(A.root,0);
    int max = INT_MIN;
    int min = INT_MAX;
    cout << "Максимальное значение в дереве: " << (A.find_max(A.root,max, nullptr))->key << endl;
    cout << "Минимальное значение в дереве: " << A.find_min(A.root,min);
}
// Вывод дерева
void TREE::print_tree (Node *w,int p){
  if  (w != nullptr){
    print_tree ((w->R_node),p+1);
    for  (int i=1; i<=p; i++) cout<<"   ";
    cout<<w->key<<endl;
    print_tree ((w->L_node),p+1);
  }
}
// Вывод дерева справа-налево
void TREE::print_tree_reverse(Node *w,int p){
  if  (w != nullptr){
    print_tree_reverse ((w->L_node),p+1);
    for  (int i=1; i<=p; i++) cout<<"   ";
    cout<<w->key<<endl;
    print_tree_reverse ((w->R_node),p+1);
  }
}
// Подсчёт уровней
int TREE::levels(Node* curr, int l){
    if (curr == nullptr) return 0;
    else l+=1;
    int l1,l2;
    if (levels(curr->L_node, l) > l){
        l1 =levels(curr->L_node, l);
    }
    if (levels(curr->R_node, l) > l){
        l2 =levels(curr->R_node, l);
    }
    return max(l1,l2);
}

Node* TREE::find_max(Node* node, int& max, Node* max_node){ // ПЕРЕДЕЛАТЬ, ИЗ ОТЧЁТА
    vector <Node*> queue;
    queue.push_back(node);
    while (queue.size() > 0){
        Node* first = queue[0];
        queue.erase(queue.begin());
        if (first->key > max){
            max = first->key;
            max_node = first;
        }
        if (first->L_node != nullptr) queue.push_back(first->L_node);
        if (first->R_node != nullptr) queue.push_back(first->R_node);
        
    }
    return max_node;
}

int TREE::find_min(Node*curr, int& min){
    if (curr->L_node != nullptr) find_min(curr->L_node, min);
    if (curr->R_node != nullptr) find_min(curr->R_node, min);
    if (curr->key < min) min = curr->key;
    return min;
}