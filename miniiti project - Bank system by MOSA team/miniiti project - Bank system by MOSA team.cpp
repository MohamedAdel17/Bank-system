#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <ctime>
#include <regex>
#include <windows.h>
using namespace std;

//main menu function
void main_menu();

//login functions
void admin_login();
void employee_login();

//==========================================================================

class Person {
protected:
	string id, first_name, last_name, password;

public:
	//constructors
	Person() {};
	Person(string id, string first_name, string last_name, string password) {
		this->id = id;
		this->first_name = first_name;
		this->last_name = last_name;
		this->password = password;
	}

	//setters
	void set_id(string id) {
		this->id = id;
	}
	void set_first_name(string first_name) {
		this->first_name = first_name;
	}
	void set_last_name(string last_name) {
		this->last_name = last_name;
	}
	void set_password(string password) {
		this->password = password;
	}

	//getters
	string get_id() {
		return id;
	}
	string get_first_name() {
		return first_name;
	}
	string get_last_name() {
		return last_name;
	}
	string get_password() {
		return password;
	}
};

//=======================================================================

class Account : public Person {
private:
	double balance;
	string account_type;
public:
	//constructors
	Account() {};
	Account(string id, string first_name, string last_name, string password, double balance, string account_type) : Person(id, first_name, last_name, password) {
		this->balance = balance;
		this->account_type = account_type;
	}

	//setter
	void set_balance(double balance) {
		this->balance = balance;
	}
	void set_account_type(string account_type) {
		this->account_type = account_type;
	}

	//getter
	double get_balance() {
		return balance;
	}
	string get_account_type() {
		return account_type;
	}

	//methods
	void check_balance(Account account);
	void withdraw(Account &account);
	void deposit(Account &account);
	void transfer_money(Account &account);
	void print_info(Account account);
	void show_account_menu(Account account);
	void show_my_account_transactions(Account account);
};

void Account::check_balance(Account account) {
	system("CLS");
	cout << "\n\nYour current balance is: " << account.get_balance() << endl << endl << endl;
	system("PAUSE");
	system("CLS");
}

