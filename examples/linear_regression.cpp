#include <iostream>
#include "scheme/params.h"
#include "scheme/keys.h"
#include "scheme/keygenerator.h"

int main() {
    std::cout << "--- FHE Framework: Key Generation Test ---" << std::endl;

    // 1. Set up parameters
    Parameters params;
    params.poly_modulus_degree = 8;
    params.ciphertext_modulus = 17;

    // 2. Create a KeyGenerator instance using our parameters
    KeyGenerator keygen(params);

    // 3. Create empty placeholder objects for the keys
    SecretKey secret_key;
    PublicKey public_key;

    // 4. Tell the key generator to create and fill the keys
    keygen.generate(secret_key, public_key);

    std::cout << "\nKey generation complete." << std::endl;
    std::cout << "Secret key 's' polynomial degree: " << secret_key.s.degree() << std::endl;
    std::cout << "Public key 'p0' polynomial degree: " << public_key.p0.degree() << std::endl;
    std::cout << "Public key 'p1' polynomial degree: " << public_key.p1.degree() << std::endl;

    // Let's peek at a sample coefficient to see that they are populated.
    // The actual values will be different each time you run the program.
    std::cout << "\nSample from s[0]: " << secret_key.s.coefficients[0] << std::endl;
    std::cout << "Sample from p1[0]: " << public_key.p1.coefficients[0] << std::endl;
    std::cout << "Sample from p0[0]: " << public_key.p0.coefficients[0] << std::endl;
    
    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}