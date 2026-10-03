#include <iostream>
#include <vector>
#include <string>
#include<limits>
#include<iomanip>

using namespace std; 

class Expense {
private: int id;
	   string description;
	   double amount;

public:
	Expense(int id, string description, double amount) {
		this->id = id;
		this->description = description;
		this->amount = amount;
	}

	int getID() const {
		return id;
	}

	string getDescription() const {
		return description;
	}

	double getAmount() const {
		return amount;
	}

	void setDescription(string NewDescription) {
		description = NewDescription;
	}
	void setAmount(double NewAmount) {
		amount = NewAmount;
	}

	void display() const {
		cout << left << setw(5) << id << setw(25) << description << amount << "\n";
	}
};

class ExpenseManager {
private: 
	vector<Expense> expenses;
	int nextID;

public: 
	ExpenseManager() {
		nextID = 1;
	}


	void AddExpense() {
		string desc;
		double amount;

		cout << " Description: ";
		getline(cin >> ws, desc);


		cout << "Amount : ";
		while (!(cin >> amount) || amount <= 0) {
			cout << "Enter a valid positive amount : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		Expense newExpense(nextID, desc, amount);
		expenses.push_back(newExpense);
		nextID++;
	}


	void viewExpense() {

		if (expenses.empty()) {
			cout << "No expenses recorder. \n";
			return;
		}

		cout << left << setw(5) << "ID" << setw(25) << "Description" << "Amount\n";
		
		for (const Expense& expense : expenses) {
			expense.display();
		}
	}



	void editExpense() {
		int id;
		cout << "Enter the ID of the expense to edit: "; 
		cin >> id;

		for (auto& exp : expenses) {
			if(exp.getID() == id) {
				string newDesc;
				double newAmount;

				cout << "Current description : " << exp.getDescription() << "\n";
				cin.ignore();
				getline(cin, newDesc);
				exp.setDescription(newDesc);


				cout << "Current amount : " << exp.getAmount() << "\n";
				cin >> newAmount;
				exp.setAmount(newAmount);

				cout << "Expense was successfully updated.\n";
				return;
			}
		}
		cout << "Expense with ID" << id << "was not found.\n";
	}

	void DeleteExpense() {
		int id;
		cout << "Enter the ID of the expense to delete: ";
		cin >> id;

		for (auto it = expenses.begin(); it != expenses.end(); ++it) {
			if (it->getID() == id) {
				expenses.erase(it);
				cout << "Expense with ID " << id << " was successfully deleted.\n";
				return;
			}
		}
		cout << "Expense with ID " << id << " was not found.\n";
	}

	void showTotal() {
		double total = 0;
		for (const auto& exp : expenses) {
			total += exp.getAmount();
		}
		cout << "Total expenses: " << total << "\n";
	}
};


int main() {
	ExpenseManager manager;
	int choice;

	do {
		cout << " -- Expense Manager --\n";
		cout << " 1. Add Expense.\n";
		cout << " 2. View Expenses.\n";
		cout << " 3. Edit Expense.\n";
		cout << " 4. Delete Expense.\n";
		cout << " 5. Show Total Expenses.\n";
		cout << "Choose an option (1-5) or 0 to exit: ";
		cin >> choice;


		switch (choice) {
		case 1:  manager.AddExpense(); break;
		case 2:  manager.viewExpense(); break;
		case 3:  manager.editExpense(); break;
		case 4:  manager.DeleteExpense(); break;
		case 5:  manager.showTotal(); break;
		case 0:  cout << "Exiting the program.\n"; break;
		default: cout << "Option not valid. Please choose a number between 0 and 5.\n"; break;

		}
	} while (choice != 0);
	return 0;
}