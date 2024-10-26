# RSA Decryption Project

This project is an educational tool designed to decrypt a message encrypted with RSA encryption. Given a public key and an encrypted message, the program demonstrates how to break RSA encryption to retrieve the original message by calculating the private key. This project is built for a scenario where only the public key is known.

## Problem Statement

In this project, we assume:
- The public key \((e, n)\) is known.
- The private key is **unknown**.
- An encrypted message \( C \) was intecepted.
  
The task is to "break" the RSA encryption and decrypt the intecepted message without the private key. The solution involves factoring \( n \), computing Euler’s totient function, and finding the decryption exponent using the extended Euclidean algorithm.

## How It Works

The program follows these steps to decrypt the message:

1. **Factorize \( n \)**: Determine the two prime factors of \( n \) to calculate Euler's totient function.
2. **Calculate Euler's Totient Function**: Using the factors of \( n \), compute \( \phi(n) \).
3. **Determine Decryption Exponent \( d \)**: Using the extended Euclidean GCD function, find \( d \) such that \( e \cdot d \equiv 1 \ (\text{mod} \ \phi(n)) \).
4. **Decrypt the Message**: Use the decryption exponent to compute the plaintext message from \( C \).
5. **Translate the Message**: Convert the decrypted numerical message into readable text.

## Inputs

- **Public Key (e, n)**: The encryption exponent \( e \) and modulus \( n \) are provided by the user.
- **Message Size and Encrypted Message \( C \)**: The program accepts the encrypted message size and the message itself as input.

## Output

The program prints:
1. The decoded numerical message.
2. The translated plaintext message.

## Requirements

- C++
## Author
[Marlon L](https://www.linkedin.com/in/marlon-l/)

## Acknowledgments

Thanks to Professor Strzheletska and Mr. Euclid that made this project possible.
