#include <iostream>

using namespace std;

class Node {
    public :
        int data ;
        Node* next ;
        Node(int d):data(d),next(NULL){} // constructor declaration
        ~Node(){cout << "deleting node with data " << data << endl ;}/// destructor declaration
};

class Linked_List {
    private:
        Node* head ;
        int len ;
    public:
        ~Linked_List(){cout << "deleting linked list"<< endl ;}
        Linked_List():head(NULL),len(0){}
        void InsertPos(int value , int pos);
        void push(int value);
        void DeletePos(int pos);
        void print();
        void setHead(Node* newHead);
        void setLength(int val);
        Node* getHead();
        int length();
        int top();
};
void Linked_List::setLength(int val)
{
    this->len = val ;
}
void Linked_List::setHead(Node* newHead)
{
    this->head = newHead ;
}
Node* Linked_List::getHead(){
    return this->head ;
}
int Linked_List::length(){
    return this->len ;
}
int Linked_List::top(){
    return this->head->data ;
}
void Linked_List::DeletePos(int pos){
    Node* prev = NULL ;
    Node* iter = this->head;
    if(pos == 1)
    {
        this->head = iter->next;
        this->len--;
        delete iter ;
        return ;
    }
    while(pos > 1)
    {
        pos--;
        prev = iter ;
        iter = iter->next ;
    }
    if(prev == NULL)
    {
        cout << "Invalid position" << endl ;
        return ;
    }
    prev->next = iter->next ;
    this->len--;
    delete iter ;
}
void Linked_List::InsertPos(int value,int pos){
    Node* x = new Node(value);
    if(this->head == NULL || pos == 1)
    {
        this->len++;
        x->next = this->head ;
        this->head = x ;
        return ;
    }
    Node * iter = this->head ;
    while(pos > 1 && iter!=NULL)
    {
        iter = iter->next;
        pos--;
    }
    if(iter == NULL)
    {
        cout << "Invalid position" << endl ;
        return ;
    }
    Node * next_one = iter->next ;
    iter->next = x ;
    x->next = next_one ;
    this->len++;
    return ;
}
void Linked_List::print(){
    if(this->head == NULL)
    {
        cout << "Empty List " << endl ;
        return ;
    }
    Node* x = this->head ;
    while(x!=NULL)
    {
        cout << x->data << ",";
        x = x->next ;
    }
    cout << endl ;
}
Linked_List Merge_TwoLinked(Linked_List& link1,Linked_List& link2){
    /// my iterator for the result linked list
    Linked_List link3  ;
    Node* it = new Node(-1);
    link3.setHead(it);
    Node* iter1 = link1.getHead();
    Node* iter2 = link2.getHead();
    while(iter1!=NULL || iter2!=NULL)
    {
        if(iter1 == NULL)
        {
            it->next = iter2 ;
            break ;
        }
        else if(iter2==NULL)
        {
            it->next = iter1;
            break ;
        }
        else if(iter1->data < iter2->data)
        {
            it->next = iter1;
            iter1 = iter1->next ;
        }
        else
        {
            it->next = iter2;
            iter2 = iter2->next ;
        }
        it = it->next;
    }
    link3.setHead(link3.getHead()->next);
    link3.setLength(link2.length()+link1.length());
    delete it ;
    return link3;
}
/// you can't make argument constant because they are passed to methods
/// so they can't be sure if they won't change
bool Check_TwoLinked(Linked_List& link1,Linked_List& link2){
    Node* iter1 = (Node*)link1.getHead() ;
    Node* iter2= (Node*)link2.getHead();
    while(iter1 != NULL || iter2 != NULL)
    {
        if(iter1 == NULL || iter2 == NULL)
            return false ;
       if(iter1->data != iter2->data)
            return false ;
        iter1 = iter1->next ;
        iter2 = iter2->next ;
    }
    return true ;
}

int main()
{
    Linked_List x , y;
    x.InsertPos(4,1);
    y.InsertPos(4,1);
    x.print();
    x.InsertPos(3,1);
    y.InsertPos(3,1);
    x.print();
    x.InsertPos(1,1);
    y.InsertPos(1,1);
    x.print();
    x.print();
    y.print();
    Linked_List r = Merge_TwoLinked(x,y);
    r.print();
    return 0;
}
