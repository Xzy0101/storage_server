#pragma once

#ifndef PBKDF2_PASS_HASH_H
#define PBKDF2_PASS_HASH_H

#ifdef __cplusplus
extern "C" {
#endif
	
	int hash_new_pass(const char *pass, unsigned char *salt, int salt_len, unsigned char *passHash, int hash_len);
	int hash_pass(const char *pass, const unsigned char *salt, int salt_len, unsigned char *passHash, int hash_len);

#ifdef __cplusplus
}
#endif

#endif