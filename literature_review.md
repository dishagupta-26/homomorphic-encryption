# Post-Quantum Cryptography Fully Homomorphic Encryption Framework  
## 📚 Literature Review

---

## 1. Objective
Brief overview of the aim of this literature review and how it will guide the development of the FHE framework.

> Example:  
> To understand the design decisions, encryption schemes, and performance characteristics of existing FHE libraries and lattice-based cryptographic foundations, guiding the development of an indigenous, modular FHE library.

---

## 2. Studied Libraries and Frameworks

### 🔹 OpenFHE
- **URL:** https://github.com/openfheorg/openfhe-development  
- **Encryption Schemes Supported:** CKKS, BFV, BGV  
- **Strengths:**
  - Modular and extensible architecture
  - Active development and strong community support
- **Limitations:**
  - Steep learning curve
  - Complex setup and integration

> Key Learnings:
- [ ] Design structure and modularity
- [ ] Bootstrapping implementation
- [ ] Key switching and noise management

---

### 🔹 Microsoft SEAL
- **URL:** https://github.com/microsoft/SEAL  
- **Encryption Schemes:** BFV, CKKS  
- **Strengths:**
  - High performance
  - Well-documented
- **Limitations:**
  - Less modular than OpenFHE
  - Lacks native bootstrapping

> Key Learnings:
- [ ] Encoding and parameter tuning
- [ ] Polynomial arithmetic design
- [ ] Practical API usability

---

### 🔹 HElib
- **URL:** https://github.com/homenc/HElib  
- **Encryption Schemes:** BGV  
- **Strengths:**
  - Deep academic roots
  - Built-in bootstrapping
- **Limitations:**
  - Older codebase
  - More complex than SEAL for new developers

> Key Learnings:
- [ ] Handling complex ciphertext structures
- [ ] Bootstrapping logic and circuit evaluation
- [ ] Modulus switching techniques

---

## 3. Cryptographic Foundations

### 🔸 Ring-LWE (Learning With Errors over Rings)
- **Description:**  
  A hardness assumption over polynomial rings with noise, forming the basis of lattice cryptography.
- **Mathematical Foundation:**  
  - Polynomial ring: \(\mathbb{Z}_q[x]/(x^n + 1)\)
  - Error term introduces controlled noise
- **Applications:** Keygen, encryption/decryption primitives

---

### 🔸 CKKS Scheme (Approximate HE)
- **Purpose:** Real number operations (e.g., for ML)
- **Properties:** Supports approximate arithmetic
- **Use Case Fit:** Encrypted linear regression

---

### 🔸 BFV Scheme (Exact Integer HE)
- **Purpose:** Integer operations with exactness
- **Properties:** Better suited for logic-based FHE applications

---

### 🔸 Number Theoretic Transform (NTT)
- **Purpose:** Fast polynomial multiplication in finite fields
- **Relation to FFT:** NTT is modular FFT using primitive roots of unity
- **Importance in FHE:** Enables efficient ciphertext multiplication

---

## 4. Observations and Design Insights

| Feature                | OpenFHE         | SEAL             | HElib            |
|------------------------|-----------------|------------------|------------------|
| Modularity             | ✅ High         | ⚠️ Medium        | ⚠️ Low           |
| Bootstrapping Support  | ✅ Yes          | ❌ No            | ✅ Yes           |
| Learning Curve         | ❌ Steep        | ✅ Moderate      | ❌ Complex        |
| Supported Schemes      | CKKS, BFV, BGV  | CKKS, BFV        | BGV              |

---

## 5. Summary and Recommendations

- **Library to Model Architecture On:** OpenFHE (for modularity)
- **Scheme for Demo Use Case:** CKKS (for real-valued ML use case)
- **Mathematical Foundation:** Start with Ring-LWE and NTT-based multiplication
- **Bootstrapping:** Optional phase after core functions

---

## 6. References
- [OpenFHE Docs](https://openfhe-development.readthedocs.io/en/latest/)
- [Microsoft SEAL Manual](https://www.microsoft.com/en-us/research/project/microsoft-seal/)
- [HElib Paper](https://eprint.iacr.org/2013/420)
- [Lattice Cryptography Notes](https://crypto.stanford.edu/pbc/notes/crypto/lattice.html)
- [CKKS Original Paper](https://eprint.iacr.org/2016/421)

---
