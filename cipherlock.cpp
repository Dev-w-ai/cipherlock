#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ================= CIPHER ENGINE CLASS =================
class CipherEngine {
private:
    // Helper method to execute core character transformation shifts
    string transformText(string text, int key, bool isEncrypt) {
        // Ensure the key wraps within the 26-letter alphabet space safely
        key = key % 26;
        if (!isEncrypt) {
            // Apply defensive math offset to handle negative C++ modulo behavior safely
            key = (26 - key) % 26;
        }

        for (char &ch : text) {
            // Process Uppercase Block
            if (ch >= 'A' && ch <= 'Z') {
                ch = ((ch - 'A' + key) % 26) + 'A';
            }
            // Process Lowercase Block
            else if (ch >= 'a' && ch <= 'z') {
                ch = ((ch - 'a' + key) % 26) + 'a';
            }
        }
        return text;
    }

    // Isolated internal file parser
    string readFile(const string& filename) {
        ifstream file(filename);
        string data = "";
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                if (!data.empty()) {
                    data += '\n'; // Precise byte tracking layout fixed previously
                }
                data += line;
            }
            file.close();
        } else {
            cout << "[ERROR] Target file could not be opened or located!" << endl;
        }
        return data;
    }

    // Isolated internal file writer
    void saveFile(const string& filename, const string& data) {
        ofstream file(filename);

        if (file.is_open()) {
            file << data;
            file.close();
            cout << "[SUCCESS] Safe data state synced to disk: " << filename << endl;
        } else {
            cout << "[ERROR] Output stream failed. Check directory permissions!" << endl;
        }
    }

public:
    // Operational Interface for Encryption Workflow
    void encryptFile(const string& inputFile, const string& outputFile, int key) {
        string rawText = readFile(inputFile);
        if (rawText.empty() && !inputFile.empty()) return; // Stop processing if source file read failed

        string secureText = transformText(rawText, key, true);
        
        cout << "\n--- TRANSFORMATION PREVIEW (ENCRYPTED) ---" << endl;
        cout << secureText << endl;
        cout << "------------------------------------------\n" << endl;

        saveFile(outputFile, secureText);
    }

    // Operational Interface for Decryption Workflow
    void decryptFile(const string& inputFile, const string& outputFile, int key) {
        string secureText = readFile(inputFile);
        if (secureText.empty() && !inputFile.empty()) return; // Stop processing if source file read failed

        string clearText = transformText(secureText, key, false);

        cout << "\n--- TRANSFORMATION PREVIEW (DECRYPTED) ---" << endl;
        cout << clearText << endl;
        cout << "------------------------------------------\n" << endl;

        saveFile(outputFile, clearText);
    }
};

// ================= MAIN INTERFACE LOOP =================
int main() {
    // Instantiate our custom Cryptographic Object
    CipherEngine engine;

    while (true) {
        int choice;

        cout << endl;
        cout << "========== CIPHER LOCK (OOP EDITION) ==========" << endl;
        cout << "1. Encrypt Existing File" << endl;
        cout << "2. Decrypt Existing File" << endl;
        cout << "3. Terminate Session" << endl;
        cout << "Enter system choice: ";
        cin >> choice;

        // Clear input buffer pipeline to avoid input corruption on string parsing
        cin.ignore();

        if (choice == 3) {
            cout << "Closing system session safely..." << endl;
            break;
        }

        if (choice == 1 || choice == 2) {
            string inputFile, outputFile;
            int key;

            cout << "Enter absolute source filename: ";
            getline(cin, inputFile);

            cout << "Enter target shift key weight: ";
            cin >> key;
            cin.ignore(); // Flush newline out of stream buffer

            cout << "Enter destination filename: ";
            getline(cin, outputFile);

            if (choice == 1) {
                engine.encryptFile(inputFile, outputFile, key);
            } else {
                engine.decryptFile(inputFile, outputFile, key);
            }
        } else {
            cout << "[WARNING] Selection invalid. Re-indexing menu operations!" << endl;
        }
    }

    return 0;
}