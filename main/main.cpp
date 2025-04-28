#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

#pragma once

#ifndef MYHEADER_H
#define MYHEADER_H

class UserInterfaceClass {
private:
    vector<pair<string, string>> userDatabase; // email, password

public:
    string interfaceID;

    void loadUsers() {
        ifstream file("userpass.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string email, password;
            if (getline(ss, email, ',') && getline(ss, password)) {
                userDatabase.push_back(make_pair(email, password));
            }
        }
        file.close();
    }

    void saveUser(const string& email, const string& password) {
        ofstream file("userpass.txt", ios::app);
        file << email << "," << password << endl;
        file.close();
    }

    bool login(const string& email, const string& password) {
        for (const auto& user : userDatabase) {
            if (user.first == email && user.second == password) {
                return true;
            }
        }
        return false;
    }

    bool registerUser(const string& userData) {
        size_t commaPos = userData.find(',');
        if (commaPos == string::npos) {
            cout << "Invalid format. Use email,password format." << endl;
            return false;
        }
        string email = userData.substr(0, commaPos);
        string password = userData.substr(commaPos + 1);

        for (const auto& user : userDatabase) {
            if (user.first == email) {
                cout << "User already exists." << endl;
                return false;
            }
        }

        userDatabase.push_back(make_pair(email, password));
        saveUser(email, password);
        return true;
    }

    bool applyForRemoval(const string& reason) {
        ofstream file("removal.txt", ios::app);
        if (file.is_open()) {
            file << "Reason for Removal: " << reason << "\n---\n";
            file.close();
            return true;
        }
        return false;
    }

    bool submitReport(const string& details) {
        ofstream file("report.txt", ios::app);
        if (file.is_open()) {
            file << "Report Details: " << details << "\n---\n";
            file.close();
            return true;
        }
        return false;
    }

    vector<pair<string, string>> getAllUsers() {
        return userDatabase;
    }
};

class NotificationClass {
public:
    string notificationID;
    string userID;
    string message;

    void sendNotification(const string& userID, const string& message) {
        cout << "Notification to " << userID << ": " << message << endl;

        ofstream file("notifications.txt", ios::app);
        if (file.is_open()) {
            file << "Notification to " << userID << ": " << message << "\n";
            file.close();
        }
        else {
            cout << "Failed to save notification to file.\n";
        }
    }
};

class DocumentSubmissionClass {
public:
    string documentID;
    string memberID;
    string documentType;
    string submissionDate;

    void submitDocument(const string& memberID, const string& documentData) {
        cout << "Document \"" << documentData << "\" submitted for member: " << memberID << endl;

        ofstream file("documents.txt", ios::app);
        if (file.is_open()) {
            file << "Member ID: " << memberID << "\nDocument: " << documentData << "\n---\n";
            file.close();
        }
        else {
            cout << "Failed to save document to file.\n";
        }
    }
};

class SubmitMemberReportClass {
public:
    string reportID;
    string memberID;
    string details;

    bool submitReport(const string& memberID, const string& details) {
        cout << "Submitting report for member " << memberID << ": " << details << endl;

        ofstream file("member_reports.txt", ios::app);
        if (file.is_open()) {
            file << "Member ID: " << memberID << "\nReport Details: " << details << "\n---\n";
            file.close();
            return true;
        }
        else {
            cout << "Failed to save member report to file.\n";
            return false;
        }
    }
};

class GenerateCreditReportClass {
public:
    string reportID;

    void generateReport(const string& userID) {
        cout << "Generating Credit Report for: " << userID << endl;

        ofstream file("credit_reports.txt", ios::app);
        if (file.is_open()) {
            file << "Generated Credit Report for User: " << userID << "\n---\n";
            file.close();
        }
        else {
            cout << "Failed to save credit report to file.\n";
        }
    }
};

#endif

