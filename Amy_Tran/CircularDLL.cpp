#include <iostream>

using namespace std;

//Data Class: This is what goes inside your Node
class Process {
public:
    string processName;
    int totalTime;
    Process (string processName, int totalTime){
        this->processName = processName;
        this->totalTime = totalTime;
        //Fill contructor here
    }
    void updateRunTime(int qTime) {
        //maybe remove parameter?
        this->totalTime-= qTime;

//write method to update totalTime after each quantum cycle.
    }
    void print () {

        cout<< "Process "<< this->processName <<" " <<totalTime<< " seconds \n";
        //write print method to print the name of the process and the time left
    }

    int getTime()
    {
        return this->totalTime;
    }
};
// Node Class: Node for the DoublyLinkedList
template <typename T> class Node {
public:
    T *data;
    Node<T> *next;
    Node<T> *prev;
    Node (T *data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
    void print () {
        data->print ();
    }
};
//CircularDoublyLinkedList Class: Container for Nodes
template <typename T> class CircularDLL {
/*private:*/

public:
    Node<T> *curr;
    int length;
    Node<T> *head;
    Node<T> *tail;
// Constructor
    CircularDLL(T *data) {
        Node<T> *newNode = new Node<T>(data);
        curr = newNode;
        head = newNode;
        tail= newNode;
        length = 1;
//Write constructor for the DLL here
    }
//Destructor
    ~CircularDLL() {
        Node<T> *temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }

        while (temp != head) {
            temp->next = head->next;
            delete head;
            head = temp->next;
        }

        if (temp == head) {
            delete head;
            head = nullptr;
        }

//Write code for destructor here

    }

    void printList() {
        Node<T> *temp = head;
        do {
            temp->print();
            temp = temp->next;
        } while (temp != head);
    }

    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

//Insert a process
    void insertProcess(T* data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = tail = newNode;
            newNode->next = newNode->prev = newNode; // Point to itself, making the list circular
        } else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            tail = newNode; // New node becomes the new tail
        }
        length++;
    }
//write code to insert process here
//Delete a Process
    void deleteProcess(int index) {
        if (index < 0 || index >= length)
            return;

        //  Delete at head
        if (index == 0)
        {
            if (length == 0)
                return;
            Node<T> *curr = head;
            if (length == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                head = head->next;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            delete curr;
            length--;
        }

        else if (index == length - 1)
        {
            if (length == 0)
                return;
            Node<T> *curr = tail;
            if (length == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                tail = tail->prev;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            delete curr;
            length--;
        }
        else{
            Node<T> *curr = get(index);
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            // Node<T> *prev = get(index - 1);
            // Node<T> *temp = prev->next;

            // prev->next = temp->next;
            delete curr;
            length--;
        }
    }

    //method to return the length of the circular doubly linked list

    int LLength()
    {
        return length;
    }



//write code to delete process here

};


int main(){
    //data objects
    Process *p1 = new Process("A", 4);
    Process *p2 = new Process("B", 5);
    Process *p3 = new Process("C", 17);
    Process *p4 = new Process("D", 3);
    Process *p5 = new Process("E", 10);

    //linked list

    CircularDLL<Process> *DLL = new CircularDLL<Process>(p1);
    DLL->insertProcess(p2);
    DLL->insertProcess(p3);
    DLL->insertProcess(p4);
    DLL->insertProcess(p5);


    //DLL->deleteProcess(1);


    //start of operations
    int val;
    string opp;
    int count= 1;
    string newName;
    int newTime;
    int findInd=0;


    int cumiTime=0;
    cout<<"Enter Quantum Time: ";
    cin>>val;
    cout<<"\n";
    cout<<"Prepopulating with processes"<<"\n";
    cout<<endl;
    DLL->printList();


    while(DLL->LLength()>0) {

        cout << "Add new process? (Enter Y/N)";
        cin >> opp;
        cout<<endl;
        if(opp=="Y")
        {
            cout<<"Enter New Process Name: ";
            cin>>newName;
            cout<<endl<<"Enter Total Process Time: ";
            cin>>newTime;
            cout<<endl;
            Process *p6 = new Process(newName, newTime);
            DLL->insertProcess(p6);
            cout<<"Process Added. "<<endl;
            cout<<endl;
            DLL->printList();
        }
        else{
            cumiTime += val;
            cout<<"Running Cycle "<< count<<endl;
            cout<< "After cycle "<< count<< " - "<<cumiTime<< " seconds elapses - state of process is as follows: "<<endl;

            int length = DLL->LLength();




            for (int i = length - 1; i >= 0; i--) {
                DLL->get(i)->data->updateRunTime(val);
                if (DLL->get(i)->data->getTime() <= 0) {
                    DLL->deleteProcess(i);
                    if(DLL->LLength()==0) {
                        cout << endl;
                        cout << "All processes are completed. " << endl;
                    }

                }
            }

            DLL->printList();
            findInd=0;


            count++;
        }

    }



    return 0;

}
