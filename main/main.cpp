#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <cstdlib> 
#include <algorithm>

using namespace std;


int generateRandomCreditScore() {
    return rand() % 301 + 500;  // Generates a number between 500 and 800
}

// ENUM for Improvement Submission Status
enum Status {
    Pending,
    Approved,
    Rejected
};


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

        float creditScore = generateRandomCreditScore();
        userDatabase.push_back(make_pair(email, make_pair(password, creditScore)));
        saveUser(email, password, creditScore);
        return true;
    }

    void updateCreditScore(const string& email, float newScore) {
        for (auto& user : userDatabase) {
            if (user.first == email) {
                user.second.second = newScore;
                cout << "Credit score for " << email << " updated to " << newScore << endl;
                break;
            }
        }
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

class GenerateCreditReportClass {
public:
    string reportID;
    string memberID;
    string email;
    float creditScore;

    GenerateCreditReportClass(const string& rid = "", const string& mid = "", const string& em = "", float score = 0.0f)
        : reportID(rid), memberID(mid), email(em), creditScore(score) {}

    void generateReport() {
        time_t now = time(0);
        char* dt = ctime(&now);

        cout << "\n===== Credit Report =====\n";
        cout << "Report ID: " << reportID << endl;
        cout << "Member ID: " << memberID << endl;
        cout << "Email:     " << email << endl;
        cout << "Generated: " << dt;
        cout << "Credit Score: " << creditScore << endl;

        if (creditScore >= 750) {
            cout << "Status: Excellent Credit\n";
        }
        else if (creditScore >= 650) {
            cout << "Status: Good Credit\n";
        }
        else if (creditScore >= 550) {
            cout << "Status: Fair Credit\n";
        }
        else {
            cout << "Status: Poor Credit\n";
        }
        cout << "===========================\n";

        // Also save to file
        ofstream file("credit_reports.txt", ios::app);
        if (file.is_open()) {
            file << "Report ID: " << reportID << "\n"
                << "Member ID: " << memberID << "\n"
                << "Email: " << email << "\n"
                << "Generated: " << dt
                << "Credit Score: " << creditScore << "\n"
                << "===========================\n";
            file.close();
        }
        else {
            cout << "Failed to save report to file.\n";
        }
    }
};

// Notification Class
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

// Document Submission Class
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

// Member Report Class
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

// Manager Class
class ManagerClass {
public:
    string managerID;
    string name;
    string email;

    void wipeAllData() {
        remove("userpass.txt");
        remove("credit_reports.txt");
        remove("member_reports.txt");
        remove("notifications.txt");
        cout << "All user data has been wiped from the system." << endl;
    }
};

// Improvement Submission Class
class ImprovementSubmissionClass {
public:
    string submissionID;
    string memberID;
    vector<string> documents;
    Status status;

    bool submitImprovementRequest(string memberID, vector<string> proofDocuments) {
        this->memberID = memberID;
        this->documents = proofDocuments;
        this->status = Pending;
        return true;
    }

    string trackImprovementStatus(string requestID) {
        switch (status) {
        case Pending: return "Pending";
        case Approved: return "Approved";
        case Rejected: return "Rejected";
        }
        return "Unknown";
    }
};

// Fraud Alert Class
class FraudAlertClass {
public:
    string alertID;
    string description;
    string reporterID;

    bool resolveFraudCase(string id) {
        cout << "Resolving fraud case with ID: " << id << endl;
        return true;
    }

    void logFraudIncident(string details) {
        cout << "Logging fraud incident: " << details << endl;
        ofstream file("fraud_alerts.txt", ios::app);
        if (file.is_open()) {
            file << "Alert ID: " << alertID << "\n"
                << "Reporter ID: " << reporterID << "\n"
                << "Description: " << details << "\n"
                << "---\n";
            file.close();
        }
        else {
            cout << "Failed to save fraud incident to file.\n";
        }
    }
};

// Member Class
class MemberClass {
public:
    string memberID;
    string name;
    string email;
    float creditScore;
    vector<string> paymentHistory;

    MemberClass(const string& id = "", const string& nm = "", const string& em = "", float score = 0.0f)
        : memberID(id), name(nm), email(em), creditScore(score) {}

    void viewCreditScore() const {
        cout << "Member ID: " << memberID << "\n"
            << "Name:      " << name << "\n"
            << "Email:     " << email << "\n"
            << "Score:     " << creditScore << "\n"
            << "History:   ";
        for (const auto& rec : paymentHistory) cout << rec << "; ";
        cout << "\n\n";
    }

    bool applyForImprovement(const vector<string>& proofDocuments) {
        cout << "[Member] " << memberID << " submitted " << proofDocuments.size()
            << " docs for credit improvement." << endl;
        return true;
    }
};

// Admin Class
class AdminClass {
public:
    string adminID;
    string name;
    string email;
    vector<string> privileges;

    AdminClass(const string& id = "", const string& nm = "", const string& em = "")
        : adminID(id), name(nm), email(em) {}

    bool reviewBlacklistEntry(const string& entryID) {
        cout << "[Admin] Reviewing blacklist entry " << entryID << endl;
        return true;
    }

    void manageAccessRights(const string& userID) {
        cout << "[Admin] Managing access for user " << userID << endl;
    }

    bool verifyDocumentSubmission(const string& memberID, const vector<string>& documents) {
        cout << "[Admin] Verified " << documents.size() << " docs for member " << memberID << endl;
        return true;
    }
};

// CIBIL Associate Class
class CIBILAssociateClass {
public:
    string associateID;
    string institutionName;
    string contactInfo;

    CIBILAssociateClass(const string& id = "", const string& inst = "", const string& contact = "")
        : associateID(id), institutionName(inst), contactInfo(contact) {}

    void submitDefaulterData(const string& memberID, const string& reason) {
        cout << "[Associate] Submitted defaulter data for " << memberID
            << " Reason: " << reason << endl;
    }

    string trackReportStatus(const string& reportID) {
        cout << "[Associate] Tracking status for report " << reportID << endl;
        return "Pending";
    }

    void submitFinancialData(const string& memberID, const string& data) {
        cout << "[Associate] Submitted financial data \"" << data
            << "\" for " << memberID << endl;
    }
};

// Credit Report Class
class CreditReportClass {
public:
    string reportID;
    string memberID;
    string loanDetails;

    CreditReportClass(const string& rid = "", const string& mid = "", const string& loan = "")
        : reportID(rid), memberID(mid), loanDetails(loan) {}

    float calculateCreditScore(const vector<float>& payments) {
        if (payments.empty()) return 0.0f;
        float sum = accumulate(payments.begin(), payments.end(), 0.0f);
        return sum / payments.size();
    }

    void generateReport(const string& userID) {
        cout << "[CreditReport] Generating report " << reportID
            << " for user " << userID << "\n"
            << "Loan details: " << loanDetails << "\n\n";
    }
};

// Blacklist Entry Class
class BlacklistEntryClass {
public:
    string entryID;
    string memberID;
    string reason;
    float fineAmount;

    BlacklistEntryClass(const string& eid = "", const string& mid = "",
        const string& rsn = "", float fine = 0.0f)
        : entryID(eid), memberID(mid), reason(rsn), fineAmount(fine) {}

    bool submitFineReceipt(const string& receiptData) {
        cout << "[Blacklist] Receipt for entry " << entryID
            << ": " << receiptData << endl;
        return true;
    }

    bool updateStatus(const string& status) {
        cout << "[Blacklist] Entry " << entryID
            << " status updated to " << status << endl;
        return true;
    }
};

// Payment History Class
class PaymentHistoryClass {
public:
    string paymentID;
    string memberID;
    float amountPaid;
    string paymentDate;

    PaymentHistoryClass(const string& pid = "", const string& mid = "",
        float amt = 0.0f, const string& date = "")
        : paymentID(pid), memberID(mid), amountPaid(amt), paymentDate(date) {}

    void addPaymentRecord(const string& mid, float amount, const string& date) {
        memberID = mid;
        amountPaid = amount;
        paymentDate = date;
        cout << "[PaymentHistory] " << memberID
            << " paid " << amountPaid
            << " on " << paymentDate << endl;
    }
};


int main() {
    srand(time(0));  // Initialize random seed

    UserInterfaceClass uic;
    uic.loadUsers();

    ImprovementSubmissionClass improvementManager;
    FraudAlertClass fraudManager;

    bool programRunning = true;

    while (programRunning) {
        int choice;
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore();  // Clear newline character

        bool loggedIn = false;
        string email, password, role = "";

        if (choice == 1) {
            cout << "Enter email,password (managers must use @manager.com in email): ";
            string userData;
            getline(cin, userData);

            if (uic.registerUser(userData)) {
                cout << "Registration successful.\n";
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

                // Detect role
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

                // Create credit report for the logged-in user
                float userScore = 0.0f;
                for (const auto& user : uic.getAllUsers()) {
                    if (user.first == email) {
                        userScore = user.second.second;
                        break;
                    }
                }

                // Generate a report ID based on time
                time_t now = time(0);
                string reportID = "RPT" + to_string(now % 1000000);

                GenerateCreditReportClass creditReport(reportID, "MEM" + to_string(rand() % 10000), email, userScore);
                creditReport.generateReport();

                if (role == "admin") {
                    NotificationClass notifier;
                    SubmitMemberReportClass memberReporter;
                    int adminChoice = 0;

                    while (adminChoice != 9) {
                        cout << "\nAdmin Options:\n";
                        cout << "1. View all users\n";
                        cout << "2. Track report status\n";
                        cout << "3. Update credit score\n";
                        cout << "4. Submit report\n";
                        cout << "5. Send notification\n";
                        cout << "6. Submit member report\n";
                        cout << "7. Log Fraud Incident\n";
                        cout << "8. Resolve Fraud Case\n";
                        cout << "9. Logout\n";
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
                            string emailToUpdate;
                            getline(cin, emailToUpdate);
                            cout << "Enter new credit score: ";
                            float newScore;
                            cin >> newScore;
                            cin.ignore();
                            uic.updateCreditScore(emailToUpdate, newScore);
                        }
                        else if (adminChoice == 4) {
                            string details;
                            cout << "Enter report details: ";
                            getline(cin, details);
                            uic.submitReport(details);
                        }
                        else if (adminChoice == 5) {
                            string userID, message;
                            cout << "Enter userID: ";
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
                            string fraudDetails;
                            cout << "Enter fraud details: ";
                            getline(cin, fraudDetails);
                            fraudManager.logFraudIncident(fraudDetails);
                            cout << "Fraud incident logged.\n";
                        }
                        else if (adminChoice == 8) {
                            string alertID;
                            cout << "Enter fraud alert ID to resolve: ";
                            getline(cin, alertID);
                            if (fraudManager.resolveFraudCase(alertID)) {
                                cout << "Fraud case resolved.\n";
                            }
                            else {
                                cout << "Failed to resolve fraud case.\n";
                            }
                        }
                        else if (adminChoice == 9) {
                            cout << "Logging out...\n";
                        }
                        else {
                            cout << "Invalid choice.\n";
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
                            cout << "Blacklist review functionality would go here.\n";
                        }
                        else if (managerChoice == 3) {
                            manager.wipeAllData();
                        }
                        else if (managerChoice == 4) {
                            cout << "Logging out...\n";
                        }
                        else {
                            cout << "Invalid choice.\n";
                        }
                    }
                }
                else if (role == "user") {
                    DocumentSubmissionClass docSubmitter;
                    int userChoice = 0;
                    while (userChoice != 8) {  // Changed to 8 to add new option
                        cout << "\nUser Options:\n";
                        cout << "1. View Credit Score\n";
                        cout << "2. Generate New Credit Report\n";  // New option
                        cout << "3. Submit Document\n";
                        cout << "4. Apply for Removal\n";
                        cout << "5. Submit Report\n";
                        cout << "6. Submit Improvement Request\n";
                        cout << "7. Track Improvement Request Status\n";
                        cout << "8. Logout\n";
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
                            // Generate a new report
                            float userScore = 0.0f;
                            for (const auto& user : uic.getAllUsers()) {
                                if (user.first == email) {
                                    userScore = user.second.second;
                                    break;
                                }
                            }
                            time_t now = time(0);
                            string newReportID = "RPT" + to_string(now % 1000000);
                            GenerateCreditReportClass newReport(newReportID, "MEM" + to_string(rand() % 10000), email, userScore);
                            newReport.generateReport();
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
                            vector<string> documents;
                            string doc;
                            cout << "Enter documents (type 'done' when finished):\n";
                            while (true) {
                                getline(cin, doc);
                                if (doc == "done") break;
                                documents.push_back(doc);
                            }
                            improvementManager.submitImprovementRequest(email, documents);
                            cout << "Improvement request submitted.\n";
                        }
                        else if (userChoice == 6) {
                            cout << "Improvement Status: " << improvementManager.trackImprovementStatus(improvementManager.submissionID) << endl;
                        }
                        else if (userChoice == 7) {
                            cout << "Logging out...\n";
                        }
                        else if (userChoice == 8) {
                            cout << "Logging out...\n";
                        }
                        else {
                            cout << "Invalid choice.\n";
                        }
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

    return 0;
}