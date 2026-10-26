#include <iostream>
 
using namespace std;


template<typename T> 
class Node {
    
    public:
    Node<T>* next;
    Node<T>* prev;
    T value;
    
    Node(T value){
        this->next = nullptr;
        this->prev = nullptr;
        this->value = value;
    }
};


template<typename T>
class linkedList {
 
public:
    Node<T>* tail;
    Node<T>* current;
    Node<T>* head;
 
    linkedList() {
        this->head = nullptr;
        this->current = nullptr;
        this->tail = nullptr;
    }
 
    ~linkedList() {
        clearList();
        
    }
 
    void addBegin(T value) {

        Node<T>* newNode = new Node(value);
 
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
 
    void showFromBegin() {

        Node<T>* traversal = head;

        std::cout << "List from begin: ";
        while (traversal != nullptr) {
            cout << traversal->value << " ";
            traversal = traversal->next;
        }
        std::cout << std::endl;
    }
 
    void showFromBack() {

        Node<T>* backwards = tail;

        std::cout << "List from back: ";
        while (backwards != nullptr) {
            cout << backwards->value << " ";
            backwards = backwards->prev;
        }
        std::cout << std::endl;
    }
 
    void addEnd(T value) {

        Node<T>* newNode = new Node<T>(value);

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void removeFront(){

        Node<T>* temp = head;

        if(head == nullptr){    //if no elements in list return
            return;
        }
        else if(head == tail){  //if only one elemnt in list delete and set nullptrs
            delete head;
            head = nullptr;
            current = nullptr;
            tail = nullptr;
        }
        else{                   //for >2 elements in list copy head, set head to next node then delete connections and delete copy
            head = head->next;
            head->prev = nullptr;
            temp->next = nullptr;
            delete temp;
        }
    }

    void removeBack(){

        Node<T>* temp = tail;

        if(tail == nullptr){
            return;
        }
        else if(tail == head){
            delete tail;
            tail = nullptr;
            current = nullptr;
            head = nullptr;
        }
        else{
            tail = tail->prev;
            tail->next = nullptr;
            temp->prev = nullptr;
            delete temp;
        }
    }

    void clearList(){

        while(head != nullptr){
            removeFront();
        }
        cout << "List is empty" << endl;
    }

    Node<T>* findElement(const T& target){

        current = head;
        while(current != nullptr){
            if(current->value == target){
                return current;
            }
            else{
                current = current->next;
            }
        }
        return nullptr;
    }

    void removeCurrent(){  

        Node<T>* temp = current;
        Node<T>* temp2 = current;
        if(current == nullptr){
            return;
        }
        else if(current == head){
            removeFront();
        }
        else if(current == tail){
            removeBack();
        }
        else{
            current = current->next;
            temp = temp->prev;
            temp->next = current;
            current->prev = temp;
            temp2->prev = nullptr;
            temp2->next = nullptr;
            delete temp2;
            current = nullptr;
            temp = nullptr;
        }
    }

    void findAndRemove(T target){   

        findElement(target);
        removeCurrent();
    }

    void addInOrder(T value){

        current = head;
        if(current == nullptr){                 //if list is empty
            addBegin(value);    
            return;
        }
        while(current != nullptr){
            if(current->value > value){                 //if node that we want to add is lower than head
                addBegin(value);
                return;
            }
            else if(current->value < value){            //if node that we want to add is higher than tail
                if(current->next == nullptr){
                    addEnd(value);
                    return;
                }
                current = current->next;
                if(current->value > value){                     //if node that we want to add is somewhere between
                    Node<T>* newNode = new Node<T>(value);
                    Node<T>* temp = current;
                    current = current->prev;
                    current->next = newNode;
                    newNode->prev = current;
                    newNode->next = temp;
                    temp->prev = newNode;
                    current = nullptr;
                    temp = nullptr;
                    return;
                }
            }
            else if(current->value == value){               //if we want to add node with value that already exists{
                if(current->prev == nullptr){               //if node is the same value as head
                    addBegin(value);
                    return;
                }
                else if(current->next == nullptr){          //if node is the same value as tail
                    addEnd(value);
                    return;
                }
                else{                                           //if node is the same value as node somewhere between(in the middle) }
                    Node<T>* newNode = new Node<T>(value);
                    Node<T>* temp = current;
                    current = current->prev;
                    current->next = newNode;
                    newNode->prev = current;
                    newNode->next = temp;
                    temp->prev = newNode;
                    current = nullptr;
                    temp = nullptr;
                    return;
                }
            }
        }
    }

    void setValue(T newValue){

        current->value = newValue;
    }

    void findAndChange(T target, T newValue){

        findElement(target);
        setValue(newValue);
    }

    void countElements(){

        current = head;
        int count = 0;
        while(current!=nullptr){
            count++;
            current = current->next;
        }
        std::cout << "List has " << count << " elements." << std::endl;
    }
 
};

/*template<typename T>
struct someObject{

    int field1;
    char field2;
};*/

 
int main()
{
    linkedList<int>* ll = new linkedList<int>();
 
    //ll->addBegin(6);
    //ll->addBegin(2);
    //ll->addBegin(7);
    //ll->addBegin(2);
    ll->addInOrder(8);
    //ll->addInOrder(6);
    ll->addInOrder(2);
    ll->addInOrder(4);
    ll->addInOrder(4);
    ll->addInOrder(2);
    ll->addInOrder(8);
    //ll->addInOrder(5);
    //ll->addEnd(200);
    //ll->addEnd(1);
    ll->showFromBegin();
    ll->countElements();
    ll->findAndChange(2, 500);
    ll->findAndRemove(4);
    //ll->findElement(4);
    //ll->removeCurrent();
    ll->showFromBegin();
    //ll->removeFront();
    //ll->removeCurrent();
    ll->countElements();
    //ll->showFromBegin();
    //ll->removeBack();
    //cout << endl;
    //ll->clearList();
    //ll->showFromBegin();
    delete ll;
    return 0;
}