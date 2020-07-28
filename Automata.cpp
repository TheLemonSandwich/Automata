#include<iostream>
using namespace std;

struct Transition
{
	char letter;
	int toState;
	Transition* nextEdge;

	Transition()
	{
		nextEdge = NULL;
		letter = '\0';
		toState = -1;
	}
};

struct State
{
	int stateName;
	char status;
	Transition* head;

	State()
	{
		head = NULL;
		status = '\0';
		stateName = -1;
	}
};

void initializeStates(State*& DFA, const int numOfStates)
{
	for (int i = 0; i < numOfStates; i++)
	{
		DFA[i].stateName = i;
	}
}

void addTransition(State* DFA, const int state, const char letter, const int toState)
{
	Transition* ptrTrans = new Transition;

	ptrTrans->letter = letter;
	ptrTrans->toState = toState;

	ptrTrans->nextEdge = DFA[state].head;
	DFA[state].head = ptrTrans;
}

void displayDFA(const State* DFA, const int numOfStates)
{
	Transition* temp;

	for (int i = 0; i < numOfStates; i++)
	{
		cout << "State: " << DFA[i].stateName << endl;
		cout << "Status: " << DFA[i].status << endl;
		temp = DFA[i].head;
		while (temp != NULL)
		{
			cout << "At " << temp->letter << " transition to: " << temp->toState << endl;
			temp = temp->nextEdge;
		}
		cout << endl;
	}
}

void checkString(State* DFA, const int numOfStates, const string& inputString)
{
	//Will start from state 0 because it is the start state;
	int currentState = 0;
	Transition* temp;

	//Initial start with first state;

	for (int i = 0; inputString[i] != '\0'; i++)
	{
		temp = DFA[currentState].head;
		while (temp != NULL)
		{
			if (temp->letter == inputString[i])
			{
				currentState = temp->toState;
				break;
			}
			temp = temp->nextEdge;
		}
	}

	if (DFA[currentState].status == '+')
	{
		cout << "\nString is ACCEPTED.";
	}
	else
	{
		cout << "\nString is REJECTED.";
	}
}

int main()
{
	int numOfStates;
	int** transitionTable;
	int numOfLetters;
	char* alphabets;
	State* DFA;
	int finalState;
	string inputString;
	int inputFlag;

	cout << "Enter number of states you want in this dfa:";
	cin >> numOfStates;

	DFA = new State[numOfStates];
	initializeStates(DFA, numOfStates);

	//Display states
	cout << "States:" << endl;
	for (int i = 0; i < numOfStates; i++)
	{
		cout << DFA[i].stateName << endl;
	}

	cout << "\nEnter the number of alphabets:";
	cin >> numOfLetters;


	alphabets = new char[numOfLetters];
	for (int i = 0; i < numOfLetters; i++)
	{
		cout << "Enter alphabet " << i + 1 << ":";
		cin >> alphabets[i];
	}

	//Make a transition table and add inputs
	transitionTable = new int* [numOfStates];

	for (int i = 0; i < numOfStates; i++)
	{
		transitionTable[i] = new int[numOfLetters];
	}

	cout << "\nEnter the transtions:\n";

	for (int i = 0; i < numOfStates; i++)
	{
		cout << "State: " << i << endl;
		for (int j = 0; j < numOfLetters; j++)
		{
			cout << "At input " << alphabets[j] << ":";
			cin >> transitionTable[i][j];
		}
		cout << endl;
	}

	//Display tranisiton table
	cout << "State\t";
	for (int i = 0; i < numOfLetters; i++)
	{
		cout << alphabets[i] << "\t";
	}

	cout << endl;

	for (int i = 0; i < numOfStates; i++)
	{
		cout << i;
		for (int j = 0; j < numOfLetters; j++)
		{
			cout << "\t" << transitionTable[i][j];
		}
		cout << endl;
	}

	//Make the first state the start state
	DFA[0].status = '-';
	//Make final states
	cout << "Enter which state you what to be the final state:\n";
	cout << "Press -1 to stop entering the final states\n";

	while (1)
	{
		cin >> finalState;
		if (finalState == -1)
		{
			break;
		}
		else
		{
			DFA[finalState].status = '+';
		}
	}

	//Make a new DFA
	for (int i = 0; i < numOfStates; i++)
	{
		for (int j = 0; j < numOfLetters; j++)
		{
			addTransition(DFA, i, alphabets[numOfLetters - j - 1], transitionTable[i][numOfLetters - j - 1]);
		}
	}

	displayDFA(DFA, numOfStates);
	cout << endl;

	cout << "Enter 1 to enter new string.\nEnter 0 to exit.\n";
	do
	{
		cout << "Enter the input string:";
		cin >> inputString;

		checkString(DFA, numOfStates, inputString);
		cout << "\nDo you want to enter a new string?:";
		cin >> inputFlag;
	} while (inputFlag != 0);
}

