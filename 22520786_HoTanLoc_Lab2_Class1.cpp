#include <iostream>
#include <string>

// Node class representing each node in the linked list
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Stack {
private:
    Node* top; 

public:
    Stack() {
        top = nullptr;
    }
    
    ~Stack() {
        while (!IsEmpty()) {
            Pop();
        }
    }
    
    bool IsEmpty() {
        return top == nullptr;
    }

    void Push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int Pop() {
        if (IsEmpty()) {
            throw std::out_of_range("The stack is empty.");
        }
        Node* temp = top;
        int value = top->data;
        top = top->next;
        delete temp;
        return value;
    }

    bool IsFull(int size) {
        Node* p = top;
        int count = 0;
        while (p != nullptr) {
            count++;
            p = p->next;
        }
        return size == count;
    }

    int Peek() {
        if (IsEmpty()) {
            throw std::out_of_range("The stack is empty.");
        }
        return top->data;
    }

    bool isValidBrackets(const std::string& str) {
        Stack stack; // Create a stack for checking brackets
        bool insideQuotes = false; // Flag to track if we are inside quotes

        for (char ch : str) {
            if (ch == '"') {
                insideQuotes = !insideQuotes; // Toggle the state
            }
            
            if (!insideQuotes) {
                if (ch == '(' || ch == '[') {
                    stack.Push(ch);
                } else if (ch == ')') {
                    if (stack.IsEmpty() || stack.Pop() != '(') {
                        return false; // Invalid if there's no matching opening bracket
                    }
                } else if (ch == ']') {
                    if (stack.IsEmpty() || stack.Pop() != '[') {
                        return false; // Invalid if there's no matching opening bracket
                    }
                }
            }
        }

        return stack.IsEmpty() && !insideQuotes;
    }

    std::string reverseWords(const std::string& str) {
        Stack stack; // Create a stack to reverse characters
        std::string result; // String to store the final result

        for (char ch : str) {
            if (ch == ' ') {
                while (!stack.IsEmpty()) {
                    result += stack.Pop(); // Add characters in reversed order
                }
                result += ' '; // Add the space after the word
            } else {
                stack.Push(ch); // Push characters onto the stack
            }
        }

        // Pop remaining characters from the stack for the last word
        while (!stack.IsEmpty()) {
            result += stack.Pop();
        }

        return result;
    }
};

int main() {
    int choice;
    Stack stack;

    do {
        std::cout << "Enter your choice (1: Push, 2: IsEmpty, 3: IsFull, 4: BracketCheck, 5: ReverseWords, 6: Exit): ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int x;
                std::cout << "Enter elements to push (-1 to stop): ";
                while (std::cin >> x && x != -1) {
                    stack.Push(x);
                }
                break;
            }
            case 2: {
                if (stack.IsEmpty()) {
                    std::cout << "True\n";
                } else {
                    std::cout << "False\n";
                }
                break;
            }
            case 3: {
                int size;
                std::cout << "Enter the size limit: ";
                std::cin >> size;
                if (stack.IsFull(size)) {
                    std::cout << "True\n";
                } else {
                    std::cout << "False\n";
                }
                break;
            }
            case 4: {
                std::string str;
                std::cout << "Enter string to check for brackets: ";
                std::cin >> str;
                if (stack.isValidBrackets(str)) {
                    std::cout << "True\n";
                } else {
                    std::cout << "False\n";
                }
                break;
            }
            case 5: {
                std::string str;
                std::cout << "Enter string to reverse words: ";
                std::cin.ignore();
                std::getline(std::cin, str); // Get the full line for reversing words
                std::string reversed = stack.reverseWords(str);
                std::cout << "Reversed words: " << reversed << "\n";
                break;
            }
            case 6: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    } while (choice != 6);

    return 0;
}
