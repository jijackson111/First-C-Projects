#include <iostream>
#include <string>
#include <fstream>
#include <regex>

// Declaration
using namespace std;

// Login class
class Login {
    public:
    string username;
    string password;
    string checkAgainst;

    int checkPasswordMatch() {
        string toCheck = username + ":" + password;
        if (toCheck == checkAgainst) {
            cout << "Password match" << endl;
            return 1;
        }
        else {
            cout << "Invalid password" << endl;
            return 0;
        }
    }

    int checkUserExists(string user) {
        string line;
        ifstream file("credentials.txt");
        if (file.is_open()) {
            while (getline(file, line)) {
                regex Find("(.*)(:)");
                smatch m;
                regex_search(line, m, Find);
                string userline = m[1];
                if (userline == user) {
                    username = user;
                    checkAgainst = line;
                    return 1;
                }
                else {
                    continue;
                }
            }
        file.close();
        }
        return 0;
    }

    void setPass() {
        string pass;
        cout << "Enter password: ";
        cin >> pass;
        password = pass;
    }

    string setUser() {
        string user;
        cout << "Enter username: ";
        cin >> user;
        string re = "(.*)(:)";
        return user;
    }

};

// Register class
class Register {
    public:
    string username;
    string password;
    
    void outputToFile() {
        ofstream outfile;
        outfile.open("credentials.txt", ios_base::app);
        outfile << endl;
        outfile << username << ":" << password << endl;
    }

    int checkUserExists(string user) {
        string line;
        ifstream file("credentials.txt");
        if (file.is_open()) {
            while (getline(file, line)) {
                regex Find("(.*)(:)");
                smatch m;
                regex_search(line, m, Find);
                string userline = m[1];
                if (userline == user) {
                    return 1;
                }
                else {
                    continue;
                }
            }
        file.close();
        }
        return 0;
    }

    void setPass() {
        string pass;
        cout << "Enter password: ";
        cin >> pass;
        password = pass;
    }

    string setUser() {
        string user;
        cout << "Enter username: ";
        cin >> user;
        string re = "(.*)(:)";
        return user;
    }
};

// Class object functions
int loginDoesMatch(Login obj1) {
    obj1.setPass();
    cout << endl;
    return obj1.checkPasswordMatch();
}

void loginObject() {
    Login obj1;
    string user = obj1.setUser();
    int userExists = obj1.checkUserExists(user);
    int wasMatch;
    if (userExists == 0) {
        cout << "Does not exist";
    }
    else {
        wasMatch = loginDoesMatch(obj1);
    }
    int attemptsLeft = 3;
    while (attemptsLeft > 0 && wasMatch==0) {
            cout << endl;
            cout << to_string(attemptsLeft) << " attempts left" << endl;
            wasMatch = loginDoesMatch(obj1);
            attemptsLeft -= 1;
    }
    if (attemptsLeft == 0) {
        cout << "No attempts left" << endl;
    }
    else {
        ignore;
    }
}

void registerObject() {
    Register obj1;
    string user = obj1.setUser();
    int userExists = obj1.checkUserExists(user);
    if (userExists == 1) {
        cout << "Username already exists" << endl;
    }
    else {
        obj1.username = user;
        obj1.setPass();
        obj1.outputToFile();
        cout << endl;
        cout << "Credentials saved" << endl;
    }
}

// Main function
int main() {
    int option;
    cout << endl;
    cout << "Enter 1 to login, enter 2 to register: ";
    cin >> option;
    cout << endl;
    if (option == 1) {
        loginObject();
    }
    else if (option == 2) {
        registerObject();
    }
    else {
        cout << "Invalid option" << endl;;
    }
    return 0;
}