#include <iostream>
#include <array>
#include <vector>
#include <cmath>
using namespace std;

// Function to check if the public key is valid
bool isValidPublicKey(int e, int p, int q, int phi);
//we need to check that n is a product of two distinct prime number 
// factorize n into p and q (p < q)
void factorizeN(int n, int& p, int& q);

//  compute Euler's Totient Function phi(n) =(p-1)(q-1)
int computePhi(int p, int q);
int modPow(int base, int exponent, int mod);
// find the modular inverse of e mod phi(n)
int computeD(int e, int phi);

// Function to decode the encrypted message
void decodeMessage(const vector<int>& encryptedMessage, int d, int n, vector<int>& decodedIntegers);

// Function to map integers to characters based on the given encoding scheme
char mapIntegerToChar(int value);

//need to see if e and phi(n) are coprime, for this we know GCD(e , phi(n) ) =1 
array<int,3> extgcd(int a, int b); 
bool isCoprime(int a , int b);
bool isPrime(int n);

int main() {
    int e, n;
    cin >> e >> n;

    int m;
    cin >> m;

    vector<int> encryptedMessage(m);
    for (int i = 0; i < m; ++i) {
        cin >> encryptedMessage[i];
    }
    int p, q;
    factorizeN(n, p, q);

    // Check if the public key is valid
    int phi = computePhi(p, q);
    if (!isValidPublicKey(e, p, q, phi)) {
        cout << "Public key is not valid!";
        return 0;
    }
 
    // Ensure p < q
    if (p > q) swap(p, q);

    int d = computeD(e, phi);

    // Output p, q, phi(n), and d
    cout << p << " " << q << " " << phi << " " << d << "\n";

    //TODO CHECK IF PH(N) AND e are CO PRIME
    if (isCoprime(phi, e)) {
        //decode
        vector<int> decodedIntegers;
        decodeMessage(encryptedMessage, d, n, decodedIntegers);

        // Output decoded integers
        for (int i = 0; i < decodedIntegers.size(); ++i) {
            cout << decodedIntegers[i];
           
                cout << " ";
            
        }
        cout << "\n";

        // Output decoded characters
        for (int val : decodedIntegers) {
            char c = mapIntegerToChar(val);
            cout << c ;
        }
        //cout << "\n";
    } else cout << "Public key is not valid!";
    return 0;
}

//easy function first phi 
int computePhi(int p, int q) {
    return (p - 1) * (q - 1);
}
char mapIntegerToChar(int value) {
    if (value >= 7 && value <= 32) {
        // Map values 7 to 32 to uppercase letters A to Z
        return 'A' + (value - 7);
    } else if (value == 33) {
        // space
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

void decodeMessage(const vector<int>& encryptedMessage, int d, int n, vector<int>& decodedIntegers) {
    for (int i = 0; i < encryptedMessage.size(); i++) {
        int c = encryptedMessage[i];
        decodedIntegers.push_back(modPow(c, d, n));
        //To decode the message preform c^d mod n
    }
}

// With a little help of paul interpertation Euclid's algo
array<int, 3> extgcd(int a, int b) {
    if (b == 0)
        return {a, 1, 0};
    auto arr = extgcd(b, a % b);
    return {arr[0], arr[2], arr[1] - (a / b) * arr[2]};
}
bool isCoprime(int a, int b) {
    auto result = extgcd(a, b);
    int gcdC = result[0];
    return gcdC == 1;
}
int computeD(int e, int phi) {
    //from our extended algo we have x and the gcd, the gcd is guranteed to be 1 once we are here 
    //incase x is negative 
    auto result = extgcd(e, phi);
    int x = result[1];
    //just incase x is negative
    return (x % phi + phi) % phi;
}

void factorizeN(int n, int& p, int& q) {
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            return;
        }
    }
    p = n;
    q = 1;
}
bool isPrime(int n) {
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;
    int sqrt_n = static_cast<int>(std::sqrt(n));
    for (int i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}
bool isValidPublicKey(int e, int p, int q, int phi) {
    if (!isPrime(p) || !isPrime(q)) {
        return false; 
    }
    if (p == q) {
        return false; // p and q should be distinct
    }

    //  if e and phi are coprime
    if (!isCoprime(e, phi)) {
        return false; // e and phi should be coprime
    }
    
    return true;
}

int modPow(int base, int exponent, int mod) {
    if (mod == 1) return 0; 

    int result = 1;
    base = base % mod;  

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}
