/* Testing MatrixSSL's pstm_exptmod with values causing a wrong result
 * by Hanno Böck, license: CC0
 */

#include <stdio.h>
#include <stdlib.h>
#include <openssl/bn.h>
#include <crypto/cryptoApi.h>

unsigned char a1[] = {
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x2f, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc7, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2d, 0x2f, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x38, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
	0x2f, 0x3e, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x3d, 0x2f,
	0x2f, 0xff, 0xff, 0xff, 0x7f, 0x2f, 0x2f, 0x28, 0x2f, 0x2f
};

unsigned int a1_len = 154;

unsigned char b1[] = {
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
	0x32, 0x2f, 0x2f, 0x2f
};

unsigned int b1_len = 16;

unsigned char m1[] = {
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x2f, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0x2f, 0x2f, 0x2f,
	0x00, 0x00, 0x00, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xff, 0xff, 0xff, 0x00, 0x2f,
	0x2f, 0x2f, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x13,
	0xc4, 0xbb, 0x83, 0x59, 0x00, 0x06, 0xe0, 0x77, 0xaa, 0x2f, 0x2f, 0x2f,
	0x2f, 0x2f, 0x22, 0x2f, 0x2f
};

unsigned int m1_len = 113;

/* test bn functions from openssl/libcrypto */
char *bntest(unsigned char *a_raw, int a_len, unsigned char *b_raw, int b_len,
	     unsigned char *m_raw, int m_len)
{
	BN_CTX *bctx = BN_CTX_new();
	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *m = BN_new();
	BIGNUM *res1 = BN_new();
	char *result;

	BN_bin2bn(a_raw, a_len, a);
	BN_bin2bn(b_raw, b_len, b);
	BN_bin2bn(m_raw, m_len, m);

	BN_mod_exp(res1, a, b, m, bctx);
printf("a: %s\n",BN_bn2hex(a));
printf("b: %s\n",BN_bn2hex(b));
printf("m: %s\n",BN_bn2hex(m));
	result = BN_bn2hex(res1);
	printf("openssl:\n%s\n", result);

	BN_free(a);
	BN_free(b);
	BN_free(m);
	BN_free(res1);
	BN_CTX_free(bctx);

	return result;
}

char *matrixtest(unsigned char *a_raw, int a_len, unsigned char *b_raw,
		 int b_len, unsigned char *m_raw, int m_len)
{
	unsigned char *rr = malloc(4096);
	char *buf, *buf_ptr;
	int i, s;
	pstm_int a, b, m, r;

	if (pstm_init_for_read_unsigned_bin(NULL, &a, a_len) < 0) {
		printf("pstm_init_for_read_unsigned_bin a error\n");
		return 0;
	}
	if (pstm_read_unsigned_bin(&a, a_raw, a_len) != 0) {
		printf("pstm_read_unsigned_bin a error\n");
		return 0;
	}
	if (pstm_init_for_read_unsigned_bin(NULL, &b, b_len) < 0) {
		printf("pstm_init_for_read_unsigned_bin b error\n");
		return 0;
	}
	if (pstm_read_unsigned_bin(&b, b_raw, b_len) != 0) {
		printf("pstm_read_unsigned_bin b error\n");
		return 0;
	}
	if (pstm_init_for_read_unsigned_bin(NULL, &m, m_len) < 0) {
		printf("pstm_init_for_read_unsigned_bin c error\n");
		return 0;
	}
	if (pstm_read_unsigned_bin(&m, m_raw, m_len) != 0) {
		printf("pstm_read_unsigned_bin c error\n");
		return 0;
	}

	if (pstm_init(NULL, &r) != 0) {
		printf("pstm_init r error\n");
		return 0;
	}

	if (pstm_exptmod(NULL, &a, &b, &m, &r) != 0) {
		printf("pstm_exptmod error\n");
		return 0;
	}

	if (pstm_to_unsigned_bin(0, &r, rr) < 0) {
		printf("pstm_to_unsigned_bin error\n");
		return 0;
	}
	s = pstm_unsigned_bin_size(&r);
	buf = buf_ptr = malloc(s * 2 + 1);
	for (i = 0; i < s; i++) {
		buf_ptr += sprintf(buf_ptr, "%02X", rr[i]);
	}

	printf("matrixssl:\n%s\n", buf);
	return buf;
}

int main(int argc, char *argv[])
{
	char *r1, *r2;

	r1 = matrixtest(a1, a1_len, b1, b1_len, m1, m1_len);

	r2 = bntest(a1, a1_len, b1, b1_len, m1, m1_len);

	if (strcmp(r1, r2) != 0)
		printf("Results differ!\n");

	return 0;
}