#include <string.h>
#include "crypto.h"

void xorEncryptDecrypt(char *data, const char *key, int length) {
    int keyLength = strlen(key);
    for (int i = 0; i < length; i++) {
        data[i] ^= key[i % keyLength]; // XOR each character with the key
    }
}