void Account::withdraw(Account &account) {
	system("CLS");
	cout << "Please enter the amount you want to withdraw:\n";
	double withdraw_amount;
	do {
		cin >> withdraw_amount;
		if (withdraw_amount < 0) {
			system("CLS");
			cout << "You can't enter a negative value!\n\n";
			cout << "Please enter the amount you want to withdraw:\n";
			continue;
		}
		if (withdraw_amount > account.get_balance()) {
			system("CLS");
			cout << "Invalid transaction!\nInsufficient funds.\n\n";
			cout << "Your account balance is: " << account.get_balance() << endl << endl;
			cout << "Please enter the amount you want to withdraw:\n";
			continue;
		}
		double current_balance = account.get_balance();
		account.set_balance(current_balance -= withdraw_amount);

		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << account.get_balance() << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code

		//transaction history update code start
		string id, month, current_time, from, to, by, type, what_day;
		int day, year;
		double amount;

		ofstream time_temp("time_temp.txt");

		time_t now = time(0);
#pragma warning(suppress : 4996).
		char* dt = ctime(&now); //gives a certain readable time format

		time_temp << dt;
		time_temp.close();

		ofstream transactions_file("transactions.txt", ios::app);
		ifstream transactions("time_temp.txt");
		while (transactions >> what_day >> month >> day >> current_time >> year) {
			transactions_file << account.get_id() << " " << day << " " << month << " " << year << " " << current_time << " " << withdraw_amount << " " << account.get_id() << " " << "N/A" << " " << "Client" << " " << "Withdraw" << endl;

		}
		transactions_file.close();
		transactions.close();
		remove("time_temp.txt");
		//transaction history update code end

		system("CLS");
		cout << "Done!\nYour Current balance is: " << account.get_balance() << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Account::deposit(Account &account) {
	system("CLS");
	double deposit_amount;
	cout << "Please enter the amount you want to deposit:\n";
	do {
		bool input_test = (bool)(cin >> deposit_amount);
		if (input_test == 0 || deposit_amount < 0) {
			system("CLS");
			cout << "Invalid input!\n\n";
			cout << "Please enter the amount you want to deposit:\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		double current_balance = account.get_balance();
		account.set_balance(current_balance += deposit_amount);

		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << account.get_balance() << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code

		//transaction history update code start
		string id, month, current_time, from, to, by, type, what_day;
		int day, year;
		double amount;

		ofstream time_temp("time_temp.txt");

		time_t now = time(0);
#pragma warning(suppress : 4996).
		char* dt = ctime(&now); //gives a certain readable time format

		time_temp << dt;
		time_temp.close();

		ofstream transactions_file("transactions.txt", ios::app);
		ifstream transactions("time_temp.txt");
		while (transactions >> what_day >> month >> day >> current_time >> year) {
			transactions_file << account.get_id() << " " << day << " " << month << " " << year << " " << current_time << " " << deposit_amount << " " << "N/A" << " " << account.get_id() << " " << "Client" << " " << "Deposit" << endl;

		}
		transactions_file.close();
		transactions.close();
		remove("time_temp.txt");
		//transaction history update code end

		system("CLS");
		cout << "Done!\nYour Current balance is: " << account.get_balance() << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Account::transfer_money(Account &account) {
	system("CLS");
	cout << "Please enter the account id you want to transfer to:\n";
	string another_account_id;
	cin >> another_account_id;

	bool id_found = false;
	string id_check;
	string first_name_check, last_name_check, password_check, account_type_check;
	double balance_check;

	ifstream accounts_file("accounts.txt");
	while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
		if (id_check == another_account_id) {
			id_found = true;
		}
	}

	while (id_found == false) {
		system("CLS");
		cout << "Invalid account id!\n\n";
		cout << "Please enter another account id to transfer to:\n";
		cin >> another_account_id;

		string id_check;
		string first_name_check, last_name_check, password_check, account_type_check;
		double balance_check;

		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
			if (id_check == another_account_id) {
				id_found = true;
			}
		}
	}

	cout << "Please enter the amount you want to transfer:\n";
	double transfer_amount;

	do {
		cin >> transfer_amount;
		if (transfer_amount < 0) {
			system("CLS");
			cout << "You can't enter a negative value!\n\n";
			cout << "Please enter the amount you want to transfer:\n";
			continue;
		}
		if (transfer_amount > account.get_balance()) {
			system("CLS");
			cout << "Invalid transaction!\nInsufficient funds.\n\n";
			cout << "Your account balance is: " << account.get_balance() << endl << endl;
			cout << "Please enter the amount you want to transfer:\n";
			continue;
		}
		double current_balance = account.get_balance();
		account.set_balance(current_balance -= transfer_amount);

		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == another_account_id) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << (balance_update += transfer_amount) << " " << account_type_update << endl;
				continue;
			}
			else if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << account.get_balance() << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code

		//transaction history update code start
		string id, month, current_time, from, to, by, type, what_day;
		int day, year;
		double amount;

		ofstream time_temp("time_temp.txt");

		time_t now = time(0);
#pragma warning(suppress : 4996).
		char* dt = ctime(&now); // gives a certain readable time format

		time_temp << dt;
		time_temp.close();

		ofstream transactions_file("transactions.txt", ios::app);
		ifstream transactions("time_temp.txt");
		while (transactions >> what_day >> month >> day >> current_time >> year) {
			transactions_file << account.get_id() << " " << day << " " << month << " " << year << " " << current_time << " " << transfer_amount << " " << account.get_id() << " " << another_account_id << " " << "Client" << " " << "Transfer" << endl;
		}
		transactions_file.close();
		transactions.close();
		remove("time_temp.txt");
		//transaction history update code end

		system("CLS");
		cout << "Done!\nYour Current balance is: " << account.get_balance() << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Account::print_info(Account account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code
	system("PAUSE");
	system("CLS");
}

void Account::show_account_menu(Account account) {
	system("CLS");
	bool test;
	int account_menu_option;
	do {
		test = 1;
		cout << "\n\n\n\tHello " << account.get_first_name() << " " << account.get_last_name() << "!\n"
			<< "\tWhat would you like to do?\n\n" <<
			"\t1. Check my account balance.\n\n" <<
			"\t2. Withdraw.\n\n" <<
			"\t3. Deposit.\n\n" <<
			"\t4. Transfer money.\n\n" <<
			"\t5. Show all my account info.\n\n" <<
			"\t6. Show all my account transactions.\n\n" <<
			"\t7. Log out.\n\t";

		bool input_test = (bool)(cin >> account_menu_option);
		if (input_test == 0) {
			test = input_test;
			system("CLS");
			cout << "\n\n\n\tInvalid input!\n";
			cout << "\tPlease enter a valid value!\n\n\t";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		system("CLS");
		switch (account_menu_option) {
		case 1:
			check_balance(account);
			break;
		case 2:
			withdraw(account);
			break;
		case 3:
			deposit(account);
			break;
		case 4:
			transfer_money(account);
			break;
		case 5:
			print_info(account);
			break;
		case 6:
			show_my_account_transactions(account);
			break;
		case 7:
			main_menu();
			break;
		}
	} while (account_menu_option == 1 || account_menu_option == 2 || account_menu_option == 3 || account_menu_option == 4 || account_menu_option == 5 || account_menu_option == 6 || test == 0);
}

void Account::show_my_account_transactions(Account account) {
	system("CLS");
	string id, month, current_time, from, to, by, type;
	int day, year;
	double amount;

	cout << "Transaction type" << "  |  " << "Amount" << "  |  " << "From" << "  |  " << "To" << "  |  " << "By" << "  |  " << "Day" << "  |  " << "Month" << "  |  " << "Year" << "  |  " << "Time" << endl;
	cout << "______________________________________________________________________________________________" << endl;

	ifstream transactions_file("transactions.txt");
	while (transactions_file >> id >> day >> month >> year >> current_time >> amount >> from >> to >> by >> type) {
		if (account.get_id() == id || account.get_id() == from || account.get_id() == to) {
			cout << endl << type;

			for (int i = 0; i < 22 - type.length(); i++) {
				cout << " ";
			}

			cout << amount;
			string m = to_string(amount);
			for (int i = 0; i < 18 - m.length(); i++) {
				cout << " ";
			}

			cout << from;
			for (int i = 0; i < 9 - from.length(); i++) {
				cout << " ";
			}

			cout << to;
			for (int i = 0; i < 5 - to.length(); i++) {
				cout << " ";
			}

			cout << by;
			for (int i = 0; i < 9 - by.length(); i++) {
				cout << " ";
			}

			cout << day;
			m = to_string(day);
			for (int i = 0; i < 7 - m.length(); i++) {
				cout << " ";
			}

			cout << month;
			for (int i = 0; i < 10 - month.length(); i++) {
				cout << " ";
			}

			cout << year;
			m = to_string(year);
			for (int i = 0; i < 10 - m.length(); i++) {
				cout << " ";
			}

			cout << current_time << endl;
		}
	}
	cout << "______________________________________________________________________________________________" << endl << endl << endl;
	system("PAUSE");
	system("CLS");
}

// account login function
Account account_login();

//===============================================================================

class Employee : public Person {
protected:
	list<Account> accounts_list;

public:
	//constructor
	Employee() {};
	Employee(string id, string first_name, string last_name, string password) :Person(id, first_name, last_name, password) {};

	void create_account();

	void search_account();

	void delete_account();

	void modify_deposit(Account& account);

	void modify_withdraw(Account& account);

	void modify_transfer(Account& account);

	void modify_id(Account& account);

	void modify_name(Account& account);

	void modify_account_type(Account& account);

	void show_account_transactions(Account account);

	void access_account_menu();

	void show_all_accounts();

	void show_employee_menu();

	void show_all_transactions();
};

void Employee::create_account() {
	char x = 'y';
	string id;
	string first_name, last_name;
	string password;
	double balance;
	string account_type;

	system("CLS");
	char repeat = 'y';
	do {
		ofstream accounts_file("accounts.txt", ios::app);

		cout << "Enter account id (id must start with s5, with maximum 3 additional digits):\n";
		cin >> id;

		regex id_regex("s5[[:digit:]+]{1,3}");
		bool match_id = false;
		if (regex_match(id, id_regex))
		{
			match_id = true;
		}

		if (match_id == false) {
			system("CLS");
			continue;
		}

		string new_id = id;
		bool id_exist = false;
		ifstream accounts("accounts.txt");
		while (accounts >> id >> first_name >> last_name >> password >> balance >> account_type) {
			if (id == new_id) {
				id_exist = true;
			}
		}
		id = new_id;
		accounts.close();
		if (id_exist == true) {
			system("CLS");
			cout << "This id is used!\n";
			continue;
		}

		cout << "Enter account's holder first name:\n";
		cin >> first_name;
		cout << "Enter account's holder last name:\n";
		cin >> last_name;

		do {
			cout << "Create account password (One uppercase letter, one lowercase letter, and one digit at least, minimum length:8, maximum length: 10):\n";
			cin >> password;

			regex password_regex("^(?=(?:[^A-Z]*[A-Z]){1,}(?![^A-Z]*[A-Z]))(?=(?:[^a-z]*[a-z]){1,}(?![^a-z]*[a-z]))(?=(?:[^0-9]*[0-9]){1,}(?![^0-9]*[0-9]))[A-Za-z0-9_\.$&@#*-]{8,10}$");
			bool match_password = false;
			if (regex_match(password, password_regex))
			{
				match_password = true;
				break;
			}

			if (match_password == false) {
				continue;
			}
		} while (true);

		cout << "Enter account balance:\n";

		bool test = 1;
		do {
			bool input_test = (bool)(cin >> balance);
			if (input_test == 0 || balance <= 0) {
				system("CLS");
				cout << "Invalid input!\n";
				cout << "Please enter a valid value!\n";
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
		} while (test == 0 || balance <= 0);

		cout << "Select account type:\n";
		do {
			cin >> account_type;
			string account_type_test = account_type;
			for (int i = 0; i < account_type.length(); i++) {
				account_type_test[i] = tolower(account_type[i]);
			}

			if (account_type_test != "current" && account_type_test != "saving") {
				system("CLS");
				cout << "Please enter a valid account type!\n";
				continue;
			}
			else {
				break;
			}
		} while (true);

		for (int i = 0; i < password.length(); i++) {
			password[i] = password[i] + 1;
		}

		accounts_file << id << " " << first_name << " " << last_name << " " << password << " " << balance << " " << account_type << " " << endl;
		accounts_file.close();

		system("CLS");
		cout << "Account created!\n\n";
		cout << "Do you want to create another account?(y/n)\n";
		cin >> x;
		repeat = tolower(x);
		system("CLS");
	} while (repeat == 'y');
	system("CLS");
}

void Employee::search_account() {
	system("CLS");
	do {
		cout << "Enter the account's id:\n";
		string x;
		cin >> x;

		string id;
		string first_name, last_name;
		string password;
		double balance;
		string account_type;
		bool id_found = false;

		ifstream accounts_file("accounts.txt");

		while (accounts_file >> id >> first_name >> last_name >> password >> balance >> account_type) {
			if (id == x) {
				id_found = true;
				system("CLS");
				cout << "Account holder name: " << first_name << " " << last_name << endl
					<< "id: " << id << endl << "Current balance: " << balance << endl
					<< "Account type: " << account_type << endl << endl << endl;
				break;
			}
		}

		if (id_found == false) {
			system("CLS");
			cout << "id not found!\n\n";
			continue;
		}
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::delete_account() {
	system("CLS");
	char x = 'y';
	do {
		string id_delete;
		cout << "Enter the id of the account you want to delete:\n";
		cin >> id_delete;

		bool id_found = false;
		string id;
		string first_name, last_name, password, account_type;
		double balance;

		ofstream otemp("temp.txt", ios::app);

		ifstream accounts_file("accounts.txt");



		while (accounts_file >> id >> first_name >> last_name >> password >> balance >> account_type) {
			if (id == id_delete) {
				id_found = true;
				continue;
			}
			otemp << id << " " << first_name << " " << last_name << " " << password << " " << balance << " " << account_type << endl;
		}
		if (id_found == false) {
			system("CLS");
			cout << "id not found!\n\n";
			continue;
		}
		otemp.close();

		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id >> first_name >> last_name >> password >> balance >> account_type) {
			accounts << id << " " << first_name << " " << last_name << " " << password << " " << balance << " " << account_type << endl;
		}

		accounts.close();
		itemp.close();
		remove("temp.txt");
		cout << "Account deleted!\n\n";
		cout << "Do you want to delete another account?(y/n)\n";
		cin >> x;
		tolower(x);
	} while (x == 'y');
	system("CLS");
}

void Employee::modify_deposit(Account& account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code
	double deposit;
	cout << "Please enter the amount you want to deposit in this account:\n";
	do {
		bool input_test = (bool)(cin >> deposit);
		if (input_test == 0 || deposit < 0) {
			cout << "\nInvalid input!\n";
			cout << "Please enter a valid value!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update, new_balance;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update + deposit << " " << account_type_update << endl;
				new_balance = balance_update + deposit;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code

		//transaction history update code start
		string id, month, current_time, from, to, by, type, what_day;
		int day, year;
		double amount;

		ofstream time_temp("time_temp.txt");

		time_t now = time(0);
#pragma warning(suppress : 4996).
		char* dt = ctime(&now); // gives a certain readable time format

		time_temp << dt;
		time_temp.close();

		ofstream transactions_file("transactions.txt", ios::app);
		ifstream transactions("time_temp.txt");
		while (transactions >> what_day >> month >> day >> current_time >> year) {
			transactions_file << account.get_id() << " " << day << " " << month << " " << year << " " << current_time << " " << deposit << " " << "N/A" << " " << account.get_id() << " " << "Banker" << " " << "Deposit" << endl;

		}
		transactions_file.close();
		transactions.close();
		remove("time_temp.txt");
		//transaction history update code end

		account.set_balance(new_balance);
		system("CLS");
		//start of show account code
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "__________________________________________________________" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "__________________________________________________________" << endl << endl << endl;
		// end of show account code

		cout << "Done!\n\n";
		cout << "Account's new balance: " << account.get_balance() << endl << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::modify_withdraw(Account& account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code

	cout << "Please enter the amount you want to withdraw:\n";
	double withdraw_amount;
	do {
		bool input_test = (bool)(cin >> withdraw_amount);
		if (input_test == 0 || withdraw_amount < 0) {
			cout << "\nInvalid input!\n";
			cout << "Please enter a valid value!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		if (withdraw_amount > account.get_balance()) {
			system("CLS");
			cout << "Invalid transaction!\nInsufficient funds.\n\n";
			cout << "Your account balance is: " << account.get_balance() << endl << endl;
			cout << "Please enter the amount you want to withdraw:\n";
			continue;
		}
		double current_balance = account.get_balance();
		account.set_balance(current_balance -= withdraw_amount);

		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << account.get_balance() << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code

		//transaction history update code start
		string id, month, current_time, from, to, by, type, what_day;
		int day, year;
		double amount;

		ofstream time_temp("time_temp.txt");

		time_t now = time(0);
#pragma warning(suppress : 4996).
		char* dt = ctime(&now); //gives a certain readable time format

		time_temp << dt;
		time_temp.close();

		ofstream transactions_file("transactions.txt", ios::app);
		ifstream transactions("time_temp.txt");
		while (transactions >> what_day >> month >> day >> current_time >> year) {
			transactions_file << account.get_id() << " " << day << " " << month << " " << year << " " << current_time << " " << withdraw_amount << " " << "N/A" << " " << account.get_id() << " " << "Banker" << " " << "Withdraw" << endl;
		}
		transactions_file.close();
		transactions.close();
		remove("time_temp.txt");
		//transaction history update code end

		system("CLS");
		//start of show account code
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "__________________________________________________________" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "__________________________________________________________" << endl << endl << endl;
		// end of show account code

		cout << "Done!\nYour Current balance is: " << account.get_balance() << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::modify_transfer(Account& account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code

	cout << "Please enter the account id you want to transfer to:\n";
	string another_account_id;
	cin >> another_account_id;
	bool id_found = false;

	string id_check;
	string first_name_check, last_name_check, password_check, account_type_check;
	double balance_check;

	ifstream accounts_file("accounts.txt");
	while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
		if (id_check == another_account_id) {
			id_found = true;
		}
	}

	while (id_found == false) {
		cout << "Invalid account id!\n\n";
		cout << "Please enter another account id to transfer to:\n";
		cin >> another_account_id;

		string id_check;
		string first_name_check, last_name_check, password_check, account_type_check;
		double balance_check;

		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
			if (id_check == another_account_id) {
				id_found = true;
			}
		}
	}

	cout << "Please enter the amount you want to transfer:\n";
	double transfer_amount;

	do {
		bool input_test = (bool)(cin >> transfer_amount);
		if (input_test == 0 || transfer_amount < 0) {
			cout << "\nInvalid input!\n";
			cout << "Please enter a valid value!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		if (transfer_amount > account.get_balance()) {
			system("CLS");
			cout << "Invalid transaction!\nInsufficient funds.\n\n";
			cout << "Your account balance is: " << account.get_balance() << endl << endl;
			cout << "Please enter the amount you want to transfer:\n";
			continue;
		}
		double current_balance = account.get_balance();
		account.set_balance(current_balance -= transfer_amount);

		system("CLS");
		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == another_account_id) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << (balance_update += transfer_amount) << " " << account_type_update << endl;
				continue;
			}
			else if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << account.get_balance() << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code

		//transaction history update code start
		string id, month, current_time, from, to, by, type, what_day;
		int day, year;
		double amount;

		ofstream time_temp("time_temp.txt");

		time_t now = time(0);
#pragma warning(suppress : 4996).
		char* dt = ctime(&now); //gives a certain readable time format

		time_temp << dt;
		time_temp.close();

		ofstream transactions_file("transactions.txt", ios::app);
		ifstream transactions("time_temp.txt");
		while (transactions >> what_day >> month >> day >> current_time >> year) {
			transactions_file << account.get_id() << " " << day << " " << month << " " << year << " " << current_time << " " << transfer_amount << " " << account.get_id() << " " << another_account_id << " " << "Banker" << " " << "Transfer" << endl;
		}
		transactions_file.close();
		transactions.close();
		remove("time_temp.txt");
		//transaction history update code end

		//start of show account code
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "__________________________________________________________" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		string m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "__________________________________________________________" << endl << endl << endl;
		// end of show account code

		cout << "Done!\nYour Current balance is: " << account.get_balance() << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::modify_id(Account& account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code

	cout << "Please enter the new id:\n";

	do {
		string new_id;
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		bool id_exist = false;

		cin >> new_id;

		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == new_id) {
				id_exist = true;
			}
		}
		accounts_file.close();
		if (id_exist == true) {
			cout << "\nThis id is used!\n";
			cout << "Please enter another id:\n";
			continue;
		}

		// start of update in a file code
		accounts_file.open("accounts.txt");
		ofstream otemp("temp.txt", ios::app);
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << new_id << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code
		account.set_id(new_id);

		system("CLS");
		//start of show account code
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "__________________________________________________________" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "__________________________________________________________" << endl << endl << endl;
		// end of show account code

		cout << "Account's new id:" << account.get_id() << endl << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::modify_name(Account& account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code

	cout << "Please enter the new first name:\n";
	string new_first_name;
	cin >> new_first_name;

	cout << "Please enter the new last name:\n";
	string new_last_name;
	cin >> new_last_name;

	do {

		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << id_update << " " << new_first_name << " " << new_last_name << " " << password_update << " " << balance_update << " " << account_type_update << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code
		account.set_first_name(new_first_name);
		account.set_last_name(new_last_name);

		system("CLS");
		//start of show account code
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "__________________________________________________________" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		string m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "__________________________________________________________" << endl << endl << endl;
		// end of show account code

		cout << "Account's new holder name: " << account.get_first_name() << " " << account.get_last_name() << endl << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::modify_account_type(Account& account) {
	system("CLS");
	//start of show account code
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;

	cout << endl << account.get_first_name() << " " << account.get_last_name();
	for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
		cout << " ";
	}
	cout << account.get_id();

	for (int i = 0; i < 7 - account.get_id().length(); i++) {
		cout << " ";
	}
	cout << account.get_balance();

	string m = to_string(account.get_balance());
	for (int i = 0; i < 17 - m.length(); i++) {
		cout << " ";
	}
	cout << account.get_account_type() << endl;
	cout << "__________________________________________________________" << endl << endl << endl;
	// end of show account code

	cout << "Please enter the new account type:\n";
	string new_account_type;

	do {
		cin >> new_account_type;
		string account_type_test = new_account_type;
		for (int i = 0; i < new_account_type.length(); i++) {
			account_type_test[i] = tolower(new_account_type[i]);
		}

		if (account_type_test != "current" && account_type_test != "saving") {
			system("CLS");
			cout << "Please enter a valid account type!\n";
			continue;
		}
		else {
			break;
		}
	} while (true);

	do {
		// start of update in a file code
		string id_update;
		string first_name_update, last_name_update, password_update, account_type_update;
		double balance_update;
		ofstream otemp("temp.txt", ios::app);
		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			if (id_update == account.get_id()) {
				otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << new_account_type << endl;
				continue;
			}
			otemp << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		otemp.close();
		ofstream accounts("accounts.txt");
		accounts.clear();
		accounts.close();
		ifstream itemp("temp.txt");
		accounts.open("accounts.txt", ios::app);
		while (itemp >> id_update >> first_name_update >> last_name_update >> password_update >> balance_update >> account_type_update) {
			accounts << id_update << " " << first_name_update << " " << last_name_update << " " << password_update << " " << balance_update << " " << account_type_update << endl;
		}
		accounts.close();
		itemp.close();
		remove("temp.txt");
		// end of update in a file code
		account.set_account_type(new_account_type);

		system("CLS");
		//start of show account code
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "__________________________________________________________" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		string m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "__________________________________________________________" << endl << endl << endl;
		// end of show account code

		cout << "Account type: " << new_account_type << endl << endl;
		break;
	} while (true);
	system("PAUSE");
	system("CLS");
}

void Employee::show_account_transactions(Account account) {
	system("CLS");
	string id, month, current_time, from, to, by, type;
	int day, year;
	double amount;

	cout << "Transaction type" << "  |  " << "Amount" << "  |  " << "From" << "  |  " << "To" << "  |  " << "By" << "  |  " << "Day" << "  |  " << "Month" << "  |  " << "Year" << "  |  " << "Time" << endl;
	cout << "______________________________________________________________________________________________" << endl;

	ifstream transactions_file("transactions.txt");
	while (transactions_file >> id >> day >> month >> year >> current_time >> amount >> from >> to >> by >> type) {
		if (account.get_id() == id || account.get_id() == from || account.get_id() == to) {
			cout << endl << type;

			for (int i = 0; i < 22 - type.length(); i++) {
				cout << " ";
			}

			cout << amount;
			string m = to_string(amount);
			for (int i = 0; i < 18 - m.length(); i++) {
				cout << " ";
			}

			cout << from;
			for (int i = 0; i < 9 - from.length(); i++) {
				cout << " ";
			}

			cout << to;
			for (int i = 0; i < 5 - to.length(); i++) {
				cout << " ";
			}

			cout << by;
			for (int i = 0; i < 9 - by.length(); i++) {
				cout << " ";
			}

			cout << day;
			m = to_string(day);
			for (int i = 0; i < 7 - m.length(); i++) {
				cout << " ";
			}

			cout << month;
			for (int i = 0; i < 10 - month.length(); i++) {
				cout << " ";
			}

			cout << year;
			m = to_string(year);
			for (int i = 0; i < 10 - m.length(); i++) {
				cout << " ";
			}

			cout << current_time << endl;
		}
	}
	cout << "______________________________________________________________________________________________" << endl << endl << endl;
	system("PAUSE");
	system("CLS");
}

void Employee::access_account_menu() {
	system("CLS");
	cout << "\n\n\n\tPlease enter the account id:\n\t";
	string id_entered;
	cin >> id_entered;

	bool id_found = false;

	string id_check;
	string first_name_check, last_name_check, password_check, account_type_check;
	double balance_check;

	ifstream accounts_file("accounts.txt");
	while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
		if (id_check == id_entered) {
			id_found = true;
			break;
		}
	}

	while (id_found == false) {
		system("CLS");
		cout << "\n\n\n\tInvalid account id!\n\n";
		cout << "Please enter another account id:\n\t";
		cin >> id_entered;

		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
			if (id_check == id_entered) {
				id_found = true;
				break;
			}
		}
	}
	Account account(id_entered, first_name_check, last_name_check, password_check, balance_check, account_type_check);

	int menu_option;
	bool test;
	system("CLS");
	do {
		test = 1;
		//start of show account code
		cout << "----------------------------------------------------------" << endl;
		cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
		cout << "----------------------------------------------------------" << endl;

		cout << endl << account.get_first_name() << " " << account.get_last_name();
		for (int i = 0; i < 30 - (account.get_first_name().length() + account.get_last_name().length() + 1); i++) {
			cout << " ";
		}
		cout << account.get_id();

		for (int i = 0; i < 7 - account.get_id().length(); i++) {
			cout << " ";
		}
		cout << account.get_balance();

		string m = to_string(account.get_balance());
		for (int i = 0; i < 17 - m.length(); i++) {
			cout << " ";
		}
		cout << account.get_account_type() << endl;
		cout << "----------------------------------------------------------" << endl << endl << endl;
		// end of show account code

		cout << "\tWhat would you like to do?\n\n" <<
			"\t1. Depoist.\n\n" <<
			"\t2. Withdraw.\n\n" <<
			"\t3. Transfer to another account.\n\n" <<
			"\t4. Show all account's transactions.\n\n" <<
			"\t5. Edit account id.\n\n" <<
			"\t6. Edit account holder name.\n\n" <<
			"\t7. Change account type.\n\n" <<
			"\t8. Back to main menu.\n\n\t";

		bool input_test = (bool)(cin >> menu_option);
		if (input_test == 0) {
			test = input_test;
			system("CLS");
			cout << "\tInvalid input!\n";
			cout << "\tPlease enter a valid value!\n\n\t";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		switch (menu_option) {
		case 1:
			modify_deposit(account);
			break;
		case 2:
			modify_withdraw(account);
			break;
		case 3:
			modify_transfer(account);
			break;
		case 4:
			show_account_transactions(account);
			break;
		case 5:
			modify_id(account);
			break;
		case 6:
			modify_name(account);
			break;
		case 7:
			modify_account_type(account);
			break;
		}
	} while (menu_option == 1 || menu_option == 2 || menu_option == 3 || menu_option == 4 || menu_option == 5 || menu_option == 6 || menu_option == 7 || test == 0);
	system("CLS");
}

void Employee::show_all_accounts() {
	system("CLS");
	string id;
	string first_name, last_name;
	string password;
	double balance;
	string account_type;

	ifstream accounts_file("accounts.txt");
	cout << "Account's holder full name" << " | " << "id" << "  |  " << "Balance" << " | " << "Account Type" << endl;
	cout << "__________________________________________________________" << endl;
	while (accounts_file >> id >> first_name >> last_name >> password >> balance >> account_type) {

		cout << endl << first_name << " " << last_name;
		for (int i = 0; i < 30 - (first_name.length() + last_name.length() + 1); i++) {
			cout << " ";
		}
		cout << id;

		for (int i = 0; i < 7 - id.length(); i++) {
			cout << " ";
		}
		cout << balance;

		string m = to_string(balance);
		for (int i = 0; i < 20 - m.length(); i++) {
			cout << " ";
		}
		cout << account_type << endl;
		cout << "__________________________________________________________" << endl;
	}
	cout << endl << endl;
	system("PAUSE");
	system("CLS");
}

void Employee::show_employee_menu() {
	int banker_menu_option;
	system("CLS");
	bool test;
	do {
		test = 1;
		cout << "Hello!\n" << "What would you like to do?\n\n" <<
			"1. Show all accounts.\n" <<
			"2. Create account.\n" <<
			"3. Delete account.\n" <<
			"4. access account.\n" <<
			"5. Search accounts.\n" <<
			"6. Show all transactions.\n"
			"7. Log out.\n";

		bool input_test = (bool)(cin >> banker_menu_option);
		if (input_test == 0) {
			test = input_test;
			system("CLS");
			cout << "Invalid input!\n";
			cout << "Please enter a valid value!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		switch (banker_menu_option) {
		case 1:
			show_all_accounts();
			break;
		case 2:
			create_account();
			break;
		case 3:
			delete_account();
			break;
		case 4:
			access_account_menu();
			break;
		case 5:
			search_account();
			break;
		case 6:
			show_all_transactions();
			break;
		case 7:
			main_menu();
			break;
		}
	} while (banker_menu_option == 1 || banker_menu_option == 2 || banker_menu_option == 3 || banker_menu_option == 4 || banker_menu_option == 5 || banker_menu_option == 6 || test == 0);
}

void Employee::show_all_transactions() {
	system("CLS");
	string id, month, current_time, from, to, by, type;
	int day, year;
	double amount;

	cout << "Transaction type" << "  |  " << "Amount" << "  |  " << "From" << "  |  " << "To" << "  |  " << "By" << "  |  " << "Day" << "  |  " << "Month" << "  |  " << "Year" << "  |  " << "Time" << endl;
	cout << "______________________________________________________________________________________________" << endl;

	ifstream transactions_file("transactions.txt");
	while (transactions_file >> id >> day >> month >> year >> current_time >> amount >> from >> to >> by >> type) {
		cout << endl << type;

		for (int i = 0; i < 22 - type.length(); i++) {
			cout << " ";
		}

		cout << amount;
		string m = to_string(amount);
		for (int i = 0; i < 18 - m.length(); i++) {
			cout << " ";
		}

		cout << from;
		for (int i = 0; i < 9 - from.length(); i++) {
			cout << " ";
		}

		cout << to;
		for (int i = 0; i < 5 - to.length(); i++) {
			cout << " ";
		}

		cout << by;
		for (int i = 0; i < 9 - by.length(); i++) {
			cout << " ";
		}

		cout << day;
		m = to_string(day);
		for (int i = 0; i < 7 - m.length(); i++) {
			cout << " ";
		}

		cout << month;
		for (int i = 0; i < 10 - month.length(); i++) {
			cout << " ";
		}

		cout << year;
		m = to_string(year);
		for (int i = 0; i < 10 - m.length(); i++) {
			cout << " ";
		}

		cout << current_time << endl;

	}
	cout << "______________________________________________________________________________________________" << endl << endl << endl;
	system("PAUSE");
	system("CLS");
}

//============================================================================

class Admin : public Employee {
private:
	string id;

public:
	void create_employee();
	void search_employee();
	void delete_employee();
	void show_all_employees();
	void show_admin_menu();
	void show_admin_accounts_menu();
	void show_admin_employees_menu();
};

void Admin::create_employee() {
	system("CLS");
	string id, first_name, last_name;
	string password;
	char x = 'y';
	char repeat = 'y';
	do {
		ofstream employees_file("employees.txt", ios::app);

		cout << "Enter employee's id (must start with m5, with maximum 3 additional digits):\n";
		cin >> id;

		regex id_regex("m5[[:digit:]+]{1,3}");
		bool match_id = false;
		if (regex_match(id, id_regex))
		{
			match_id = true;
		}

		if (match_id == false) {
			system("CLS");
			continue;
		}

		string new_id = id;
		bool id_exist = false;
		ifstream employees("employees.txt");
		while (employees >> id >> first_name >> last_name >> password) {
			if (id == new_id) {
				id_exist = true;
			}
		}
		id = new_id;
		employees.close();
		if (id_exist == true) {
			system("CLS");
			cout << "This id is used!\n";
			continue;
		}

		cout << "Enter employee's first name:\n";
		cin >> first_name;
		cout << "Enter employee's last name:\n";
		cin >> last_name;


		do {
			cout << "Create employee password:\n";
			cout << "(One uppercase letter, one lowercase letter, and one digit at least, minimum length:8, maximum length: 10)\n";
			cin >> password;

			regex password_regex("^(?=(?:[^A-Z]*[A-Z]){1,}(?![^A-Z]*[A-Z]))(?=(?:[^a-z]*[a-z]){1,}(?![^a-z]*[a-z]))(?=(?:[^0-9]*[0-9]){1,}(?![^0-9]*[0-9]))[A-Za-z0-9_\.$&@#*-]{8,10}$");
			bool match_password = false;
			if (regex_match(password, password_regex))
			{
				match_password = true;
				break;
			}

			if (match_password == false) {
				continue;
			}
		} while (true);

		//encrption code
		for (int i = 0; i < password.length(); i++) {
			password[i] = password[i] + 1;
		}

		//write to the file code
		employees_file << id << " " << first_name << " " << last_name << " " << password << " " << endl;
		employees_file.close();

		system("CLS");
		cout << "Employee create!\n\n";
		cout << "Do you want to create another employee?(y/n)\n";
		cin >> x;
		repeat = tolower(x);
	} while (x == 'y');
	system("CLS");
}

void Admin::search_employee() {
	system("CLS");
	bool id_found = false;
	do {
		cout << "Enter the employee's id:\n";
		string id_entered;
		cin >> id_entered;
		string id;
		string first_name, last_name;
		string password;

		ifstream accounts_file("employees.txt");

		while (accounts_file >> id >> first_name >> last_name >> password) {
			if (id == id_entered) {
				id_found = true;
				cout << "\n\nEmployee name: " << first_name << " " << last_name << endl
					<< "\nid: " << id << endl << endl << endl;
				break;
			}
		}

		while (id_found == false) {
			system("CLS");
			cout << "Not found!\n\n";

			cout << "Do you want to search for another employee?(y/n)\n";
			char test_repeat;
			cin >> test_repeat;
			tolower(test_repeat);

			if (test_repeat == 'y') {
				id_found = false;
				break;
			}
			else {
				id_found = true;
				break;
			}
		}
	} while (!id_found);

	system("PAUSE");
	system("CLS");
}

void Admin::delete_employee() {
	system("CLS");
	char x = 'y';
	do {
		int id_delete;
		cout << "Enter the id of the employee you want to remove:\n";
		cin >> id_delete;

		bool id_found = false;
		int id;
		string first_name, last_name, password;

		ofstream otemp_employee("temp_employees.txt", ios::app);


		ifstream employees_file("employees.txt");


		while (employees_file >> id >> first_name >> last_name >> password) {
			if (id == id_delete) {
				id_found = true;
				continue;
			}
			otemp_employee << id << " " << first_name << " " << last_name << " " << password << endl;
		}

		if (id_found == false) {
			system("CLS");
			cout << "id not found!\n\n";
			continue;
		}
		otemp_employee.close();

		ofstream employees("employees.txt");
		employees.clear();
		employees.close();
		ifstream itemp_employees("temp_employees.txt");
		employees.open("employees.txt", ios::app);
		while (itemp_employees >> id >> first_name >> last_name >> password) {
			employees << id << " " << first_name << " " << last_name << " " << password << endl;
		}

		employees.close();
		itemp_employees.close();
		remove("temp_employees.txt");
		cout << "Employee deleted!\n\n";
		cout << "Do you want to delete another employee?(y/n)\n";
		cin >> x;
		tolower(x);
	} while (x == 'y');
	system("CLS");
}

void Admin::show_all_employees() {
	system("CLS");
	string id;
	string first_name, last_name;
	string password;

	ifstream employees_file("employees.txt");
	cout << "Employee's full name" << "    |    " << "id" << endl;
	cout << "__________________________________________________________" << endl;
	while (employees_file >> id >> first_name >> last_name >> password) {

		cout << endl << first_name << " " << last_name;
		for (int i = 0; i < 29 - (first_name.length() + last_name.length() + 1); i++) {
			cout << " ";
		}
		cout << id << endl;

		cout << "__________________________________________________________" << endl;
	}
	cout << endl << endl;
	system("PAUSE");
	system("CLS");
}

void Admin::show_admin_menu() {
	int banker_menu_option;
	bool test;
	system("CLS");
	do {
		test = 1;
		cout << "\n\n\n\tHello!\n" << "\n\tWhat would you like to access?\n\n" <<
			"\n\n\n\t1. Accounts.\n" <<
			"\n\n\n\t2. Employees.\n" <<
			"\n\n\n\t3. Logout.\n\t";

		bool input_test = (bool)(cin >> banker_menu_option);
		if (input_test == 0) {
			system("CLS");
			cout << "\n\n\n\tInvalid input!\n";
			cout << "\tPlease enter a valid value!\n\n";
			cin.clear();
			cin.ignore(1000, '\n');
			test = input_test;
			continue;
		}

		switch (banker_menu_option) {
		case 1:
			show_admin_accounts_menu();
			break;
		case 2:
			show_admin_employees_menu();
			break;
		case 3:
			main_menu();
			break;
		}
	} while (banker_menu_option == 1 || banker_menu_option == 2 || test == 0);
}

void Admin::show_admin_accounts_menu() {
	int banker_menu_option;
	system("CLS");
	bool test;
	do {
		test = 1;
		cout << "\n\n\n\tHello!\n" << "\tWhat would you like to do?\n\n" <<
			"\t1. Show all accounts.\n\n" <<
			"\t2. Create account.\n\n" <<
			"\t3. Delete account.\n\n" <<
			"\t4. access account.\n\n" <<
			"\t5. Search accounts.\n\n" <<
			"\t6. Show all transaction.\n\n" <<
			"\t7. Back to main menu.\n\n\t";

		bool input_test = (bool)(cin >> banker_menu_option);
		if (input_test == 0) {
			test = input_test;
			system("CLS");
			cout << "\n\n\n\tInvalid input!\n";
			cout << "\tPlease enter a valid value!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		switch (banker_menu_option) {
		case 1:
			show_all_accounts();
			break;
		case 2:
			create_account();
			break;
		case 3:
			delete_account();
			break;
		case 4:
			access_account_menu();
			break;
		case 5:
			search_account();
			break;
		case 6:
			show_all_transactions();
			break;
		case 7:
			show_admin_menu();
			break;
		}
	} while (banker_menu_option == 1 || banker_menu_option == 2 || banker_menu_option == 3 || banker_menu_option == 4 || banker_menu_option == 5 || banker_menu_option == 6 || test == 0);
}

void Admin::show_admin_employees_menu() {
	int banker_menu_option;
	system("CLS");
	bool test;
	do {
		test = 1;
		cout << "\n\n\n\tHello!\n" << "\tWhat would you like to do?\n\n" <<
			"\t1. Show all employees.\n\n" <<
			"\t2. Create employee.\n\n" <<
			"\t3. Delete employee.\n\n" <<
			"\t4. Search employees.\n\n" <<
			"\t5. Back to main menu.\n\n\t";

		bool input_test = (bool)(cin >> banker_menu_option);
		if (input_test == 0) {
			test = input_test;
			system("CLS");
			cout << "\n\n\n\tInvalid input!\n";
			cout << "\tPlease enter a valid value!\n\t";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		switch (banker_menu_option) {
		case 1:
			show_all_employees();
			break;
		case 2:
			create_employee();
			break;
		case 3:
			delete_employee();
			break;
		case 4:
			search_employee();
			break;
		case 5:
			show_admin_menu();
			break;
		}
	} while (banker_menu_option == 1 || banker_menu_option == 2 || banker_menu_option == 3 || banker_menu_option == 4 || test == 0);
}
//=======================================================================

//create admin function
//used only one time to create admin file
void create_admin() {
	ofstream admin_file("admin.txt");
	int id = 1;
	string password = "admin123";

	admin_file << id << " " << password;
	admin_file.close();
}

void start_screen() {
	system("color 0E");
	cout << endl << endl << endl << endl;
	cout << "\t\t#               #   # # # #   #         # # # #   # # # # #       #       #       # # # #\n";
	cout << "\t\t #             #    #         #         #         #       #      #  #   #  #      #      \n";
	cout << "\t\t  #     #     #     # # # #   #         #         #       #     #     #     #     # # # #\n";
	cout << "\t\t   #  #   #  #      #         #         #         #       #    #             #    #      \n";
	cout << "\t\t    #       #       # # # #   # # # #   # # # #   # # # # #   #               #   # # # #\n";
	cout << "\n\t\t                                     To MOSA bank\n";
	Sleep(3000);
	system("CLS");
}

int main()
{
	start_screen();
	main_menu();
}


void main_menu() {
	system("CLS");
	system("color  0E");
	int login_type;
	while (true) {

		cout << "\n\n\n\tPlease choose how you would like to login:\n\n" <<
			"\t1. Admin\n\n" << "\t2. Employee\n\n" << "\t3. Client\n\n" << "\t4. Exit\n\t";

		bool input_test = (bool)(cin >> login_type);
		if (input_test == 0) {
			system("CLS");
			cout << "\n\n\n\tInvalid input!\n";
			cout << "\n\n\n\tPlease enter a valid value!\n\t";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		if (login_type > 4 || login_type <= 0) {
			system("CLS");
			cout << "\n\n\n\tWrong input, please try again!\n\n";
			login_type = 1;
			continue;
		}
		system("CLS");

		switch (login_type) {
		case 1:
			system("color  1F");
			admin_login();
			break;
		case 2:
			system("color  1F");
			employee_login();
			break;
		case 3:
			system("color  80");
			account_login();
			break;
		case 4:
			cout << "\n\n\n\n\n\n\t\t\t\tThank you for using our banking system!\n\n\n\n\n\n\n\n\n\n";
			exit(1);
		default:
			break;
		}
	}
}

Account account_login() {
	system("CLS");
	Account account;
	string id;
	string first_name, last_name, password;
	double balance;
	string account_type;

	string id_entered;
	cout << "\n\n\n\tPlease enter your account id:\n\t";
	cin >> id_entered;

	bool id_found = false;

	string id_check;
	string first_name_check, last_name_check, password_check, account_type_check;
	double balance_check;

	ifstream accounts_file("accounts.txt");
	while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
		if (id_check == id_entered) {
			id_found = true;
		}
	}

	while (id_found == false) {
		system("CLS");
		cout << "\n\n\n\tInvalid account id!\n\n";
		cout << "\tPlease enter your account id:\n\t";
		cin >> id_entered;

		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id_check >> first_name_check >> last_name_check >> password_check >> balance_check >> account_type_check) {
			if (id_check == id_entered) {
				id_found = true;
			}
		}
	}
	string password_entered;
	do {
		cout << "\tPlease enter your account password:\n\t";

		cin >> password_entered;

		for (int i = 0; i < password_entered.length(); i++) { //encrypting the entered password instead of decrypting the saved one
			password_entered[i] = password_entered[i] + 1;		// to avoid too much code with files
		}

		ifstream accounts_file("accounts.txt");
		while (accounts_file >> id >> first_name >> last_name >> password >> balance >> account_type) {
			if (id_entered == id) {
				if (password_entered == password) {

					account.set_id(id);
					account.set_first_name(first_name);
					account.set_last_name(last_name);
					account.set_password(password);
					account.set_balance(balance);
					account.set_account_type(account_type);
					account.show_account_menu(account);
					break;
				}
				else {
					system("CLS");
					cout << "Wrong password!\n\n";
					break;
				}
			}
		}
	} while (true);
	return account;
}

void employee_login() {
	system("CLS");
	Employee employee;

	string id_entered;
	cout << "\n\n\n\tPlease enter your employee id:\n\t";
	cin >> id_entered;

	bool id_found = false;

	string id_check;
	string first_name_check, last_name_check, password_check;

	ifstream employees_file("employees.txt");
	while (employees_file >> id_check >> first_name_check >> last_name_check >> password_check) {
		if (id_check == id_entered) {
			id_found = true;
		}
	}

	while (id_found == false) {
		system("CLS");
		cout << "\n\n\n\tInvalid employee id!\n\n";
		cout << "\tPlease enter your employee id:\n\t";
		cin >> id_entered;

		ifstream employees_file("employees.txt");
		while (employees_file >> id_check >> first_name_check >> last_name_check >> password_check) {
			if (id_check == id_entered) {
				id_found = true;
			}
		}
	}
	string password_entered;
	do {
		cout << "\n\tPlease enter your employee password:\n\t";

		cin >> password_entered;

		for (int i = 0; i < password_entered.length(); i++) {
			password_entered[i] = password_entered[i] + 1;
		}

		ifstream employees_file("employees.txt");
		while (employees_file >> id_check >> first_name_check >> last_name_check >> password_check) {
			if (id_entered == id_check) {
				if (password_entered == password_check) {
					employee.show_employee_menu();
					break;
				}
				else {
					system("CLS");
					cout << "\n\n\n\tWrong password!\n\n";
					break;
				}
			}
		}
	} while (true);
}

void admin_login() {
	system("CLS");
	Admin admin;
	do {
		cout << "\n\n\n\tPlease enter your id and password:\n\t";
		string id;
		string password_entered;
		cin >> id;
		if (id != "1") {
			system("CLS");
			cout << "\n\n\n\tWrong id!\n";
			continue;
		}
		cout << "\t";
		cin >> password_entered;

		string password;
		ifstream admin_file("admin.txt");

		while (admin_file >> id >> password) {

			if (password_entered == password) {
				admin.show_admin_menu();
				break;
			}
			else {
				system("CLS");
				cout << "\n\n\n\tWrong password!\n\n";
				break;
			}
		}
	} while (true);
}