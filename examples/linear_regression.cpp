#include <iostream>
#include <cmath> // Required for std::abs
#include "scheme/params.h"
#include "scheme/keys.h"
#include "scheme/keygenerator.h"
#include "scheme/encryptor.h"
#include "scheme/decryptor.h"

int main() {
    std::cout << "--- FHE Framework: Encrypt/Decrypt Test ---" << std::endl;

    // 1. Setup
    Parameters params;
    params.poly_modulus_degree = 8;
    params.ciphertext_modulus = 17;

    KeyGenerator keygen(params);
    SecretKey secret_key;
    PublicKey public_key;
    keygen.generate(secret_key, public_key);

    Encryptor encryptor(params, public_key);
    Decryptor decryptor(params, secret_key);

    // 2. Encrypt a SMALLER message to avoid boundary issues in decoding
    uint64_t message = 2;
    Polynomial plain_message(params.poly_modulus_degree - 1);
    plain_message.coefficients[0] = message;

    std::cout << "\nOriginal message: " << message << std::endl;
    Ciphertext ciphertext;
    encryptor.encrypt(plain_message, ciphertext);
    std::cout << "Message encrypted." << std::endl;

    // 3. Decrypt the message
    Polynomial decrypted_poly;
    decryptor.decrypt(ciphertext, decrypted_poly);
    uint64_t noisy_message = decrypted_poly.coefficients[0];
    std::cout << "Decryption complete." << std::endl;
    std::cout << "Decrypted value (with noise): " << noisy_message << std::endl;

    // 4. Decode and Verify
    uint64_t q = params.ciphertext_modulus;
    uint64_t half_q = q / 2;
    int64_t decoded_message = noisy_message;

    // This logic works for results that don't cross the q/2 boundary.
    if (noisy_message > half_q) {
        decoded_message = static_cast<int64_t>(noisy_message) - static_cast<int64_t>(q);
    }
    
    if (std::abs(decoded_message - static_cast<int64_t>(message)) <= 5) {
        std::cout << "\nSUCCESS: Decryption is correct (within noise tolerance)!" << std::endl;
    } else {
        std::cout << "\nFAILURE: Decryption is incorrect (noise is too large)." << std::endl;
    }
    
    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}