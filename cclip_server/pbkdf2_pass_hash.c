#include "pbkdf2_pass_hash.h"
#include <openssl/evp.h>
#include <openssl/rand.h>

int generate_salt(unsigned char *salt, 
	int len) 
{
	return RAND_bytes(salt, len);
}
int hash_new_pass(const char *pass, 
	unsigned char *salt, 
	int salt_len, 
	unsigned char *passHash, 
	int hash_len) {
	int res;
	res = generate_salt(salt, salt_len);
	if (res == 1)
		res = hash_pass(pass, salt, salt_len, passHash, hash_len);
	return res;
}
int hash_pass(const char *pass, 
	const unsigned char *salt, 
	int salt_len, 
	unsigned char *passHash, 
	int hash_len) 
{
	const int iteration = 256000;
	return PKCS5_PBKDF2_HMAC(pass, -1, salt, salt_len, iteration, EVP_sha512(), hash_len, passHash);
}
