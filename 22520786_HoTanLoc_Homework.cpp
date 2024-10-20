// MSSV: 22520786
// Full Name: Ho Tan Loc
#include <iostream>
using namespace std;

const int MAX_DISKS = 3; // Number of disks

// Function to display the current state of the towers
void displayTowers(int A[], int B[], int C[]) {
    cout << "=========================\n";
    cout << "A Tower: < ";
    for (int i = 0; i < MAX_DISKS; ++i) {
        if (A[i] != 0) cout << A[i] << " ";
    }
    cout << ">\n";

    cout << "B Tower: < ";
    for (int i = 0; i < MAX_DISKS; ++i) {
        if (B[i] != 0) cout << B[i] << " ";
    }
    cout << ">\n";

    cout << "C Tower: < ";
    for (int i = 0; i < MAX_DISKS; ++i) {
        if (C[i] != 0) cout << C[i] << " ";
    }
    cout << ">\n";
    cout << "=========================\n";
}

// Function to move a disk from one tower to another
bool moveDisk(int from[], int to[]) {
    int fromIndex = -1, toIndex = -1;

    // Find the top disk in 'from' tower
    for (int i = MAX_DISKS - 1; i >= 0; --i) {
        if (from[i] != 0) {
            fromIndex = i;
            break;
        }
    }

    // Find the top empty position in 'to' tower
    for (int i = 0; i < MAX_DISKS; ++i) {
        if (to[i] == 0) {
            toIndex = i;
            break;
        }
    }

    // Validate the move
    if (fromIndex == -1 || (toIndex > 0 && to[toIndex - 1] < from[fromIndex])) {
        return false; // Invalid move
    }

    // Move the disk
    to[toIndex] = from[fromIndex];
    from[fromIndex] = 0;
    return true;
}

bool isSolved(int C[]) {
    // Check if all disks are moved to Tower C in the correct order
    for (int i = 0; i < MAX_DISKS; ++i) {
        if (C[i] != MAX_DISKS - i) return false;
    }
    return true;
}

int main() {
    // Towers initialized as arrays
    int A[MAX_DISKS] = { 3, 2, 1 }; // Tower A with all disks
    int B[MAX_DISKS] = { 0 };       // Tower B (empty)
    int C[MAX_DISKS] = { 0 };       // Tower C (empty)

    int choice;
    cout << "========= Tower of Hanoi =========\n";
    cout << "0. Exit\n";
    cout << "1. A -> B\n";
    cout << "2. B -> A\n";
    cout << "3. B -> C\n";
    cout << "4. C -> B\n";
    cout << "5. C -> A\n";
    cout << "6. A -> C\n";

    while (true) {
        displayTowers(A, B, C); // Display current tower status
        cout << "Please input your move: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        // Perform the move based on user's choice
        bool validMove = false;
        switch (choice) {
            case 1: validMove = moveDisk(A, B); break; // A -> B
            case 2: validMove = moveDisk(B, A); break; // B -> A
            case 3: validMove = moveDisk(B, C); break; // B -> C
            case 4: validMove = moveDisk(C, B); break; // C -> B
            case 5: validMove = moveDisk(C, A); break; // C -> A
            case 6: validMove = moveDisk(A, C); break; // A -> C
            default:
                cout << "Invalid input! Try again.\n";
                continue;
        }

        if (!validMove) {
            cout << "Invalid move! Please try again.\n";
            continue;
        }

        // Check if the puzzle is solved
        if (isSolved(C)) {
            cout << "Congratulations! You solved the puzzle!\n";
            displayTowers(A, B, C);
            break;
        }
    }

    return 0;
}
// Question 2
#include <iostream>
#include <vector>
#include <limits> // For clearing input buffer
using namespace std;

class BrowserHistory {
private:
    vector<string> backStack;   // Stores the URLs for back navigation
    vector<string> forwardStack; // Stores the URLs for forward navigation
    string currentURL;           // Stores the currently visited URL

public:
    // Visit a new URL and clear the forward stack
    void visit(const string& url) {
        if (!currentURL.empty()) {
            backStack.push_back(currentURL); // Save current URL to the back stack
        }
        currentURL = url;
        forwardStack.clear(); // Clear forward stack
        cout << "Visited: " << currentURL << endl;
    }

    // Go back to the previous URL
    void back() {
        if (backStack.empty()) {
            cout << "No more back history!" << endl;
            return;
        }
        forwardStack.push_back(currentURL); // Save current URL to the forward stack
        currentURL = backStack.back(); // Retrieve the last URL from the back stack
        backStack.pop_back(); // Remove it from the back stack
        cout << "Back to: " << currentURL << endl;
    }

    // Go forward to the next URL
    void forward() {
        if (forwardStack.empty()) {
            cout << "No more forward history!" << endl;
            return;
        }
        backStack.push_back(currentURL); // Save current URL to the back stack
        currentURL = forwardStack.back(); // Retrieve the last URL from the forward stack
        forwardStack.pop_back(); // Remove it from the forward stack
        cout << "Forward to: " << currentURL << endl;
    }
};

int main() {
    BrowserHistory browser;
    int choice;
    string url;

    do {
        cout << "\nMenu:\n";
        cout << "1. Visit a new URL\n";
        cout << "2. Go back\n";
        cout << "3. Go forward\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input (non-integer)
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number between 1 and 4.\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard input
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter URL: ";
            cin.ignore(); // Clear leftover newline character
            getline(cin, url); // Allow spaces in URLs
            browser.visit(url);
            break;
        case 2:
            browser.back();
            break;
        case 3:
            browser.forward();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
// Question 3
#include <iostream>

using namespace std;

const int MAX_N = 100000; 
int heights[MAX_N];      
int result[MAX_N];       

int main() {
    int n; 
    cout << "Enter the number of people: ";
    cin >> n;
    cout << "Enter the heights of the people: ";
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }
    for (int i = 0; i < n; ++i) {
        result[i] = 0; 
        for (int j = i + 1; j < n; ++j) {
            if (heights[j] < heights[i]) {
                result[i]++;
            }
            else {

                break;
            }
        }
    }

    // Output the result
    cout << "Output: [";
    for (int i = 0; i < n; ++i) {
        cout << result[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}

// Question 4
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        deque<int> q;

        // Traverse prices in reverse order
        for (int i = n; i > 0; --i) {
            // Remove elements from the front that cannot be used
            while (!q.empty() && q.front() > i * 2 + 1) {
                q.pop_front();
            }
            // If we're in the left half of the prices, we can add the value
            if (i <= (n - 1) / 2) {
                prices[i - 1] += prices[q.front() - 1];
            }
            // Remove elements from the back if they are greater than or equal to the current price
            while (!q.empty() && prices[q.back() - 1] >= prices[i - 1]) {
                q.pop_back();
            }
            // Add the current index to the deque
            q.push_back(i);
        }
        // The result will be the first element in the modified prices array
        return prices[0];
    }
};

int main() {
    Solution solution;

    int n; // Number of fruits
    cout << "Enter the number of fruits: ";
    cin >> n;

    vector<int> prices(n); // Vector to store prices of fruits
    cout << "Enter the prices of the fruits: ";
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    // Call the method and output the result
    int result = solution.minimumCoins(prices);
    cout << "Minimum number of coins necessary: " << result << endl;

    return 0;
}
