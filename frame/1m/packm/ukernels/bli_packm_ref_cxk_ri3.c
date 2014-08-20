/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas at Austin

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas at Austin nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"

#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_2xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_4xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_6xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_8xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_10xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_12xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_14xk_ri3 )



#undef  GENTFUNCCO
#define GENTFUNCCO( ctype, ctype_r, ch, chr, varname ) \
\
void PASTEMAC(ch,varname)( \
                           conj_t  conja, \
                           dim_t   n, \
                           void*   beta, \
                           void*   a, inc_t inca, inc_t lda, \
                           void*   p, inc_t psp,  inc_t ldp  \
                         ) \
{ \
	const inc_t       inca2     = 2 * inca; \
	const inc_t       lda2      = 2 * lda; \
\
	ctype*            beta_cast =             beta; \
	ctype_r* restrict beta_r    = ( ctype_r* )beta; \
	ctype_r* restrict beta_i    = ( ctype_r* )beta + 1; \
	ctype_r* restrict alpha1_r  = ( ctype_r* )a; \
	ctype_r* restrict alpha1_i  = ( ctype_r* )a + 1; \
	ctype_r* restrict pi1_r     = ( ctype_r* )p; \
	ctype_r* restrict pi1_i     = ( ctype_r* )p +   psp; \
	ctype_r* restrict pi1_ri    = ( ctype_r* )p + 2*psp; \
\
	if ( PASTEMAC(ch,eq1)( *beta_cast ) ) \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +14*inca2), *(alpha1_i +14*inca2), *(pi1_r +14), *(pi1_i +14), *(pi1_ri +14) ); \
				PASTEMAC(ch,copyjri3s)( *(alpha1_r +15*inca2), *(alpha1_i +15*inca2), *(pi1_r +15), *(pi1_i +15), *(pi1_ri +15) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +14*inca2), *(alpha1_i +14*inca2), *(pi1_r +14), *(pi1_i +14), *(pi1_ri +14) ); \
				PASTEMAC(ch,copyri3s)( *(alpha1_r +15*inca2), *(alpha1_i +15*inca2), *(pi1_r +15), *(pi1_i +15), *(pi1_ri +15) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
	else \
	{ \
		if ( bli_is_conj( conja ) ) \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +14*inca2), *(alpha1_i +14*inca2), *(pi1_r +14), *(pi1_i +14), *(pi1_ri +14) ); \
				PASTEMAC(ch,scal2jri3s)( *beta_r, *beta_i, *(alpha1_r +15*inca2), *(alpha1_i +15*inca2), *(pi1_r +15), *(pi1_i +15), *(pi1_ri +15) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
		else \
		{ \
			for ( ; n != 0; --n ) \
			{ \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 0*inca2), *(alpha1_i + 0*inca2), *(pi1_r + 0), *(pi1_i + 0), *(pi1_ri + 0) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 1*inca2), *(alpha1_i + 1*inca2), *(pi1_r + 1), *(pi1_i + 1), *(pi1_ri + 1) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 2*inca2), *(alpha1_i + 2*inca2), *(pi1_r + 2), *(pi1_i + 2), *(pi1_ri + 2) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 3*inca2), *(alpha1_i + 3*inca2), *(pi1_r + 3), *(pi1_i + 3), *(pi1_ri + 3) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 4*inca2), *(alpha1_i + 4*inca2), *(pi1_r + 4), *(pi1_i + 4), *(pi1_ri + 4) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 5*inca2), *(alpha1_i + 5*inca2), *(pi1_r + 5), *(pi1_i + 5), *(pi1_ri + 5) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 6*inca2), *(alpha1_i + 6*inca2), *(pi1_r + 6), *(pi1_i + 6), *(pi1_ri + 6) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 7*inca2), *(alpha1_i + 7*inca2), *(pi1_r + 7), *(pi1_i + 7), *(pi1_ri + 7) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 8*inca2), *(alpha1_i + 8*inca2), *(pi1_r + 8), *(pi1_i + 8), *(pi1_ri + 8) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r + 9*inca2), *(alpha1_i + 9*inca2), *(pi1_r + 9), *(pi1_i + 9), *(pi1_ri + 9) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +10*inca2), *(alpha1_i +10*inca2), *(pi1_r +10), *(pi1_i +10), *(pi1_ri +10) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +11*inca2), *(alpha1_i +11*inca2), *(pi1_r +11), *(pi1_i +11), *(pi1_ri +11) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +12*inca2), *(alpha1_i +12*inca2), *(pi1_r +12), *(pi1_i +12), *(pi1_ri +12) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +13*inca2), *(alpha1_i +13*inca2), *(pi1_r +13), *(pi1_i +13), *(pi1_ri +13) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +14*inca2), *(alpha1_i +14*inca2), *(pi1_r +14), *(pi1_i +14), *(pi1_ri +14) ); \
				PASTEMAC(ch,scal2ri3s)( *beta_r, *beta_i, *(alpha1_r +15*inca2), *(alpha1_i +15*inca2), *(pi1_r +15), *(pi1_i +15), *(pi1_ri +15) ); \
\
				alpha1_r += lda2; \
				alpha1_i += lda2; \
				pi1_r    += ldp; \
				pi1_i    += ldp; \
				pi1_ri   += ldp; \
			} \
		} \
	} \
}

INSERT_GENTFUNCCO_BASIC0( packm_ref_16xk_ri3 )
