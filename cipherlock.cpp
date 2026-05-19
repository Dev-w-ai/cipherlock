#include<iostream>
#include<string>
#include<fstream>

using namespace std;


// ================= ENCRYPT FUNCTION =================

string encrypt(string text, int key){

    key = key % 26;

    for(char &ch : text){

        // Encrypt uppercase letters
        if(ch >= 'A' && ch <= 'Z'){
            ch = ((ch - 'A' + key) % 26) + 'A';
        }

        // Encrypt lowercase letters
        else if(ch >= 'a' && ch <= 'z'){
            ch = ((ch - 'a' + key) % 26) + 'a';
        }
    }

    return text;
}


// ================= DECRYPT FUNCTION =================

string decrypt(string text, int key){

    key = key % 26;

    for(char &ch : text){

        // Decrypt uppercase letters
        if(ch >= 'A' && ch <= 'Z'){
            ch = ((ch - 'A' - key + 26) % 26) + 'A';
        }

        // Decrypt lowercase letters
        else if(ch >= 'a' && ch <= 'z'){
            ch = ((ch - 'a' - key + 26) % 26) + 'a';
        }
    }

    return text;
}


// ================= READ FILE FUNCTION =================

string readFile(string filename){

    ifstream file(filename);

    string data = "";
    string line;

    if(file.is_open()){

        while(getline(file, line)){

            if(!data.empty()){
                data += '\n';
            }

            data += line;
        }

        file.close();
    }

    else{
        cout << "File could not be opened!" << endl;
    }

    return data;
}


// ================= SAVE FILE FUNCTION =================

void saveFile(string filename, string data){

    ofstream file(filename);

    if(file.is_open()){

        file << data;

        file.close();

        cout << "Data saved successfully in " << filename << endl;
    }

    else{
        cout << "File could not be created!" << endl;
    }
}


// ================= MAIN FUNCTION =================

int main(){

    while(true){

        int choice;

        cout << endl;
        cout << "========== CIPHER LOCK ==========" << endl;
        cout << "1. Encrypt File" << endl;
        cout << "2. Decrypt File" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        // ================= ENCRYPT =================

        if(choice == 1){

            string inputFile;
            string outputFile;
            int key;

            cout << "Enter file name to encrypt: ";
            getline(cin, inputFile);

            // Read file contents
            string text = readFile(inputFile);

            cout << "Enter encryption key: ";
            cin >> key;

            cin.ignore();

            // Encrypt file contents
            string encrypted = encrypt(text, key);

            cout << endl;
            cout << "Encrypted Text:" << endl;
            cout << encrypted << endl;

            cout << endl;
            cout << "Enter output file name: ";
            getline(cin, outputFile);

            // Save encrypted data
            saveFile(outputFile, encrypted);
        }

        // ================= DECRYPT =================

        else if(choice == 2){

            string inputFile;
            string outputFile;
            int key;

            cout << "Enter file name to decrypt: ";
            getline(cin, inputFile);

            // Read encrypted file
            string text = readFile(inputFile);

            cout << "Enter decryption key: ";
            cin >> key;

            cin.ignore();

            // Decrypt text
            string decrypted = decrypt(text, key);

            cout << endl;
            cout << "Decrypted Text:" << endl;
            cout << decrypted << endl;

            cout << endl;
            cout << "Enter output file name: ";
            getline(cin, outputFile);

            // Save decrypted data
            saveFile(outputFile, decrypted);
        }

        // ================= EXIT =================

        else if(choice == 3){

            cout << "Exiting Program..." << endl;
            break;
        }

        // ================= INVALID INPUT =================

        else{
            cout << "Invalid Choice!" << endl;
        }
    }

    return 0;
}