int main() {
    UserInterfaceClass uic;
    uic.loadUsers();

    int choice;
    cout << "1. Login\n2. Register\nChoose an option: ";
    cin >> choice;
    cin.ignore();

    bool loggedIn = false;
    string email, password, role = "";

    if (choice == 1) {
        cout << "Email: ";
        getline(cin, email);
        cout << "Password: ";
        getline(cin, password);

        if (uic.login(email, password)) {
            cout << "Login successful.\n";
            loggedIn = true;

            // Automatically detect admin
            if (email.size() >= 10 && email.substr(email.size() - 10) == "@admin.com") {
                role = "admin";
            }
            else {
                role = "user";
            }
        }
        else {
            cout << "Login failed. Incorrect email or password.\n";
        }
    }
    else if (choice == 2) {
        string userData;
        cout << "Enter email,password: ";
        getline(cin, userData);

        if (uic.registerUser(userData)) {
            cout << "Registration successful.\n";

            // Now prompt login again
            cout << "\nPlease login now:\n";
            cout << "Email: ";
            getline(cin, email);
            cout << "Password: ";
            getline(cin, password);

            if (uic.login(email, password)) {
                cout << "Login successful.\n";
                loggedIn = true;

                // Automatically detect admin
                if (email.size() >= 10 && email.substr(email.size() - 10) == "@admin.com") {
                    role = "admin";
                }
                else {
                    role = "user";
                }
            }
            else {
                cout << "Login failed. Incorrect email or password.\n";
            }
        }
        else {
            cout << "Registration failed.\n";
        }
    }
    else {
        cout << "Invalid choice.\n";
    }

    


    // Logged in user menu
    if (loggedIn) {
        if (role == "admin") {
            NotificationClass notifier;
            SubmitMemberReportClass memberReporter;
            GenerateCreditReportClass reportGenerator;

            int adminChoice = 0;
            while (adminChoice != 6) {
                cout << "\nAdmin Options:\n";
                cout << "1. View all users\n";
                cout << "2. Submit Report\n";
                cout << "3. Generate Credit Report\n";
                cout << "4. Send Notification\n";
                cout << "5. Submit Member Report\n";
                cout << "6. Logout\n";
                cout << "Choose an option: ";
                cin >> adminChoice;
                cin.ignore();

                if (adminChoice == 1) {
                    cout << "\nRegistered Users:\n";
                    for (const auto& user : uic.getAllUsers()) {
                        cout << "- " << user.first << endl;
                    }
                }
                else if (adminChoice == 2) {
                    string details;
                    cout << "Enter report details: ";
                    getline(cin, details);
                    uic.submitReport(details);
                }
                else if (adminChoice == 3) {
                    string userID;
                    cout << "Enter userID to generate credit report for: ";
                    getline(cin, userID);
                    reportGenerator.generateReport(userID);
                }
                else if (adminChoice == 4) {
                    string userID, message;
                    cout << "Enter userID to send notification to: ";
                    getline(cin, userID);
                    cout << "Enter notification message: ";
                    getline(cin, message);
                    notifier.sendNotification(userID, message);
                }
                else if (adminChoice == 5) {
                    string memberID, reportDetails;
                    cout << "Enter member ID: ";
                    getline(cin, memberID);
                    cout << "Enter report details: ";
                    getline(cin, reportDetails);
                    memberReporter.submitReport(memberID, reportDetails);
                }
                else if (adminChoice == 6) {
                    cout << "Logging out...\n";
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
        }
        else if (role == "user") {
            int userChoice = 0;
            while (userChoice != 3) {
                cout << "\nUser Options:\n";
                cout << "1. Apply for Removal\n";
                cout << "2. Submit Document\n";
                cout << "3. Logout\n";
                cout << "Choose an option: ";
                cin >> userChoice;
                cin.ignore();

                if (userChoice == 1) {
                    string reason;
                    cout << "Enter reason for credit report removal: ";
                    getline(cin, reason);
                    uic.applyForRemoval(reason);
                }
                else if (userChoice == 2) {
                    DocumentSubmissionClass docSubmit;
                    string memberID, documentData;
                    cout << "Enter your Member ID: ";
                    getline(cin, memberID);
                    cout << "Enter document details: ";
                    getline(cin, documentData);
                    docSubmit.submitDocument(memberID, documentData);
                }
                else if (userChoice == 3) {
                    cout << "Logging out...\n";
                }
                else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
        }
    }

    return 0;
}