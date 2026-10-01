#include "hash.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E;
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = (B & C) | (C & D);

            unsigned char old_A = A;
            unsigned char old_B = B;
            unsigned char old_E = E;

            A = old_B;
            B = old_A;
            C = (old_B >> 1) + old_E;
            D = (old_A >> 2) ^ g;
            E = g + msg[i];
        }
    }

    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    if (digest) {
        digest[0] = A;
        digest[1] = B;
        digest[2] = C;
        digest[3] = D;
        digest[4] = E;
    }

    return digest;
}

unsigned char* SSHA2(const unsigned char* msg, size_t length) {
    unsigned char A = 0, B = 0, C = 0, D = 0, E = 0;
    size_t i;
    
    for (i = 0; i < length; ++i) {
        unsigned char F = (B & C) | (C & D);
        unsigned char b_shr1 = B >> 1;
        unsigned char a_shr2 = A >> 2;
        
        unsigned char new_A = F + E + msg[i];
        unsigned char new_B = A;
        unsigned char new_C = b_shr1 + F;
        unsigned char new_D = a_shr2 ^ b_shr1;
        unsigned char new_E = D;
        
        A = new_A;
        B = new_B;
        C = new_C;
        D = new_D;
        E = new_E;
    }
    
    unsigned char* hash = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    if (hash) {
        hash[0] = A;
        hash[1] = B;
        hash[2] = C;
        hash[3] = D;
        hash[4] = E;
    }
    return hash;
}

int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}