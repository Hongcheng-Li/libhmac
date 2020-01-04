/*
 * Library SHA-256 context type testing program
 *
 * Copyright (C) 2011-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H )
#include <openssl/sha.h>

#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H )
#include <openssl/evp.h>
#endif

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU
#endif

#include "hmac_test_libcerror.h"
#include "hmac_test_libhmac.h"
#include "hmac_test_macros.h"
#include "hmac_test_memory.h"
#include "hmac_test_unused.h"

/* Make sure libhmac_sha256.h is included to define LIBHMAC_HAVE_SHA256_SUPPORT
 */
#include "../libhmac/libhmac_sha256.h"

typedef struct hmac_test_sha256_test_vector hmac_test_sha256_test_vector_t;

struct hmac_test_sha256_test_vector
{
	/* The description
	 */
	const char *description;

	/* The key
	 */
	uint8_t key[ 144 ];

	/* The key size
	 */
	size_t key_size;

	/* The data
	 */
	uint8_t data[ 164 ];

	/* The data size
	 */
	size_t data_size;

	/* The expected hmac
	 */
	uint8_t hmac[ LIBHMAC_SHA256_HASH_SIZE ];

	/* The hmac size
	 */
	size_t hmac_size;
};

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )

static int (*hmac_test_real_SHA256_Init)(SHA256_CTX *)                                         = NULL;
static int (*hmac_test_real_SHA256_Update)(SHA256_CTX *, const void *, unsigned long)          = NULL;
static int (*hmac_test_real_SHA256_Final)(unsigned char *, SHA256_CTX *)                       = NULL;

int hmac_test_SHA256_Init_attempts_before_fail                                                 = -1;
int hmac_test_SHA256_Update_attempts_before_fail                                               = -1;
int hmac_test_SHA256_Final_attempts_before_fail                                                = -1;

#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )

static int (*hmac_test_real_EVP_DigestInit_ex)(EVP_MD_CTX *, const EVP_MD *, ENGINE *)         = NULL;
static int (*hmac_test_real_EVP_DigestUpdate)(EVP_MD_CTX *, const void *, size_t)              = NULL;
static int (*hmac_test_real_EVP_DigestFinal_ex)(EVP_MD_CTX *, unsigned char *, unsigned int *) = NULL;

int hmac_test_EVP_DigestInit_ex_attempts_before_fail                                           = -1;
int hmac_test_EVP_DigestUpdate_attempts_before_fail                                            = -1;
int hmac_test_EVP_DigestFinal_ex_attempts_before_fail                                          = -1;

#endif /* defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH ) */

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )

/* Custom SHA256_Init for testing error cases
 * Returns 1 if successful or 0 otherwise
 */
int SHA256_Init(
     SHA256_CTX *c )
{
	int result = 0;

	if( hmac_test_real_SHA256_Init == NULL )
	{
		hmac_test_real_SHA256_Init = dlsym(
		                              RTLD_NEXT,
		                              "SHA256_Init" );
	}
	if( hmac_test_SHA256_Init_attempts_before_fail == 0 )
	{
		hmac_test_SHA256_Init_attempts_before_fail = -1;

		return( 0 );
	}
	else if( hmac_test_SHA256_Init_attempts_before_fail > 0 )
	{
		hmac_test_SHA256_Init_attempts_before_fail--;
	}
	result = hmac_test_real_SHA256_Init(
	          c );

	return( result );
}

/* Custom SHA256_Update for testing error cases
 * Returns 1 if successful or 0 otherwise
 */
int SHA256_Update(
     SHA256_CTX *c,
     const void *data,
     unsigned long len )
{
	int result = 0;

	if( hmac_test_real_SHA256_Update == NULL )
	{
		hmac_test_real_SHA256_Update = dlsym(
		                                RTLD_NEXT,
		                                "SHA256_Update" );
	}
	if( hmac_test_SHA256_Update_attempts_before_fail == 0 )
	{
		hmac_test_SHA256_Update_attempts_before_fail = -1;

		return( 0 );
	}
	else if( hmac_test_SHA256_Update_attempts_before_fail > 0 )
	{
		hmac_test_SHA256_Update_attempts_before_fail--;
	}
	result = hmac_test_real_SHA256_Update(
	          c,
	          data,
	          len );

	return( result );
}

