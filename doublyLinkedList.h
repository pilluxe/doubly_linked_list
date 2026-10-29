#include <iostream>
#include <chrono>
#include <type_traits>
#include <string>
#include <sstream>
 
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
    bool data;
 
    linkedList(bool data) {

        this->head = nullptr;
        this->current = nullptr;
        this->tail = nullptr;
        this->data = data;
    }
 
    ~linkedList() {

        clearList(data);
    }
 
    void addBegin(T value) {

        auto start1 = chrono::steady_clock::now();
        Node<T>* newNode = new Node(value);
 
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        auto stop1 = chrono::steady_clock::now();
        double time = chrono::duration<double, milli>(stop1 - start1).count();
        std::cout << "Time to addBegin in milliseconds: " << time << std::endl;
    }
 
    void showFromBegin() {

        Node<T>* traversal = head;

        std::cout << "List from begin: ";
        if constexpr(is_pointer_v<T>){
            while(traversal != nullptr){
                cout << *traversal->value << " ";
                traversal = traversal->next;
            } 
        }
        else{
            while(traversal != nullptr) {
                cout << traversal->value << " ";
                traversal = traversal->next;
            }
        }
        std::cout << std::endl;
    }
 
    void showFromBack() {

        Node<T>* backwards = tail;

        std::cout << "List from back: ";
        if constexpr(is_pointer_v<T>){
            while(backwards != nullptr){
            cout << *backwards->value << " ";
            backwards = backwards->prev;        
            }
        }
        else{
            while (backwards != nullptr) {
                cout << backwards->value << " ";
                backwards = backwards->prev;
                }
            }
        std::cout << std::endl;
    }
 
    void addEnd(T value) {

        auto start1 = chrono::steady_clock::now();
        Node<T>* newNode = new Node<T>(value);

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        auto stop1 = chrono::steady_clock::now();
        double time = chrono::duration<double, milli>(stop1 - start1).count();
        std::cout << "Time to addEnd in milliseconds: " << time << std::endl;
    }

    void removeFront(bool deleteValue){

        auto start1 = chrono::steady_clock::now();
        auto start2 = chrono::steady_clock::now();
        Node<T>* temp = head;

        if(head == nullptr){    //if no elements in list return
            return;
        }
        else if(head == tail){  //if only one elemnt in list delete and set nullptrs
            if(deleteValue){
                if constexpr(is_pointer_v<T>){
                    delete head->value;
                }
            }
            delete head;
            head = nullptr;
            current = nullptr;
            tail = nullptr;
            auto stop2 = chrono::steady_clock::now();
            double time2 = chrono::duration<double, milli>(stop2 - start2).count();
            std::cout << "Time to removeFront in milliseconds: " << time2 << std::endl;
        }
        else{                   //for >2 elements in list copy head, set head to next node then delete connections and delete copy
            head = head->next;
            head->prev = nullptr;
            temp->next = nullptr;
            if(deleteValue){
                if constexpr(is_pointer_v<T>){
                    delete temp->value;
                }
            }
            delete temp;
            current = nullptr;
            auto stop1 = chrono::steady_clock::now();
            double time = chrono::duration<double, milli>(stop1 - start1).count();
            std::cout << "Time to removeFront in milliseconds: " << time << std::endl;
        }
    }

    void removeBack(bool deleteValue){

        auto start1 = chrono::steady_clock::now();
        Node<T>* temp = tail;

        if(tail == nullptr){
            return;
        }
        else if(tail == head){
            if(deleteValue){
                if constexpr(is_pointer_v<T>){
                    delete tail->value;
                }
            }
            delete tail;
            tail = nullptr;
            current = nullptr;
            head = nullptr;
        }
        else{
            tail = tail->prev;
            tail->next = nullptr;
            temp->prev = nullptr;
            if(deleteValue){
                if constexpr(is_pointer_v<T>){
                    delete temp->value;
                }
            }
            delete temp;
            current = nullptr;
            auto stop1 = chrono::steady_clock::now();
            double time = chrono::duration<double, milli>(stop1 - start1).count();
            std::cout << "Time to removeBack in milliseconds: " << time << std::endl;
        }
    }

    void clearList(bool deleteValue){

        while(head != nullptr){
            removeFront(deleteValue);
        }
        cout << "List is empty" << endl;
    }

    Node<T>* findElement(const T& target){

        auto start1 = chrono::steady_clock::now();
        current = head;
        if constexpr(is_pointer_v<T>){
            while(current != nullptr){
                if(*current->value == *target){
                    return current;
                }
                else{
                    current = current->next;
                }
            }
            return nullptr;
        }
        else{
            while(current != nullptr){
                if(current->value == target){
                    auto stop1 = chrono::steady_clock::now();
                    double time = chrono::duration<double, milli>(stop1 - start1).count();
                    std::cout << "Time to findElement in milliseconds: " << time << std::endl;
                    return current;
                }
                else{
                    current = current->next;
                }
            }
            return nullptr;
        }
    }

    void removeCurrent(bool deleteValue){  

        auto start1 = chrono::steady_clock::now();
        Node<T>* temp = current;
        Node<T>* temp2 = current;
        if(current == nullptr){
            return;
        }
        else if(current == head){
            removeFront(deleteValue);
            current = nullptr;
        }
        else if(current == tail){
            removeBack(deleteValue);
            current = nullptr;
        }
        else{
            current = current->next;
            temp = temp->prev;
            temp->next = current;
            current->prev = temp;
            temp2->prev = nullptr;
            temp2->next = nullptr;
            if(deleteValue){
                if constexpr(is_pointer_v<T>){
                    delete temp2->value;
                }
            }
            delete temp2;
            current = nullptr;
            temp = nullptr;
            auto stop1 = chrono::steady_clock::now();
            double time = chrono::duration<double, milli>(stop1 - start1).count();
            std::cout << "Time to removeCurrent in milliseconds: " << time << std::endl;
        }
    }

    bool findAndRemove(T target, bool deleteValue){   

        if(findElement(target)){
            removeCurrent(deleteValue);
            return true;
        }
        else{ return false; }
    }

    void addInOrder(T value){

        remove_pointer_t<T> cur_val;
        remove_pointer_t<T> val;
        current = head;
        if(current == nullptr){                 //if list is empty
            addBegin(value);    
            return;
        }
        if constexpr(is_pointer_v<T>){
            cur_val = *current->value;
            val = *value;
        }
        else{
            cur_val = current->value;
            val = value;
        }
        while(current != nullptr){
            auto start1 = chrono::steady_clock::now();
            if(cur_val > val){                 //if node that we want to add is lower than head
                addBegin(value);
                return;
            }
            else if(cur_val < val){            //if node that we want to add is higher than tail
                if(current->next == nullptr){
                    addEnd(value);
                    return;
                }
                if constexpr(is_pointer_v<T>){
                    current = current->next;
                    cur_val = *current->value;
                }
                else{
                    current = current->next;
                    cur_val = current->value;
                }
                if(cur_val > val){                     //if node that we want to add is somewhere between
                    Node<T>* newNode = new Node<T>(value);
                    Node<T>* temp = current;
                    current = current->prev;
                    current->next = newNode;
                    newNode->prev = current;
                    newNode->next = temp;
                    temp->prev = newNode;
                    current = nullptr;
                    temp = nullptr;
                    auto stop1 = chrono::steady_clock::now();
                    double time = chrono::duration<double, milli>(stop1 - start1).count();
                    std::cout << "Time to addInOrder in milliseconds: " << time << std::endl;
                    return;
                }
            }
            else if(cur_val == val){    
                auto start2 = chrono::steady_clock::now();           //if we want to add node with value that already exists{
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
                    auto stop2 = chrono::steady_clock::now();
                    double time2 = chrono::duration<double, milli>(stop2 - start2).count();
                    std::cout << "Time to addInOrder in milliseconds: " << time2 << std::endl;
                    return;
                }
            }
        }
    }

    void setValue(T newValue){

        if constexpr(is_pointer_v<T>){
            *current->value = *newValue;
        }
        else{
            current->value = newValue;
        }
    }

    bool findAndChange(T target, T newValue){

        if(findElement(target)){
            setValue(newValue);
            return true;
        }
        else{ return false; }
    }

    int countElements(){

        current = head;
        int count = 0;
        while(current!=nullptr){
            count++;
            current = current->next;
        }
        return count;
    }
 
    void findIter(int target){

        remove_pointer_t<T> cur_val;
        auto start1 = chrono::steady_clock::now();
        auto start2 = chrono::steady_clock::now();
        current = head;
        int count = 0;
        if(current == nullptr){
            cout << "List is empty" << endl;
            return;
        }
        else{
            while(current != nullptr){
                if constexpr(is_pointer_v<T>){
                    cur_val = *current->value;
                }
                else{
                    cur_val = current->value;
                }
                if(count == target){
                    cout << cur_val << endl;
                    auto stop2 = chrono::steady_clock::now();
                    double time = chrono::duration<double, milli>(stop2 - start2).count();
                    std::cout << "Time to findIter in milliseconds: " << time << std::endl;
                    return;
                }
                if(current->next == nullptr){
                    cout << "Index out of list" << endl;
                    auto stop1 = chrono::steady_clock::now();
                    double time = chrono::duration<double, milli>(stop1 - start1).count();
                    std::cout << "Time to findIter in milliseconds: " << time << std::endl;
                    return;
                }
                current = current->next;
                count++;
            }
        }
    }

    string listToString(){

        Node<T>* traversal = head;
        ostringstream ss;

        ss << "List has " << countElements() << " elements - ";
        if constexpr(is_pointer_v<T>){
            while(traversal != nullptr){
                ss << *traversal->value << " ";
                traversal = traversal->next;
            } 
        }
        else{
            while(traversal != nullptr) {
                ss << traversal->value << " ";
                traversal = traversal->next;
            }
        }
        return ss.str();
    }

};


struct someObject{
    
    int field1;
    char field2;

    someObject() = default;

    someObject(int field1, char field2) 
                : field1(field1), field2(field2) {}

    bool operator==(const someObject& other) const{     //our key to compare two objects is field1
        return this->field1 == other.field1;
    }

    bool operator<(const someObject& other) const{
        return this->field1 < other.field1;
    }

    bool operator>(const someObject& other) const{
        return this->field1 > other.field1;
    }

    someObject& operator+=(const someObject& other){
        this->field1 += other.field1;
        this->field2 += other.field2;
        return *this; 
    }
};

ostream& operator<<(ostream& os, const someObject& o){
    os << o.field1 << o.field2;
    return os;
}
