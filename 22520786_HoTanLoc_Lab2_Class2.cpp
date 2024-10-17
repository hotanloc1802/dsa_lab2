#include <iostream>
using namespace std;

// Node class representing each node in the queue
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Queue class using linked lists
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue() {
        while (!IsEmpty()) {
            Dequeue();
        }
    }

    // Function to check if the queue is empty
    bool IsEmpty() {
        return front == nullptr;
    }

    // Function to enqueue an element to the queue
    void Enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode; // If the queue was empty
        }
        rear = newNode;
    }

    // Function to dequeue an element from the queue
    int Dequeue() {
        if (IsEmpty()) {
            throw std::out_of_range("Queue is empty.");
        }
        Node* temp = front;
        int value = front->data;
        front = front->next;

        // If the queue becomes empty, also reset rear
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return value;
    }

    // Function to check if the queue is full (not applicable for linked lists)
    bool IsFull() {
        return false; // A linked list based queue is never full unless memory is exhausted
    }
};

// Menu-driven main function
int main() {
    Queue queue;
    int choice;

    do {
        cout << "\nQueue Menu:\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Check if the queue is empty\n";
        cout << "4. Check if the queue is full\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Enter the value to enqueue: ";
                cin >> value;
                queue.Enqueue(value);
                cout << value << " enqueued successfully.\n";
                break;
            }
            case 2: {
                try {
                    int dequeuedValue = queue.Dequeue();
                    cout << dequeuedValue << " dequeued successfully.\n";
                } catch (const std::out_of_range& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << (queue.IsEmpty() ? "Queue is empty." : "Queue is not empty.") << endl;
                break;
            }
            case 4: {
                cout << (queue.IsFull() ? "Queue is full." : "Queue is not full.") << endl;
                break;
            }
            case 5: {
                cout << "Exiting the program.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
/* At FontBath Bank, a solitary teller attends to a lengthy line of customers. New patrons enter
the queue at its rear, and the teller will assist a customer only if they possess all the necessary
documentation. Construct a representation of this queue, noting that 25% of the time, a
customer’s paperwork may be insufficient, resulting in their return to the end of the queue.
Illustrate what the bank’s lobby scenario would resemble over the course of several minutes.*/ 
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For rand() and srand()
#include <unordered_map>  // To track customer failures

using namespace std;

// Node structure for linked list queue
struct Node {
    int data;      // Customer ID
    Node* next;

    Node(int d) : data(d), next(nullptr) {}
};

// Custom Queue Class
class Queue {
private:
    Node* front; // Points to the first customer in the queue
    Node* rear;  // Points to the last customer in the queue

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Enqueue: Add a customer to the end of the queue
    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Dequeue: Remove a customer from the front of the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot dequeue.\n";
            return -1;
        }
        Node* temp = front;
        int data = temp->data;
        front = front->next;

        if (front == nullptr) rear = nullptr;

        delete temp;
        return data;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }
};

// Simulate the bank queue with time tracking and fail limit
double bankSimulation(int queueSize) {
    Queue bankQueue;
    unordered_map<int, int> failCount;  // Track failures for each customer
    int totalCustomers = queueSize;     // Total customers to be served
    double totalTime = 0.0;             // Total time for serving all customers

    srand(time(0));  // Seed for random number generation

    // Add all customers to the queue initially
    for (int i = 1; i <= queueSize; ++i) {
        bankQueue.enqueue(i);
        failCount[i] = 0;  // Initialize fail count for each customer
    }

    // Process the queue until all customers are served
    while (totalCustomers > 0) {
        int customer = bankQueue.dequeue();
        totalTime += 1.0;  // Base processing time for each customer

        // 50% chance of incomplete paperwork
        if (rand() % 100 < 50) {
            failCount[customer]++;  // Increment the customer's fail count

            if (failCount[customer] > 1) {
                // Customer leaves the queue after two failures
                cout << "Customer " << customer << " failed twice and left the queue.\n";
                --totalCustomers;  // Reduce the total customers to be served
            } else {
                // Customer fails and returns to the back of the queue
                cout << "Customer " << customer << " failed. Sent to the back of the queue.\n";
                bankQueue.enqueue(customer);
                totalTime += 0.25;  // Penalty time for failure
            }
        } else {
            cout << "Customer " << customer << " successfully served.\n";
            --totalCustomers;  // Reduce the number of customers left to serve
        }
    }

    return totalTime;
}

int main() {
    int queueSize = 5;  // Number of customers in the queue

    double totalTime = bankSimulation(queueSize);
    cout << "Total time to serve all customers: " << totalTime << " seconds\n";

    return 0;
}
/*As individuals arrive on the dance floor, they should be paired as swiftly as possible: male with
female, male with female, continuing sequentially. In instances where multiple men arrive consecutively, they should be paired in the order of their arrival, and the same applies to multiple
women. A queue of ”spares” should be maintained, consisting of men without corresponding
women or vice versa, and these individuals should be paired as suitable opportunities arise.*/
#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Function to handle dance pairing
void handleArrival(queue<string>& menQueue, queue<string>& womenQueue, string person) {
    if (person == "M") {
        if (!womenQueue.empty()) {
            // Pair the man with the first woman in the queue
            string woman = womenQueue.front();
            womenQueue.pop();
            cout << "Pair formed: Man with Woman\n";
        } else {
            // No woman available, add the man to the men queue
            menQueue.push(person);
            cout << "No woman available, Man added to the queue.\n";
        }
    } else if (person == "W") {
        if (!menQueue.empty()) {
            // Pair the woman with the first man in the queue
            string man = menQueue.front();
            menQueue.pop();
            cout << "Pair formed: Woman with Man\n";
        } else {
            // No man available, add the woman to the women queue
            womenQueue.push(person);
            cout << "No man available, Woman added to the queue.\n";
        }
    }
}

// Function to display remaining spares
void displaySpares(queue<string>& menQueue, queue<string>& womenQueue) {
    cout << "\nRemaining spares on the dance floor:\n";
    cout << "Men waiting: " << menQueue.size() << "\n";
    cout << "Women waiting: " << womenQueue.size() << "\n";
}

int main() {
    queue<string> menQueue;    // Queue to store waiting men
    queue<string> womenQueue;  // Queue to store waiting women

    // Simulating arrival sequence
    string arrivals[] = {"M", "M", "W", "W", "M", "W", "M"};
    int n = sizeof(arrivals) / sizeof(arrivals[0]);

    for (int i = 0; i < n; ++i) {
        cout << "Arrival: " << arrivals[i] << "\n";
        handleArrival(menQueue, womenQueue, arrivals[i]);
    }

    // Display remaining spares
    displaySpares(menQueue, womenQueue);

    return 0;
}
