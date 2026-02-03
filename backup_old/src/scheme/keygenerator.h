#pragma once
#include "scheme/params.h"
#include "scheme/keys.h"      // <-- This is the critical line that fixes the error

class KeyGenerator {
public:
    KeyGenerator(const Parameters& params);
    void generate(SecretKey& secret_key, PublicKey& public_key);
private:
    const Parameters& params;
};