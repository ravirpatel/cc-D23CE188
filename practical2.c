#include <iostream>
#include <map>
#include <set>
using namespace std;

// Finite Automaton class
class FiniteAutomaton {
    map<pair<int, char>, int> transitions;
    set<int> acceptingStates;
    int initialState;

public:
    FiniteAutomaton(int start, set<int> accepts) : initialState(start), acceptingStates(accepts) {}

    void addTransition(int from, char symbol, int to) {
        transitions[{from, symbol}] = to;
    }

    bool validateString(const string &input) {
        int currentState = initialState;
        for (char symbol : input) {
            if (transitions.find({currentState, symbol}) == transitions.end())
                return false;
            currentState = transitions[{currentState, symbol}];
        }
        return acceptingStates.find(currentState) != acceptingStates.end();
    }
};

int main() {
    int initialState, numAcceptingStates;
    cout << "Initial State: ";
    cin >> initialState;

    cout << "Number of Accepting States: ";
    cin >> numAcceptingStates;
    set<int> acceptingStates;
    cout << "Accepting States: ";
    for (int i = 0; i < numAcceptingStates; i++) {
        int state;
        cin >> state;
        acceptingStates.insert(state);
    }

    FiniteAutomaton fa(initialState, acceptingStates);

    int fromState, toState;
    char symbol;

    // Transition input
    cout << "Enter transitions (format: fromState symbol toState, type -1 to stop):\n";
    while (true) {
        cin >> fromState;
        if (fromState == -1)
            break;
        cin >> symbol >> toState;
        fa.addTransition(fromState, symbol, toState);
    }

    // Input string to validate
    string inputString;
    cout << "Input string: ";
    cin >> inputString;

    if (fa.validateString(inputString)) {
        cout << "Valid String" << endl;
    } else {
        cout << "Invalid String" << endl;
    }

    return 0;
}
