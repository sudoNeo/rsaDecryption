#include <iostream>
#include <vector>
using namespace std;

// Function to check if the public key is valid
bool isValidPublicKey(int e, int n);

// Function to factorize n into p and q (p < q)
void factorizeN(int n, int& p, int& q);

// Function to compute Euler's Totient Function phi(n)
int computePhi(int p, int q);

// Function to compute the modular inverse d of e mod phi(n)
int computeD(int e, int phi);

// Function to perform modular exponentiation
int modPow(int base, int exponent, int modulus);

// Function to decode the encrypted message
void decodeMessage(const vector<int>& encryptedMessage, int d, int n, vector<int>& decodedIntegers);

// Function to map integers to characters based on the given encoding scheme
char mapIntegerToChar(int value);

int main() {
    int e, n;
    cin >> e >> n;

    int m;
    cin >> m;

    vector<int> encryptedMessage(m);
    for (int i = 0; i < m; ++i) {
        cin >> encryptedMessage[i];
    }

    // Check if the public key is valid
    if (!isValidPublicKey(e, n)) {
        cout << "Error: Invalid public key." << endl;
        return 0;
    }

    int p, q;
    factorizeN(n, p, q);

    // Ensure p < q
    if (p > q) swap(p, q);

    int phi = computePhi(p, q);
    int d = computeD(e, phi);

    // Output p, q, phi(n), and d
    cout << p << " " << q << " " << phi << " " << d << endl;

    // Decode the message
    vector<int> decodedIntegers;
    decodeMessage(encryptedMessage, d, n, decodedIntegers);

    // Output decoded integers
    for (size_t i = 0; i < decodedIntegers.size(); ++i) {
        cout << decodedIntegers[i];
        if (i != decodedIntegers.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;

    // Output decoded characters
    for (int val : decodedIntegers) {
        char c = mapIntegerToChar(val);
        cout << c;
    }
    cout << endl;

    return 0;
}

char mapIntegerToChar(int value) {
    if (value >= 7 && value <= 32) {
        // Map values 7 to 32 to uppercase letters A to Z
        return 'A' + (value - 7);
    } else if (value == 33) {
        //  space
        return ' ';
    } else if (value == 34) {
        // Quotation 
        return '"';
    } else if (value == 35) {
        // ,
        return ',';
    } else if (value == 36) {
        // .
        return '.';
    } else if (value == 37) {
        // '
        return '\'';
    } else {
        // ?
        return '?';
    }
}
