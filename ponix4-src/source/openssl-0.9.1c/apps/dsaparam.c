/* apps/dsaparam.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "apps.h"
#include "bio.h"
#include "err.h"
#include "bn.h"
#include "rand.h"
#include "dsa.h"
#include "x509.h"
#include "pem.h"

#undef PROG
#define PROG	dsaparam_main

/* -inform arg	- input format - default PEM (one of DER, TXT or PEM)
 * -outform arg - output format - default PEM
 * -in arg	- input file - default stdin
 * -out arg	- output file - default stdout
 * -noout
 * -text
 * -C
 * -noout
 * -genkey
 */

#ifndef NOPROTO
static void MS_CALLBACK dsa_cb(int p, int n, char *arg);
#else
static void MS_CALLBACK dsa_cb();
#endif

int MAIN(argc, argv)
int argc;
char **argv;
	{
	DSA *dsa=NULL;
	int i,badops=0,text=0;
	BIO *in=NULL,*out=NULL;
	int informat,outformat,noout=0,C=0,ret=1;
	char *infile,*outfile,*prog,*inrand=NULL;
	int numbits= -1,num,genkey=0;
	char buffer[200],*randfile=NULL;

	apps_startup();

	if (bio_err == NULL)
		if ((bio_err=BIO_new(BIO_s_file())) != NULL)
			BIO_set_fp(bio_err,stderr,BIO_NOCLOSE|BIO_FP_TEXT);

	infile=NULL;
	outfile=NULL;
	informat=FORMAT_PEM;
	outformat=FORMAT_PEM;

	prog=argv[0];
	argc--;
	argv++;
	while (argc >= 1)
		{
		if 	(strcmp(*argv,"-inform") == 0)
			{
			if (--argc < 1) goto bad;
			informat=str2fmt(*(++argv));
			}
		else if (strcmp(*argv,"-outform") == 0)
			{
			if (--argc < 1) goto bad;
			outformat=str2fmt(*(++argv));
			}
		else if (strcmp(*argv,"-in") == 0)
			{
			if (--argc < 1) goto bad;
			infile= *(++argv);
			}
		else if (strcmp(*argv,"-out") == 0)
			{
			if (--argc < 1) goto bad;
			outfile= *(++argv);
			}
		else if (strcmp(*argv,"-text") == 0)
			text=1;
		else if (strcmp(*argv,"-C") == 0)
			C=1;
		else if (strcmp(*argv,"-genkey") == 0)
			genkey=1;
		else if (strcmp(*argv,"-rand") == 0)
			{
			if (--argc < 1) goto bad;
			inrand= *(++argv);
			}
		else if (strcmp(*argv,"-noout") == 0)
			noout=1;
		else if (sscanf(*argv,"%d",&num) == 1)
			{
			/* generate a key */
			numbits=num;
			}
		else
			{
			BIO_printf(bio_err,"unknown option %s\n",*argv);
			badops=1;
			break;
			}
		argc--;
		argv++;
		}

	if (badops)
		{
bad:
		BIO_printf(bio_err,"%s [options] [bits] <infile >outfile\n",prog);
		BIO_printf(bio_err,"where options are\n");
		BIO_printf(bio_err," -inform arg   input format - one of DER TXT PEM\n");
		BIO_printf(bio_err," -outform arg  output format - one of DER TXT PEM\n");
		BIO_printf(bio_err," -in arg       inout file\n");
		BIO_printf(bio_err," -out arg      output file\n");
		BIO_printf(bio_err," -text         check the DSA parameters\n");
		BIO_printf(bio_err," -C            Output C code\n");
		BIO_printf(bio_err," -noout        no output\n");
		BIO_printf(bio_err," -rand         files to use for random number input\n");
		BIO_printf(bio_err," number        number of bits to use for generating private key\n");
		goto end;
		}

	ERR_load_crypto_strings();

	in=BIO_new(BIO_s_file());
	out=BIO_new(BIO_s_file());
	if ((in == NULL) || (out == NULL))
		{
		ERR_print_errors(bio_err);
		goto end;
		}

	if (infile == NULL)
		BIO_set_fp(in,stdin,BIO_NOCLOSE);
	else
		{
		if (BIO_read_filename(in,infile) <= 0)
			{
			perror(infile);
			goto end;
			}
		}
	if (outfile == NULL)
		BIO_set_fp(out,stdout,BIO_NOCLOSE);
	else
		{
		if (BIO_write_filename(out,outfile) <= 0)
			{
			perror(outfile);
			goto end;
			}
		}

	if (numbits > 0)
		{
		randfile=RAND_file_name(buffer,200);
		RAND_load_file(randfile,1024L*1024L);

		BIO_printf(bio_err,"Generating DSA parameters, %d bit long prime\n",num);
	        BIO_printf(bio_err,"This could take some time\n");
	        dsa=DSA_generate_parameters(num,NULL,0,NULL,NULL,
			dsa_cb,(char *)bio_err);
		}
	else if	(informat == FORMAT_ASN1)
		dsa=d2i_DSAparams_bio(in,NULL);
	else if (informat == FORMAT_PEM)
		dsa=PEM_read_bio_DSAparams(in,NULL,NULL);
	else
		{
		BIO_printf(bio_err,"bad input format specified\n");
		goto end;
		}
	if (dsa == NULL)
		{
		BIO_printf(bio_err,"unable to load DSA parameters\n");
		ERR_print_errors(bio_err);
		goto end;
		}

	if (text)
		{
		DSAparams_print(out,dsa);
		}
	
	if (C)
		{
		unsigned char *data;
		int l,len,bits_p,bits_q,bits_g;

		len=BN_num_bytes(dsa->p);
		bits_p=BN_num_bits(dsa->p);
		bits_q=BN_num_bits(dsa->q);
		bits_g=BN_num_bits(dsa->g);
		data=(unsigned char *)Malloc(len+20);
		if (data == NULL)
			{
			perror("Malloc");
			goto end;
			}
		l=BN_bn2bin(dsa->p,data);
		printf("static unsigned char dsa%d_p[]={",bits_p);
		for (i=0; i<l; i++)
			{
			if ((i%12) == 0) printf("\n\t");
			printf("0x%02X,",data[i]);
			}
		printf("\n\t};\n");

		l=BN_bn2bin(dsa->q,data);
		printf("static unsigned char dsa%d_q[]={",bits_p);
		for (i=0; i<l; i++)
			{
			if ((i%12) == 0) printf("\n\t");
			printf("0x%02X,",data[i]);
			}
		printf("\n\t};\n");

		l=BN_bn2bin(dsa->g,data);
		printf("static unsigned char dsa%d_g[]={",bits_p);
		for (i=0; i<l; i++)
			{
			if ((i%12) == 0) printf("\n\t");
			printf("0x%02X,",data[i]);
			}
		printf("\n\t};\n\n");

		printf("DSA *get_dsa%d()\n\t{\n",bits_p);
		printf("\tDSA *dsa;\n\n");
		printf("\tif ((dsa=DSA_new()) == NULL) return(NULL);\n");
		printf("\tdsa->p=BN_bin2bn(dsa%d_p,sizeof(dsa%d_p),NULL);\n",
			bits_p,bits_p);
		printf("\tdsa->q=BN_bin2bn(dsa%d_q,sizeof(dsa%d_q),NULL);\n",
			bits_p,bits_p);
		printf("\tdsa->g=BN_bin2bn(dsa%d_g,sizeof(dsa%d_g),NULL);\n",
			bits_p,bits_p);
		printf("\tif ((dsa->p == NULL) || (dsa->q == NULL) || (dsa->g == NULL))\n");
		printf("\t\treturn(NULL);\n");
		printf("\treturn(dsa);\n\t}\n");
		}


	if (!noout)
		{
		if 	(outformat == FORMAT_ASN1)
			i=i2d_DSAparams_bio(out,dsa);
		else if (outformat == FORMAT_PEM)
			i=PEM_write_bio_DSAparams(out,dsa);
		else	{
			BIO_printf(bio_err,"bad output format specified for outfile\n");
			goto end;
			}
		if (!i)
			{
			BIO_printf(bio_err,"unable to write DSA paramaters\n");
			ERR_print_errors(bio_err);
			goto end;
			}
		}
	if (genkey)
		{
		DSA *dsakey;

		if ((dsakey=DSAparams_dup(dsa)) == NULL) goto end;
		if (!DSA_generate_key(dsakey)) goto end;
		if 	(outformat == FORMAT_ASN1)
			i=i2d_DSAPrivateKey_bio(out,dsakey);
		else if (outformat == FORMAT_PEM)
			i=PEM_write_bio_DSAPrivateKey(out,dsakey,NULL,NULL,0,NULL);
		else	{
			BIO_printf(bio_err,"bad output format specified for outfile\n");
			goto end;
			}
		DSA_free(dsakey);
		}
	ret=0;
end:
	if (in != NULL) BIO_free(in);
	if (out != NULL) BIO_free(out);
	if (dsa != NULL) DSA_free(dsa);
	EXIT(ret);
	}

static void MS_CALLBACK dsa_cb(p, n, arg)
int p;
int n;
char *arg;
	{
	char c='*';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	BIO_write((BIO *)arg,&c,1);
	BIO_flush((BIO *)arg);
#ifdef LINT
	p=n;
#endif
	}
