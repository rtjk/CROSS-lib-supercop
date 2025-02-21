
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// replace //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int crypto_sign_open(unsigned char *m,                          // out parameter
                     unsigned long long *mlen,                  // out parameter
                     const unsigned char *sm,                   // in parameter
                     unsigned long long smlen,                  // in parameter
                     const unsigned char *pk)                   // in parameter
{

   /* verify returns 1 if signature is ok, 0 otherwise */
   *mlen = smlen-(unsigned long long) sizeof(CROSS_sig_t);
   
   memcpy((unsigned char *) m, (const unsigned char *) sm, (size_t) *mlen);
   int ok = CROSS_verify((const pk_t *const) pk,            // in parameter
                        (const char *const) m,                  // in parameter
                        (const uint64_t) *mlen,                 // in parameter
                        (const CROSS_sig_t * const) (sm+*mlen));// in parameter


   return ok-1; // NIST convention: 0 == zero errors, -1 == error condition
} // end crypto_sign_open

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// with //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int crypto_sign_open(unsigned char *m,                          // out parameter
                     unsigned long long *mlen,                  // out parameter
                     const unsigned char *sm,                   // in parameter
                     unsigned long long smlen,                  // in parameter
                     const unsigned char *pk_static)            // in parameter
{

   /* SUPERCOP edit: make a static copy of the public key */
   const pk_t pk;
   memcpy((unsigned char *) &pk, pk_static, sizeof(pk_t));

   /* verify returns 1 if signature is ok, 0 otherwise */
   *mlen = smlen-(unsigned long long) sizeof(CROSS_sig_t);
   
   memcpy((unsigned char *) m, (const unsigned char *) sm, (size_t) *mlen);
   int ok = CROSS_verify(&pk,                                   // in parameter
                        (const char *const) m,                  // in parameter
                        (const uint64_t) *mlen,                 // in parameter
                        (const CROSS_sig_t * const) (sm+*mlen));// in parameter


   return ok-1; // NIST convention: 0 == zero errors, -1 == error condition
} // end crypto_sign_open