/* Custom SHA256_Final for testing error cases
 * Returns 1 if successful or 0 otherwise
 */
int SHA256_Final(
     unsigned char *md,
     SHA256_CTX *c )
{
	int result = 0;

	if( hmac_test_real_SHA256_Final == NULL )
	{
		hmac_test_real_SHA256_Final = dlsym(
		                               RTLD_NEXT,
		                               "SHA256_Final" );
	}
	if( hmac_test_SHA256_Final_attempts_before_fail == 0 )
	{
		hmac_test_SHA256_Final_attempts_before_fail = -1;

		return( 0 );
	}
	else if( hmac_test_SHA256_Final_attempts_before_fail > 0 )
	{
		hmac_test_SHA256_Final_attempts_before_fail--;
	}
	result = hmac_test_real_SHA256_Final(
	          md,
	          c );

	return( result );
}

#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )

/* Custom EVP_DigestInit_ex for testing error cases
 * Returns 1 if successful or 0 otherwise
 */
int EVP_DigestInit_ex(
     EVP_MD_CTX *ctx,
     const EVP_MD *type,
     ENGINE *impl )
{
	int result = 0;

	if( hmac_test_real_EVP_DigestInit_ex == NULL )
	{
		hmac_test_real_EVP_DigestInit_ex = dlsym(
		                                    RTLD_NEXT,
		                                    "EVP_DigestInit_ex" );
	}
	if( hmac_test_EVP_DigestInit_ex_attempts_before_fail == 0 )
	{
		hmac_test_EVP_DigestInit_ex_attempts_before_fail = -1;

		return( 0 );
	}
	else if( hmac_test_EVP_DigestInit_ex_attempts_before_fail > 0 )
	{
		hmac_test_EVP_DigestInit_ex_attempts_before_fail--;
	}
	result = hmac_test_real_EVP_DigestInit_ex(
	          ctx,
	          type,
	          impl );

	return( result );
}

/* Custom EVP_DigestUpdate for testing error cases
 * Returns 1 if successful or 0 otherwise
 */
int EVP_DigestUpdate(
     EVP_MD_CTX *ctx,
     const void *d,
     size_t cnt )
{
	int result = 0;

	if( hmac_test_real_EVP_DigestUpdate == NULL )
	{
		hmac_test_real_EVP_DigestUpdate = dlsym(
		                                   RTLD_NEXT,
		                                   "EVP_DigestUpdate" );
	}
	if( hmac_test_EVP_DigestUpdate_attempts_before_fail == 0 )
	{
		hmac_test_EVP_DigestUpdate_attempts_before_fail = -1;

		return( 0 );
	}
	else if( hmac_test_EVP_DigestUpdate_attempts_before_fail > 0 )
	{
		hmac_test_EVP_DigestUpdate_attempts_before_fail--;
	}
	result = hmac_test_real_EVP_DigestUpdate(
	          ctx,
	          d,
	          cnt );

	return( result );
}

/* Custom EVP_DigestFinal_ex for testing error cases
 * Returns 1 if successful or 0 otherwise
 */
int EVP_DigestFinal_ex(
     EVP_MD_CTX *ctx,
     unsigned char *md,
     unsigned int *s )
{
	int result = 0;

	if( hmac_test_real_EVP_DigestFinal_ex == NULL )
	{
		hmac_test_real_EVP_DigestFinal_ex = dlsym(
		                                     RTLD_NEXT,
		                                     "EVP_DigestFinal_ex" );
	}
	if( hmac_test_EVP_DigestFinal_ex_attempts_before_fail == 0 )
	{
		hmac_test_EVP_DigestFinal_ex_attempts_before_fail = -1;

		return( 0 );
	}
	else if( hmac_test_EVP_DigestFinal_ex_attempts_before_fail > 0 )
	{
		hmac_test_EVP_DigestFinal_ex_attempts_before_fail--;
	}
	result = hmac_test_real_EVP_DigestFinal_ex(
	          ctx,
	          md,
	          s );

	return( result );
}

#endif /* defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH ) */

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

/* Tests the libhmac_sha256_initialize function
 * Returns 1 if successful or 0 if not
 */
int hmac_test_sha256_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libhmac_sha256_context_t *context = NULL;
	int result                        = 0;

