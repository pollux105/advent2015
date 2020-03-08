#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

char *str2md5(const char *str, int length) {
    	int n;
    	MD5_CTX c;
	unsigned char digest[16];
    	char *out = (char*)malloc(33);
	MD5_Init(&c);

	while (length > 0) {
		if (length > 512) 
		{
			MD5_Update(&c, str, 512);
		} 
		else 
		{
			MD5_Update(&c, str, length);
	        }
	        length -= 512;
	        str += 512;
	}

	MD5_Final(digest, &c);

	for (n = 0; n < 16; ++n) 
	{
		snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
	}

	return out;
}


char *int2char(int nombre)
{
	char *string = (char*)malloc(100);
	sprintf(string,"%d",nombre);
	return string;
}

int main(int argc, char **argv) 
{
	char key[15] = "bgvyzdsv";
	int lenghtKey = strlen(key);
	int number = 0;
	int ZeroCondition = 1;
	
	while(ZeroCondition)
	{
		key[lenghtKey] = '\0';
		char *chaine_number = int2char(number);
		strcat (key,chaine_number);
		char *hash = str2md5(key,strlen(key));
		//printf("key : %s\t nombre %d\n",hash,number);
		number++;
		if ((hash[0] == '0' 	&& hash[1] == '0' \
					&& hash[2] == '0' \
					&& hash[3] == '0' \
					&& hash[4] == '0' \
					&& hash[5] == '0'))
			ZeroCondition = 0;
	}
	number--;	
	printf("nombre = %d\t key : %s\t hash : %s",number,key,str2md5(key,strlen(key)));

}
