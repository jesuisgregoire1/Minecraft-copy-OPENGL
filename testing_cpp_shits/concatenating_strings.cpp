#include <iostream>

class Node{
    public:
        int data;
        Node* next;
        Node(){
            this->data = 0;
            this->next = nullptr;
        }
        Node(int data) {
            this->data = data;
            this->next = nullptr;
        }   
};

class LinkedList{
    public:
    Node* head = nullptr;
    Node* current = nullptr;
    void insertAtHead(int data){
        Node* newNode = new Node(data);
        
        if(head == nullptr){
            head = newNode;
            current = head;
            return;
        }
        current->next = newNode;
        current = newNode;
    }
    void print() {
        Node *temp = head;

        // Check for empty list
        if (head == NULL) {
            std :: cout << "List empty" << std :: endl;
            return;
        }

        // Traverse the list
        while (temp != NULL) {
            std :: cout << temp->data << " ";
            temp = temp->next;
        }
    }
    
};

int main() {

    // Creating a LinkedList object
    LinkedList list;

    // Inserting nodes
    // list.insertAtHead(1);
    // list.insertAtHead(2);
    // list.insertAtHead(3);
    // list.insertAtHead(4);

    // std :: cout << "Elements of the list are: ";

    // // Print the list
    // list.print();
    // std :: cout << std :: endl;
    
    return 0;
}