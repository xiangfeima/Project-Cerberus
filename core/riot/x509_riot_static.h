// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef X509_RIOT_STATIC_H_
#define X509_RIOT_STATIC_H_

#include "x509_riot.h"


/* Internal functions declared to allow for static initialization. */
int x509_riot_create_csr (struct x509_engine *engine, const uint8_t *priv_key, size_t key_length,
	enum hash_type sig_hash, const char *name, int type, const char *eku,
	const struct x509_dice_tcbinfo *dice, uint8_t **csr, size_t *csr_length);
int x509_riot_create_self_signed_certificate (struct x509_engine *engine,
	struct x509_certificate *cert, const uint8_t *priv_key, size_t key_length,
	enum hash_type sig_hash, const uint8_t *serial_num, size_t serial_length, const char *name,
	int type, const struct x509_dice_tcbinfo *dice);
int x509_riot_create_ca_signed_certificate (struct x509_engine *engine,
	struct x509_certificate *cert, const uint8_t *key, size_t key_length, const uint8_t *serial_num,
	size_t serial_length, const char *name, int type, const uint8_t* ca_priv_key,
	size_t ca_key_length, enum hash_type sig_hash, const struct x509_certificate *ca_cert,
	const struct x509_dice_tcbinfo *dice);
int x509_riot_load_certificate (struct x509_engine *engine, struct x509_certificate *cert,
	const uint8_t *der, size_t length);
void x509_riot_release_certificate (struct x509_engine *engine, struct x509_certificate *cert);
int x509_riot_get_certificate_der (struct x509_engine *engine, const struct x509_certificate *cert,
	uint8_t **der, size_t *length);


/**
 * Constant initializer for certificate generation APIs.
 */
#ifdef X509_ENABLE_CREATE_CERTIFICATES
#define	X509_RIOT_CREATE_CERTIFICATES	\
	.create_csr = x509_riot_create_csr, \
	.create_self_signed_certificate = x509_riot_create_self_signed_certificate, \
	.create_ca_signed_certificate = x509_riot_create_ca_signed_certificate,

#define	X509_RIOT_DER_API \
	.get_certificate_der = x509_riot_get_certificate_der,
#else
#define	X509_RIOT_CREATE_CERTIFICATES
#define	X509_RIOT_DER_API
#endif

/**
 * Constant initializer for the ECC API.
 */
#define	X509_RIOT_API_INIT  { \
		X509_RIOT_CREATE_CERTIFICATES \
		.load_certificate = x509_riot_load_certificate, \
		.release_certificate = x509_riot_release_certificate, \
		X509_RIOT_DER_API \
	}


/**
 * Initialize a static instance for RSA signature verification.  This can be a constant instance.
 *
 * There is no validation done on the arguments.
 *
 * @param ecc_ptr The ECC engine to use for ECC key operations.
 * @param hash_ptr The hash engine to use for calculating digests.
 */
#define	x509_riot_static_init(ecc_ptr, hash_ptr)	{ \
		.base = X509_RIOT_API_INIT, \
		.ecc = ecc_ptr, \
		.hash = hash_ptr \
	}


#endif /* X509_RIOT_STATIC_H_ */
