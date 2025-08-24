#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "scheme/params.h"
#include "scheme/keys.h"
#include "scheme/keygenerator.h"
#include "scheme/encryptor.h"
#include "scheme/decryptor.h"
#include "scheme/evaluator.h"

// Re-using our robust verification function
void verify_decryption(const std::string& label, uint64_t expected_msg, const Polynomial& decrypted_poly, const Parameters& params);

int main() {
    std::cout << "--- FHE Framework: Homomorphic Multiplication Test ---" << std::endl;

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
    Evaluator evaluator(params);

    // 2. Encrypt two messages
    uint64_t m1 = 2, m2 = 3;
    Polynomial p1; p1.coefficients.push_back(m1);
    Polynomial p2; p2.coefficients.push_back(m2);

    Ciphertext ct1, ct2;
    encryptor.encrypt(p1, ct1);
    encryptor.encrypt(p2, ct2);
    std::cout << "\nEncrypting m1 = " << m1 << " and m2 = " << m2 << std::endl;

    // 3. Perform homomorphic multiplication
    std::vector<Polynomial> ct_mult;
    evaluator.multiply(ct1, ct2, ct_mult);
    std::cout << "Homomorphic multiplication complete." << std::endl;

    // 4. Decrypt the result using our special decryption function
    Polynomial decrypted_prod;
    decryptor.decrypt_multiplied(ct_mult, decrypted_prod);

    // 5. Verify
    verify_decryption("m1 * m2", m1 * m2, decrypted_prod, params);
    
    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}

// Definition of the verification function from the previous step
void verify_decryption(const std::string& label, uint64_t expected_msg, const Polynomial& decrypted_poly, const Parameters& params) {
    std::cout << "\nVerifying '" << label << "'..." << std::endl;
    uint64_t noisy_message = decrypted_poly.coefficients[0];
    uint64_t q = params.ciphertext_modulus;
    std::cout << "Decrypted value (with noise): " << noisy_message << std::endl;
    uint64_t noise_unsigned = (noisy_message + q - (expected_msg % q)) % q;
    int64_t noise;
    if (noise_unsigned > q / 2) { noise = static_cast<int64_t>(noise_unsigned) - static_cast<int64_t>(q); } 
    else { noise = static_cast<int64_t>(noise_unsigned); }
    std::cout << "Noise value: " << noise << std::endl;
    if (std::abs(noise) <= 5) { std::cout << "SUCCESS: Decryption is correct for " << expected_msg << "!" << std::endl; } 
    else { std::cout << "FAILURE: Decryption is incorrect for " << expected_msg << ". Noise is too large." << std::endl; }
}