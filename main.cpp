#include "common_nix.h"

using namespace std;

bool isLoggedIn()
{
	ifstream infile;
	infile.open("creds.txt");
	return !infile ? false : true;
}

bool createCredFile()
{
	try {
		system("clear");
		string username, password;
		cout << "Select a username: ";
		cin >> username;
		cout << "Select a password: ";
		cin >> password;
		ofstream file;
		file.open("creds.txt");
		file << username << "\n" << password;
		file.close();
		cout << "\nThanks! You're all set to log in now." << endl;
		system("sleep 2");
		system("clear");
		return true;
	} catch (const exception &e) {
		cerr << e.what() << '\n';
		return false;
	}
}

int main()
{
	//  Initial input to correspond to menu case opts
	int choice;
	bool onCreate = false, validFile = false;
	string _registeredUname, _registeredPword, regU, regP;
	cout << "=================WELCOME=================" << endl;
	cout << "\n\n1. Register\n2. Login\n3. Quit\n\nYour choice? => ";
	cin >> choice;
	switch (choice) {
	case 1:
		onCreate = createCredFile();
		return onCreate == true
			   ? main()
			   : false; // Automatically hop right back in
				    // to allow them to proceed with opt 2
	case 2:
		validFile =
		    isLoggedIn(); // Expect fail if user attempts to select opt
				  // 2 right away - no such file
		if (validFile) {
			system("sleep 2");
			system("clear");
			cout << "Okay, please enter the username you used "
				"during registration => ";
			cin >> _registeredUname;
			cout << "And now your password please => ";
			cin >> _registeredPword;
			system("sleep 2");
			ifstream read("creds.txt");
			getline(read, regU);
			getline(read, regP);

			if (regU == _registeredUname &&
			    regP == _registeredPword) {
				cout << "\nSUCESSFUL LOGIN. Thank you!";
			} else {
				cout << "\nBAD LOGIN";
			}
			break;
		} else {
			cout
			    << "Looks like you still need to register.\nPlease "
			       "do so, and then select this option again."
			    << endl;
			system("sleep 2");
			system("clear");
			main(); // Run it from the top...
		}
	case 3:
		break;
	default:
		break;
	}

	return 0;
}
