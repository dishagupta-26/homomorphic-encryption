 
#include "api/context.h"
#include "scheme/params.h"
#include "scheme/keys.h"
#include "scheme/keygenerator.h"
#include "scheme/encryptor.h"
#include "scheme/decryptor.h"
#include "scheme/evaluator.h"
#include "math/polynomial.h"

FHE::FHE(const Parameters& params) : params(params) {
    // Allocate memory for our internal objects
    secret_key = new SecretKey();
    public_key = new PublicKey();
    keygen = new KeyGenerator(params);
    // Encryptor, Decryptor, and Evaluator can only be created after keys are generated
    encryptor = nullptr;
    decryptor = nullptr;
    evaluator = new Evaluator(params);
}

FHE::~FHE() {
    // Clean up memory
    delete secret_key;
    delete public_key;
    delete keygen;
    delete encryptor;
    delete decryptor;
    delete evaluator;
}

void FHE::generate_keys() {
    keygen->generate(*secret_key, *public_key);
    // Now that we have keys, we can create the other objects
    encryptor = new Encryptor(params, *public_key);
    decryptor = new Decryptor(params, *secret_key);
}

Ciphertext FHE::encrypt(int64_t message) {
    Polynomial plain_poly;
    // Handle negative messages correctly
    plain_poly.coefficients.push_back((message < 0) ? params.ciphertext_modulus + message : message);
    Ciphertext ciphertext;
    encryptor->encrypt(plain_poly, ciphertext);
    return ciphertext;
}

int64_t FHE::decrypt(const Ciphertext& ciphertext) {
    Polynomial plain_poly;
    decryptor->decrypt(ciphertext, plain_poly);
    
    uint64_t noisy_message = plain_poly.coefficients[0];
    uint64_t q = params.ciphertext_modulus;
    uint64_t half_q = q / 2;

    if (noisy_message > half_q) {
        // The value represents a small negative number
        return static_cast<int64_t>(noisy_message) - static_cast<int64_t>(q);
    } else {
        // The value represents a small positive number
        return static_cast<int64_t>(noisy_message);
    }
}

Ciphertext FHE::add(const Ciphertext& ct1, const Ciphertext& ct2) {
    Ciphertext result_ct;
    evaluator->add(ct1, ct2, result_ct);
    return result_ct;
}