#if defined( HAVE_HMAC_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test libhmac_sha256_initialize without entries
	 */
	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "context",
	 context );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhmac_sha256_free(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "context",
	 context );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhmac_sha256_initialize(
	          NULL,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	context = (libhmac_sha256_context_t *) 0x12345678UL;

	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	context = NULL;

#if defined( HAVE_HMAC_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libhmac_sha256_initialize with malloc failing
		 */
		hmac_test_malloc_attempts_before_fail = test_number;

		result = libhmac_sha256_initialize(
		          &context,
		          &error );

		if( hmac_test_malloc_attempts_before_fail != -1 )
		{
			hmac_test_malloc_attempts_before_fail = -1;

			if( context != NULL )
			{
				libhmac_sha256_free(
				 &context,
				 NULL );
			}
		}
		else
		{
			HMAC_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			HMAC_TEST_ASSERT_IS_NULL(
			 "context",
			 context );

			HMAC_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libhmac_sha256_initialize with memset failing
		 */
		hmac_test_memset_attempts_before_fail = test_number;

		result = libhmac_sha256_initialize(
		          &context,
		          &error );

		if( hmac_test_memset_attempts_before_fail != -1 )
		{
			hmac_test_memset_attempts_before_fail = -1;

			if( context != NULL )
			{
				libhmac_sha256_free(
				 &context,
				 NULL );
			}
		}
		else
		{
			HMAC_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			HMAC_TEST_ASSERT_IS_NULL(
			 "context",
			 context );

			HMAC_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_HMAC_TEST_MEMORY ) */

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libhmac_sha256_initialize with SHA256_Init failing
	 */
	hmac_test_SHA256_Init_attempts_before_fail = 0;

	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	if( hmac_test_SHA256_Init_attempts_before_fail != -1 )
	{
		hmac_test_SHA256_Init_attempts_before_fail = -1;

		if( context != NULL )
		{
			libhmac_sha256_free(
			 &context,
			 NULL );
		}
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NULL(
		 "context",
		 context );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libhmac_sha256_initialize with EVP_DigestInit_ex failing
	 */
	hmac_test_EVP_DigestInit_ex_attempts_before_fail = 0;

	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	if( hmac_test_EVP_DigestInit_ex_attempts_before_fail != -1 )
	{
		hmac_test_EVP_DigestInit_ex_attempts_before_fail = -1;

		if( context != NULL )
		{
			libhmac_sha256_free(
			 &context,
			 NULL );
		}
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NULL(
		 "context",
		 context );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#else
#if defined( HAVE_CAES_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libhmac_sha256_initialize with memcpy failing
	 */
	hmac_test_memcpy_attempts_before_fail = 0;

	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	if( hmac_test_memcpy_attempts_before_fail != -1 )
	{
		hmac_test_memcpy_attempts_before_fail = -1;

		if( context != NULL )
		{
			libhmac_sha256_free(
			 &context,
			 NULL );
		}
	}
	else
	{
		CAES_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NULL(
		 "context",
		 context );

		CAES_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CAES_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */

#endif /* defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( context != NULL )
	{
		libhmac_sha256_free(
		 &context,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhmac_sha256_free function
 * Returns 1 if successful or 0 if not
 */
int hmac_test_sha256_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libhmac_sha256_free(
	          NULL,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhmac_sha256_update function
 * Returns 1 if successful or 0 if not
 */
int hmac_test_sha256_update(
     void )
{
	uint8_t data[ 208 ];

	libcerror_error_t *error          = NULL;
	libhmac_sha256_context_t *context = NULL;
	size_t maximum_size               = 0;
	int result                        = 0;

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )
#if ( SIZEOF_LONG < SIZEOF_SIZE_T )
	maximum_size = (size_t) ULONG_MAX;
#else
	maximum_size = (size_t) SSIZE_MAX;
#endif
#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )
	maximum_size = (size_t) SSIZE_MAX;
#else
	maximum_size = (size_t) SSIZE_MAX;
#endif

	/* Initialize test
	 */
	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "context",
	 context );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libhmac_sha256_update(
	          context,
	          data,
	          208,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhmac_sha256_update(
	          context,
	          data,
	          0,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhmac_sha256_update(
	          NULL,
	          data,
	          208,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhmac_sha256_update(
	          context,
	          NULL,
	          208,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( maximum_size > 0 )
	{
		result = libhmac_sha256_update(
		          context,
		          data,
		          maximum_size + 1,
		          &error );

		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libhmac_sha256_update with SHA256_Update failing
	 */
	hmac_test_SHA256_Update_attempts_before_fail = 0;

	result = libhmac_sha256_update(
	          context,
	          data,
	          208,
	          &error );

	if( hmac_test_SHA256_Update_attempts_before_fail != -1 )
	{
		hmac_test_SHA256_Update_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libhmac_sha256_update with EVP_DigestUpdate failing
	 */
	hmac_test_EVP_DigestUpdate_attempts_before_fail = 0;

	result = libhmac_sha256_update(
	          context,
	          data,
	          208,
	          &error );

	if( hmac_test_EVP_DigestUpdate_attempts_before_fail != -1 )
	{
		hmac_test_EVP_DigestUpdate_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#else
#if defined( HAVE_CAES_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED )

	/* Test libhmac_sha256_update with memcpy failing
	 */
	hmac_test_memcpy_attempts_before_fail = 0;

	result = libhmac_sha256_update(
	          context,
	          data,
	          208,
	          &error );

	if( hmac_test_memcpy_attempts_before_fail != -1 )
	{
		hmac_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		CAES_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CAES_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libhmac_sha256_update with memcpy failing
	 */
	hmac_test_memcpy_attempts_before_fail = 1;

	result = libhmac_sha256_update(
	          context,
	          data,
	          208,
	          &error );

	if( hmac_test_memcpy_attempts_before_fail != -1 )
	{
		hmac_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		CAES_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CAES_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CAES_TEST_MEMORY ) && defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH ) */

	/* Clean up
	 */
	result = libhmac_sha256_free(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "context",
	 context );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( context != NULL )
	{
		libhmac_sha256_free(
		 &context,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhmac_sha256_finalize function
 * Returns 1 if successful or 0 if not
 */
int hmac_test_sha256_finalize(
     void )
{
	uint8_t hash[ LIBHMAC_SHA256_HASH_SIZE ];

	libcerror_error_t *error          = NULL;
	libhmac_sha256_context_t *context = NULL;
	size_t maximum_size               = 0;
	int result                        = 0;

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )
	maximum_size = (size_t) SSIZE_MAX;
#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )
	maximum_size = (size_t) UINT_MAX;
#else
	maximum_size = (size_t) SSIZE_MAX;
#endif

	/* Initialize test
	 */
	result = libhmac_sha256_initialize(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "context",
	 context );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libhmac_sha256_finalize(
	          context,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhmac_sha256_finalize(
	          NULL,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhmac_sha256_finalize(
	          context,
	          NULL,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( maximum_size > 0 )
	{
		result = libhmac_sha256_finalize(
		          context,
		          hash,
		          maximum_size + 1,
		          &error );

		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	result = libhmac_sha256_finalize(
	          context,
	          hash,
	          0,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH )

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libhmac_sha256_finalize with SHA256_Final failing
	 */
	hmac_test_SHA256_Final_attempts_before_fail = 0;

	result = libhmac_sha256_finalize(
	          context,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	if( hmac_test_SHA256_Final_attempts_before_fail != -1 )
	{
		hmac_test_SHA256_Final_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#elif defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H ) && defined( HAVE_EVP_SHA256 )

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ )

	/* Test libhmac_sha256_finalize with EVP_DigestFinal_ex failing
	 */
	hmac_test_EVP_DigestFinal_ex_attempts_before_fail = 0;

	result = libhmac_sha256_finalize(
	          context,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	if( hmac_test_EVP_DigestFinal_ex_attempts_before_fail != -1 )
	{
		hmac_test_EVP_DigestFinal_ex_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) && !defined( __CYGWIN__ ) */

#else
#if defined( HAVE_HMAC_TEST_MEMORY )
#if defined( OPTIMIZATION_DISABLED )

	/* Test libhmac_sha256_finalize with memset of internal_context->block failing
	 */
	hmac_test_memset_attempts_before_fail = 0;

	result = libhmac_sha256_finalize(
	          context,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	if( hmac_test_memset_attempts_before_fail != -1 )
	{
		hmac_test_memset_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */

	/* Test libhmac_sha256_finalize with memset of internal_context failing
	 */
	hmac_test_memset_attempts_before_fail = 1;

	result = libhmac_sha256_finalize(
	          context,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	if( hmac_test_memset_attempts_before_fail != -1 )
	{
		hmac_test_memset_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_HMAC_TEST_MEMORY ) */
#endif /* defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_SHA_H ) && defined( SHA256_DIGEST_LENGTH ) */

	/* Clean up
	 */
	result = libhmac_sha256_free(
	          &context,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "context",
	 context );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( context != NULL )
	{
		libhmac_sha256_free(
		 &context,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhmac_sha256_calculate function
 * Returns 1 if successful or 0 if not
 */
int hmac_test_sha256_calculate(
     void )
{
	uint8_t data[ 208 ];
	uint8_t hash[ LIBHMAC_SHA256_HASH_SIZE ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libhmac_sha256_calculate(
	          data,
	          208,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HMAC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
#if defined( HAVE_HMAC_TEST_MEMORY )

	/* Test libhmac_sha256_calculate with malloc failing in libhmac_sha256_initialize
	 */
	hmac_test_malloc_attempts_before_fail = 0;

	result = libhmac_sha256_calculate(
	          data,
	          208,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	if( hmac_test_malloc_attempts_before_fail != -1 )
	{
		hmac_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_HMAC_TEST_MEMORY ) */

	/* Test libhmac_sha256_calculate with libhmac_sha256_update failing
	 */
	result = libhmac_sha256_calculate(
	          NULL,
	          208,
	          hash,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test libhmac_sha256_calculate with libhmac_sha256_finalize failing
	 */
	result = libhmac_sha256_calculate(
	          data,
	          208,
	          NULL,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhmac_sha256_calculate_hmac function
 * Returns 1 if successful or 0 if not
 */
int hmac_test_sha256_calculate_hmac(
     void )
{
	uint8_t hmac[ LIBHMAC_SHA256_HASH_SIZE ];

	hmac_test_sha256_test_vector_t test_vectors[ 7 ] = {
		/* RFC 4231 test vectors
		 */
		{ "RFC 4231 test vector 1",
                  { 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
		    0x0b, 0x0b, 0x0b, 0x0b }, 20,
		  { 'H', 'i', ' ', 'T', 'h', 'e', 'r', 'e' }, 8,
		  { 0xb0, 0x34, 0x4c, 0x61, 0xd8, 0xdb, 0x38, 0x53, 0x5c, 0xa8, 0xaf, 0xce, 0xaf, 0x0b, 0xf1, 0x2b,
		    0x88, 0x1d, 0xc2, 0x00, 0xc9, 0x83, 0x3d, 0xa7, 0x26, 0xe9, 0x37, 0x6c, 0x2e, 0x32, 0xcf, 0xf7 }, 32 },
		{ "RFC 4231 test vector 2",
                  { 'J', 'e', 'f', 'e' }, 4,
                  { 'w', 'h', 'a', 't', ' ', 'd', 'o', ' ', 'y', 'a', ' ', 'w', 'a', 'n', 't', ' ',
		    'f', 'o', 'r', ' ', 'n', 'o', 't', 'h', 'i', 'n', 'g', '?' }, 28,
		  { 0x5b, 0xdc, 0xc1, 0x46, 0xbf, 0x60, 0x75, 0x4e, 0x6a, 0x04, 0x24, 0x26, 0x08, 0x95, 0x75, 0xc7,
		    0x5a, 0x00, 0x3f, 0x08, 0x9d, 0x27, 0x39, 0x83, 0x9d, 0xec, 0x58, 0xb9, 0x64, 0xec, 0x38, 0x43 }, 32 },
		{ "RFC 4231 test vector 3",
                  { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		    0xaa, 0xaa, 0xaa, 0xaa }, 20,
                  { 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
		    0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
		    0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
		    0xdd, 0xdd }, 50,
		  { 0x77, 0x3e, 0xa9, 0x1e, 0x36, 0x80, 0x0e, 0x46, 0x85, 0x4d, 0xb8, 0xeb, 0xd0, 0x91, 0x81, 0xa7,
		    0x29, 0x59, 0x09, 0x8b, 0x3e, 0xf8, 0xc1, 0x22, 0xd9, 0x63, 0x55, 0x14, 0xce, 0xd5, 0x65, 0xfe }, 32 },
		{ "RFC 4231 test vector 4",
		  { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
		    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19 }, 25,
                  { 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
		    0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
		    0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
		    0xcd, 0xcd }, 50,
		  { 0x82, 0x55, 0x8a, 0x38, 0x9a, 0x44, 0x3c, 0x0e, 0xa4, 0xcc, 0x81, 0x98, 0x99, 0xf2, 0x08, 0x3a,
		    0x85, 0xf0, 0xfa, 0xa3, 0xe5, 0x78, 0xf8, 0x07, 0x7a, 0x2e, 0x3f, 0xf4, 0x67, 0x29, 0x66, 0x5b }, 32 },
		{ "RFC 4231 test vector 5",
                  { 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
		    0x0c, 0x0c, 0x0c, 0x0c }, 20,
		  { 'T', 'e', 's', 't', ' ', 'W', 'i', 't', 'h', ' ', 'T', 'r', 'u', 'n', 'c', 'a',
		    't', 'i', 'o', 'n' }, 20,
		  { 0xa3, 0xb6, 0x16, 0x74, 0x73, 0x10, 0x0e, 0xe0, 0x6e, 0x0c, 0x79, 0x6c, 0x29, 0x55, 0x55, 0x2b }, 16 },
		{ "RFC 4231 test vector 6",
                  { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		    0xaa, 0xaa, 0xaa }, 131,
		  { 'T', 'e', 's', 't', ' ', 'U', 's', 'i', 'n', 'g', ' ', 'L', 'a', 'r', 'g', 'e',
		    'r', ' ', 'T', 'h', 'a', 'n', ' ', 'B', 'l', 'o', 'c', 'k', '-', 'S', 'i', 'z',
		    'e', ' ', 'K', 'e', 'y', ' ', '-', ' ', 'H', 'a', 's', 'h', ' ', 'K', 'e', 'y',
		    ' ', 'F', 'i', 'r', 's', 't' }, 54,
		  { 0x60, 0xe4, 0x31, 0x59, 0x1e, 0xe0, 0xb6, 0x7f, 0x0d, 0x8a, 0x26, 0xaa, 0xcb, 0xf5, 0xb7, 0x7f,
		    0x8e, 0x0b, 0xc6, 0x21, 0x37, 0x28, 0xc5, 0x14, 0x05, 0x46, 0x04, 0x0f, 0x0e, 0xe3, 0x7f, 0x54 }, 32 },
		{ "RFC 4231 test vector 7",
                  { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		    0xaa, 0xaa, 0xaa }, 131,
		  { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't', ' ', 'u',
		    's', 'i', 'n', 'g', ' ', 'a', ' ', 'l', 'a', 'r', 'g', 'e', 'r', ' ', 't', 'h',
		    'a', 'n', ' ', 'b', 'l', 'o', 'c', 'k', '-', 's', 'i', 'z', 'e', ' ', 'k', 'e',
		    'y', ' ', 'a', 'n', 'd', ' ', 'a', ' ', 'l', 'a', 'r', 'g', 'e', 'r', ' ', 't',
		    'h', 'a', 'n', ' ', 'b', 'l', 'o', 'c', 'k', '-', 's', 'i', 'z', 'e', ' ', 'd',
		    'a', 't', 'a', '.', ' ', 'T', 'h', 'e', ' ', 'k', 'e', 'y', ' ', 'n', 'e', 'e',
		    'd', 's', ' ', 't', 'o', ' ', 'b', 'e', ' ', 'h', 'a', 's', 'h', 'e', 'd', ' ',
		    'b', 'e', 'f', 'o', 'r', 'e', ' ', 'b', 'e', 'i', 'n', 'g', ' ', 'u', 's', 'e',
		    'd', ' ', 'b', 'y', ' ', 't', 'h', 'e', ' ', 'H', 'M', 'A', 'C', ' ', 'a', 'l',
		    'g', 'o', 'r', 'i', 't', 'h', 'm', '.' }, 152,
		  { 0x9b, 0x09, 0xff, 0xa7, 0x1b, 0x94, 0x2f, 0xcb, 0x27, 0x63, 0x5f, 0xbc, 0xd5, 0xb0, 0xe9, 0x44,
		    0xbf, 0xdc, 0x63, 0x64, 0x4f, 0x07, 0x13, 0x93, 0x8a, 0x7f, 0x51, 0x53, 0x5c, 0x3a, 0x35, 0xe2 }, 32 },
	};

	libcerror_error_t *error = NULL;
	int result               = 0;
	int test_number          = 0;

	/* Test regular cases
	 */
	for( test_number = 0;
	     test_number < 7;
	     test_number++ )
	{
		result = libhmac_sha256_calculate_hmac(
		          test_vectors[ test_number ].key,
		          test_vectors[ test_number ].key_size,
		          test_vectors[ test_number ].data,
		          test_vectors[ test_number ].data_size,
		          hmac,
		          LIBHMAC_SHA256_HASH_SIZE,
		          &error );

		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		HMAC_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = memory_compare(
		          hmac,
		          test_vectors[ test_number ].hmac,
		          test_vectors[ test_number ].hmac_size );

		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );
	}
	/* Test error cases
	 */
	result = libhmac_sha256_calculate_hmac(
	          NULL,
	          test_vectors[ 0 ].key_size,
	          test_vectors[ 0 ].data,
	          test_vectors[ 0 ].data_size,
	          hmac,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhmac_sha256_calculate_hmac(
	          test_vectors[ 0 ].key,
	          (size_t) SSIZE_MAX + 1,
	          test_vectors[ 0 ].data,
	          test_vectors[ 0 ].data_size,
	          hmac,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhmac_sha256_calculate_hmac(
	          test_vectors[ 0 ].key,
	          test_vectors[ 0 ].key_size,
	          test_vectors[ 0 ].data,
	          test_vectors[ 0 ].data_size,
	          hmac,
	          0,
	          &error );

	HMAC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HMAC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_HMAC_TEST_MEMORY )

	/* Test libhmac_sha256_calculate_hmac with malloc failing
	 */
	hmac_test_malloc_attempts_before_fail = 0;

	result = libhmac_sha256_calculate_hmac(
	          test_vectors[ 0 ].key,
	          test_vectors[ 0 ].key_size,
	          test_vectors[ 0 ].data,
	          test_vectors[ 0 ].data_size,
	          hmac,
	          LIBHMAC_SHA256_HASH_SIZE,
	          &error );

	if( hmac_test_malloc_attempts_before_fail != -1 )
	{
		hmac_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		HMAC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HMAC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_HMAC_TEST_MEMORY ) */

/* TODO add tests for key_size <= block_size and memcpy failing */

/* TODO add tests for key_size <= block_size and memset failing */

/* TODO add tests for key_size > block_size and libhmac_sha256_initialize failing */

/* TODO add tests for key_size > block_size and libhmac_sha256_update failing */

/* TODO add tests for key_size > block_size and libhmac_sha256_finalize failing */

/* TODO add tests for key_size > block_size and memset failing */

/* TODO add tests for key_size > block_size and memcpy failing */

/* TODO add tests for malloc of inner_padding failing */

/* TODO add tests for memset of inner_padding failing */

/* TODO add tests for malloc of outer_padding failing */

/* TODO add tests for memset of outer_padding failing */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc HMAC_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] HMAC_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc HMAC_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] HMAC_TEST_ATTRIBUTE_UNUSED )
#endif
{
	HMAC_TEST_UNREFERENCED_PARAMETER( argc )
	HMAC_TEST_UNREFERENCED_PARAMETER( argv )

#if !defined( LIBHMAC_HAVE_SHA256_SUPPORT )

	/* TODO add tests for libhmac_sha256_transform */

#endif /* !defined( LIBHMAC_HAVE_SHA256_SUPPORT ) */

	HMAC_TEST_RUN(
	 "libhmac_sha256_initialize",
	 hmac_test_sha256_initialize );

	HMAC_TEST_RUN(
	 "libhmac_sha256_free",
	 hmac_test_sha256_free );

	HMAC_TEST_RUN(
	 "libhmac_sha256_update",
	 hmac_test_sha256_update );

	HMAC_TEST_RUN(
	 "libhmac_sha256_finalize",
	 hmac_test_sha256_finalize );

	HMAC_TEST_RUN(
	 "libhmac_sha256_calculate",
	 hmac_test_sha256_calculate );

	HMAC_TEST_RUN(
	 "libhmac_sha256_calculate_hmac",
	 hmac_test_sha256_calculate_hmac );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

