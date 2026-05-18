#include<iostream>
#include<string>
#include<fstream>

using namespace std;


// ================= ENCRYPT FUNCTION =================

string encrypt(string text, int key){

    key = key % 26;

    for(char &ch : text){

        // Uppercase letters
        if(ch >= 'A' && ch <= 'Z'){
            ch = ((ch - 'A' + key) % 26) + 'A';
        }

        // Lowercase letters
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

        // Uppercase letters
        if(ch >= 'A' && ch <= 'Z'){
            ch = ((ch - 'A' - key + 26) % 26) + 'A';
        }

        // Lowercase letters
        else if(ch >= 'a' && ch <= 'z'){
            ch = ((ch - 'a' - key + 26) % 26) + 'a';
        }
    }

    return text;
}


// ================= SAVE FILE FUNCTION =================

void saveFile(string data){

    ofstream file("encrypted.txt");

    if(file.is_open()){

        file << data;

        file.close();

        cout << "Data saved in encrypted.txt" << endl;
    }

    else{
        cout << "File could not be opened!" << endl;
    }
}


// ================= MAIN FUNCTION =================

int main(){

    int choice;

    cout << "===== CIPHER LOCK =====" << endl;
    cout << "1. Encrypt Text" << endl;
    cout << "2. Decrypt Text" << endl;
    cout << "3. Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore();

    if(choice == 1){

        string text;
        int key;

        cout << "Enter text to encrypt: " << endl;
        getline(cin, text);

        cout << "Enter encryption key: ";
        cin >> key;

        string encrypted = encrypt(text, key);

        cout << "Encrypted Text: " << encrypted << endl;

        saveFile(encrypted);
    }

    else if(choice == 2){

        string text;
        int key;

        cout << "Enter text to decrypt: " << endl;
        getline(cin, text);

        cout << "Enter decryption key: ";
        cin >> key;

        string decrypted = decrypt(text, key);

        cout << "Decrypted Text: " << decrypted << endl;
    }

    else if(choice == 3){

        cout << "Exiting Program..." << endl;
    }

    else{
        cout << "Invalid Choice!" << endl;
    }

    return 0;
}