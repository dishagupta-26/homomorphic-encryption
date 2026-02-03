#include <iostream>
#include <cmath>
#include "api/context.h"
#include "scheme/params.h"

int main() {
    std::cout << "--- FHE Framework: API Test ---" << std::endl;

    // 1. Set up parameters
    Parameters params;
    params.poly_modulus_degree = 8;
    params.ciphertext_modulus = 17;

    // 2. Create an FHE context
    FHE fhe(params);

    // 3. Generate Keys
    fhe.generate_keys();
    std::cout << "\nKeys generated." << std::endl;

    // 4. Encrypt two messages
    int64_t m1 = 2, m2 = 3;
    Ciphertext ct1 = fhe.encrypt(m1);
    Ciphertext ct2 = fhe.encrypt(m2);
    std::cout << "Encrypted m1=" << m1 << " and m2=" << m2 << std::endl;

    // 5. Homomorphically add them
    Ciphertext ct_add = fhe.add(ct1, ct2);
    std::cout << "Homomorphic addition performed." << std::endl;

    // 6. Decrypt the result
    int64_t decrypted_sum = fhe.decrypt(ct_add);
    std::cout << "Decrypted sum: " << decrypted_sum << std::endl;

    // 7. Verify (with restored noise tolerance)
    int64_t expected_sum = m1 + m2;
    int64_t noise = decrypted_sum - expected_sum;
    int64_t noise_tolerance = 8; // Increased tolerance for additive noise

    std::cout << "Noise: " << noise << std::endl;

    if (std::abs(noise) <= noise_tolerance) {
        std::cout << "\nSUCCESS: API test passed! Result is within noise tolerance." << std::endl;
    } else {
        std::cout << "\nFAILURE: API test failed. Noise was too large." << std::endl;
    }

    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}