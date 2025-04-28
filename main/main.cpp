#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

#pragma once

#ifndef MYHEADER_H
#define MYHEADER_H

// Helper function to generate a random credit score between 500 and 800
int generateRandomCreditScore() {
    return rand() % 301 + 500;  // Generates a number between 500 and 800
}

class UserInterfaceClass {
private:
    vector<pair<string, pair<string, float>>> userDatabase; // email, password, credit score

public:
    string interfaceID;

    void loadUsers() {
        ifstream file("userpass.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string email, password;
            float creditScore;
            if (getline(ss, email, ',') && getline(ss, password, ',') && ss >> creditScore) {
                userDatabase.push_back(make_pair(email, make_pair(password, creditScore)));
            }
        }
        file.close();
    }

    void saveUser(const string& email, const string& password, float creditScore) {
        ofstream file("userpass.txt", ios::app);
        file << email << "," << password << "," << creditScore << endl;
        file.close();
    }

    bool login(const string& email, const string& password) {
        for (const auto& user : userDatabase) {
            if (user.first == email && user.second.first == password) {
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

        // Generate a random credit score for the new user
        float creditScore = generateRandomCreditScore();

        userDatabase.push_back(make_pair(email, make_pair(password, creditScore)));
        saveUser(email, password, creditScore);
        return true;
    }

    void updateCreditScore(const string& email, float newScore) {
        for (auto& user : userDatabase) {
            if (user.first == email) {
                user.second.second = newScore;  // Update credit score
                cout << "Credit score for " << email << " updated to " << newScore << endl;
                break;
            }
        }
        // Rewrite the entire file with updated data
        ofstream file("userpass.txt", ios::trunc);
        for (const auto& user : userDatabase) {
            file << user.first << "," << user.second.first << "," << user.second.second << endl;
        }
        file.close();
    }

    vector<pair<string, pair<string, float>>> getAllUsers() {
        return userDatabase;
    }

    void applyForRemoval(const string& reason) {
        ofstream file("removal.txt", ios::app);
        if (file.is_open()) {
            file << "Reason for Removal: " << reason << "\n---\n";
            file.close();
        }
    }

    void submitReport(const string& details) {
        ofstream file("report.txt", ios::app);
        if (file.is_open()) {
            file << "Report Details: " << details << "\n---\n";
            file.close();
        }
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

    void submitReport(const string& memberID, const string& details) {
        cout << "Submitting report for member " << memberID << ": " << details << endl;

        ofstream file("member_reports.txt", ios::app);
        if (file.is_open()) {
            file << "Member ID: " << memberID << "\nReport Details: " << details << "\n---\n";
            file.close();
        }
        else {
            cout << "Failed to save member report to file.\n";
        }
    }
};

class ManagerClass {
public:
    string managerID;
    string name;
    string email;

    void wipeAllData() {
        // Deletes all user and report files
        remove("userpass.txt");
        remove("credit_reports.txt");
        remove("member_reports.txt");
        remove("notifications.txt");
        cout << "All user data has been wiped from the system." << endl;
    }
};

#endif

int main() {
    srand(time(0));  // Initialize random seed
    UserInterfaceClass uic;
    uic.loadUsers();

    bool programRunning = true;

    while (programRunning) {
        int choice;
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline character left in the input buffer

        bool loggedIn = false;
        string email, password, role = "";

        if (choice == 1) {
            cout << "Enter email,password (managers must use @manager.com in email): ";
            string userData;
            getline(cin, userData);

            if (uic.registerUser(userData)) {
                cout << "Registration successful.\n";

                // Check if the new registration is a manager
                size_t commaPos = userData.find(',');
                if (commaPos != string::npos) {
                    email = userData.substr(0, commaPos);
                    if (email.size() >= 12 && email.substr(email.size() - 12) == "@manager.com") {
                        cout << "Manager account created successfully.\n";
                    }
                }
            }
            else {
                cout << "Registration failed.\n";
            }
        }
        else if (choice == 2) {
            cout << "Email: ";
            getline(cin, email);
            cout << "Password: ";
            getline(cin, password);

            if (uic.login(email, password)) {
                cout << "Login successful.\n";
                loggedIn = true;

                // Improved role detection
                if (email.size() >= 10 && email.substr(email.size() - 10) == "@admin.com") {
                    role = "admin";
                }
                else if (email.size() >= 12 && email.substr(email.size() - 12) == "@manager.com") {
                    role = "manager";
                }
                else {
                    role = "user";
                }
                cout << "Logged in as: " << role << endl;

                // Logged in user menu
                if (role == "admin") {
                    NotificationClass notifier;
                    SubmitMemberReportClass memberReporter;

                    int adminChoice = 0;
                    while (adminChoice != 7) {
                        cout << "\nAdmin Options:\n";
                        cout << "1. View all users\n";
                        cout << "2. Track report status\n";
                        cout << "3. Update credit score\n";
                        cout << "4. Submit Report\n";
                        cout << "5. Send Notification\n";
                        cout << "6. Submit Member Report\n";
                        cout << "7. Logout\n";
                        cout << "Choose an option: ";
                        cin >> adminChoice;
                        cin.ignore();

                        if (adminChoice == 1) {
                            cout << "\nRegistered Users:\n";
                            for (const auto& user : uic.getAllUsers()) {
                                cout << "- " << user.first << " (Credit Score: " << user.second.second << ")\n";
                            }
                        }
                        else if (adminChoice == 2) {
                            cout << "Enter report ID to track status: ";
                            string reportID;
                            getline(cin, reportID);
                            cout << "Tracking report status for: " << reportID << endl;
                        }
                        else if (adminChoice == 3) {
                            cout << "Enter email to update credit score: ";
                            string email;
                            getline(cin, email);
                            cout << "Enter new credit score: ";
                            float newScore;
                            cin >> newScore;
                            uic.updateCreditScore(email, newScore);
                        }
                        else if (adminChoice == 4) {
                            string details;
                            cout << "Enter report details: ";
                            getline(cin, details);
                            uic.submitReport(details);
                        }
                        else if (adminChoice == 5) {
                            string userID, message;
                            cout << "Enter userID to send notification to: ";
                            getline(cin, userID);
                            cout << "Enter notification message: ";
                            getline(cin, message);
                            notifier.sendNotification(userID, message);
                        }
                        else if (adminChoice == 6) {
                            string memberID, reportDetails;
                            cout << "Enter member ID: ";
                            getline(cin, memberID);
                            cout << "Enter report details: ";
                            getline(cin, reportDetails);
                            memberReporter.submitReport(memberID, reportDetails);
                        }
                        else if (adminChoice == 7) {
                            cout << "Logging out...\n";
                            break;
                        }
                        else {
                            cout << "Invalid choice. Please try again.\n";
                        }
                    }
                }
                else if (role == "manager") {
                    ManagerClass manager;
                    int managerChoice = 0;
                    while (managerChoice != 4) {
                        cout << "\nManager Options:\n";
                        cout << "1. View all users\n";
                        cout << "2. Review Blacklist Entry\n";
                        cout << "3. Wipe all user data\n";
                        cout << "4. Logout\n";
                        cout << "Choose an option: ";
                        cin >> managerChoice;
                        cin.ignore();

                        if (managerChoice == 1) {
                            cout << "\nRegistered Users:\n";
                            for (const auto& user : uic.getAllUsers()) {
                                cout << "- " << user.first << "\n";
                            }
                        }
                        else if (managerChoice == 2) {
                            cout << "Blacklist review functionality would go here\n";
                        }
                        else if (managerChoice == 3) {
                            manager.wipeAllData();
                        }
                        else if (managerChoice == 4) {
                            cout << "Logging out...\n";
                            break;
                        }
                        else {
                            cout << "Invalid choice. Please try again.\n";
                        }
                    }
                }
                else if (role == "user") {
                    DocumentSubmissionClass docSubmitter;
                    int userChoice = 0;
                    while (userChoice != 5) {
                        cout << "\nUser Options:\n";
                        cout << "1. View Credit Score\n";
                        cout << "2. Submit Document\n";
                        cout << "3. Apply for Removal\n";
                        cout << "4. Submit Report\n";
                        cout << "5. Logout\n";
                        cout << "Choose an option: ";
                        cin >> userChoice;
                        cin.ignore();

                        if (userChoice == 1) {
                            for (const auto& user : uic.getAllUsers()) {
                                if (user.first == email) {
                                    cout << "Your credit score is: " << user.second.second << endl;
                                    break;
                                }
                            }
                        }
                        else if (userChoice == 2) {
                            string documentData;
                            cout << "Enter document data to submit: ";
                            getline(cin, documentData);
                            docSubmitter.submitDocument(email, documentData);
                        }
                        else if (userChoice == 3) {
                            string reason;
                            cout << "Enter reason for removal: ";
                            getline(cin, reason);
                            uic.applyForRemoval(reason);
                        }
                        else if (userChoice == 4) {
                            string details;
                            cout << "Enter report details: ";
                            getline(cin, details);
                            uic.submitReport(details);
                        }
                        else if (userChoice == 5) {
                            cout << "Logging out...\n";
                            break;
                        }
                        else {
                            cout << "Invalid choice. Please try again.\n";
                        }
                    }
                }
                else {
                    cout << "Login failed. Incorrect email or password.\n";
                }
            }
            else if (choice == 3) {
                cout << "Exiting program.\n";
                programRunning = false;
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
    }
    return 0;
}