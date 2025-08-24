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

// A new, simpler, and more robust helper function for verification
void verify_decryption(
    const std::string& label,
    uint64_t expected_msg,
    const Polynomial& decrypted_poly,
    const Parameters& params
) {
    std::cout << "\nVerifying '" << label << "'..." << std::endl;
    uint64_t noisy_message = decrypted_poly.coefficients[0];
    uint64_t q = params.ciphertext_modulus;

    std::cout << "Decrypted value (with noise): " << noisy_message << std::endl;

    // This correctly calculates the noise value by finding the shortest
    // distance in the modular ring Z_q.
    uint64_t noise_unsigned = (noisy_message + q - (expected_msg % q)) % q;
    
    int64_t noise;
    if (noise_unsigned > q / 2) {
        noise = static_cast<int64_t>(noise_unsigned) - static_cast<int64_t>(q);
    } else {
        noise = static_cast<int64_t>(noise_unsigned);
    }
    
    std::cout << "Noise value: " << noise << std::endl;
    
    // For our parameters, noise should be small.
    if (std::abs(noise) <= 5) {
        std::cout << "SUCCESS: Decryption is correct for " << expected_msg << "!" << std::endl;
    } else {
        std::cout << "FAILURE: Decryption is incorrect for " << expected_msg << ". Noise is too large." << std::endl;
    }
}

int main() {
    std::cout << "--- FHE Framework: Noise Debugging ---" << std::endl;

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

    // 2. Encrypt m1 and immediately decrypt to check its noise
    uint64_t m1 = 2;
    Polynomial p1; p1.coefficients.push_back(m1);
    Ciphertext ct1;
    encryptor.encrypt(p1, ct1);
    std::cout << "\nEncrypting m1 = " << m1;

    Polynomial decrypted_p1;
    decryptor.decrypt(ct1, decrypted_p1);
    verify_decryption("Fresh decryption of m1", m1, decrypted_p1, params);

    // 3. Encrypt m2 and immediately decrypt to check its noise
    uint64_t m2 = 3;
    Polynomial p2; p2.coefficients.push_back(m2);
    Ciphertext ct2;
    encryptor.encrypt(p2, ct2);
    std::cout << "\nEncrypting m2 = " << m2;

    Polynomial decrypted_p2;
    decryptor.decrypt(ct2, decrypted_p2);
    verify_decryption("Fresh decryption of m2", m2, decrypted_p2, params);

    // 4. Perform homomorphic addition and check the final noise
    Ciphertext ct_add;
    evaluator.add(ct1, ct2, ct_add);
    std::cout << "\nHomomorphic addition complete.";
    
    Polynomial decrypted_sum;
    decryptor.decrypt(ct_add, decrypted_sum);
    verify_decryption("m1 + m2", m1 + m2, decrypted_sum, params);
    
    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}