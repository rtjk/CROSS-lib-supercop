
#pragma once

#define CROSS_NAMESPACE(s) __namespace__ ## s

#define CROSS_keygen                                    CROSS_NAMESPACE(CROSS_keygen)
#define CROSS_sign                                      CROSS_NAMESPACE(CROSS_sign)
#define CROSS_verify                                    CROSS_NAMESPACE(CROSS_verify)
#define expand_digest_to_fixed_weight                   CROSS_NAMESPACE(expand_digest_to_fixed_weight)
#define gen_seed_tree                                   CROSS_NAMESPACE(gen_seed_tree)
#define pack_fp_syn                                     CROSS_NAMESPACE(pack_fp_syn)
#define pack_fp_vec                                     CROSS_NAMESPACE(pack_fp_vec)
#define pack_fz_rsdp_g_vec                              CROSS_NAMESPACE(pack_fz_rsdp_g_vec)
#define pack_fz_vec                                     CROSS_NAMESPACE(pack_fz_vec)
#define rebuild_leaves                                  CROSS_NAMESPACE(rebuild_leaves)
#define rebuild_tree                                    CROSS_NAMESPACE(rebuild_tree)
#define recompute_root                                  CROSS_NAMESPACE(recompute_root)
#define seed_leaves                                     CROSS_NAMESPACE(seed_leaves)
#define seed_path                                       CROSS_NAMESPACE(seed_path)
#define tree_proof                                      CROSS_NAMESPACE(tree_proof)
#define tree_root                                       CROSS_NAMESPACE(tree_root)
#define unpack_fp_syn                                   CROSS_NAMESPACE(unpack_fp_syn)
#define unpack_fp_vec                                   CROSS_NAMESPACE(unpack_fp_vec)
#define unpack_fz_rsdp_g_vec                            CROSS_NAMESPACE(unpack_fz_rsdp_g_vec)
#define unpack_fz_vec                                   CROSS_NAMESPACE(unpack_fz_vec)

#define shake128_inc_init                               CROSS_NAMESPACE(shake128_inc_init)
#define shake128_inc_absorb                             CROSS_NAMESPACE(shake128_inc_absorb)
#define shake128_inc_finalize                           CROSS_NAMESPACE(shake128_inc_finalize)
#define shake128_inc_squeeze                            CROSS_NAMESPACE(shake128_inc_squeeze)
#define shake256_inc_init                               CROSS_NAMESPACE(shake256_inc_init)
#define shake256_inc_absorb                             CROSS_NAMESPACE(shake256_inc_absorb)
#define shake256_inc_finalize                           CROSS_NAMESPACE(shake256_inc_finalize)
#define shake256_inc_squeeze                            CROSS_NAMESPACE(shake256_inc_squeeze)
#define shake128_absorb                                 CROSS_NAMESPACE(shake128_absorb)
#define shake128_squeezeblocks                          CROSS_NAMESPACE(shake128_squeezeblocks)
#define shake128                                        CROSS_NAMESPACE(shake128)
#define shake128_ctx_clone                              CROSS_NAMESPACE(shake128_ctx_clone)
#define shake256_absorb                                 CROSS_NAMESPACE(shake256_absorb)
#define shake256_squeezeblocks                          CROSS_NAMESPACE(shake256_squeezeblocks)
#define shake256                                        CROSS_NAMESPACE(shake256)
#define shake256_ctx_clone                              CROSS_NAMESPACE(shake256_ctx_clone)
#define sha3_256                                        CROSS_NAMESPACE(sha3_256)
#define sha3_256_inc_init                               CROSS_NAMESPACE(sha3_256_inc_init)
#define sha3_256_inc_absorb                             CROSS_NAMESPACE(sha3_256_inc_absorb)
#define sha3_256_inc_finalize                           CROSS_NAMESPACE(sha3_256_inc_finalize)
#define sha3_384_inc_init                               CROSS_NAMESPACE(sha3_384_inc_init)
#define sha3_384_inc_absorb                             CROSS_NAMESPACE(sha3_384_inc_absorb)
#define sha3_384_inc_finalize                           CROSS_NAMESPACE(sha3_384_inc_finalize)
#define sha3_384                                        CROSS_NAMESPACE(sha3_384)
#define sha3_512                                        CROSS_NAMESPACE(sha3_512)
#define sha3_512_inc_init                               CROSS_NAMESPACE(sha3_512_inc_init)
#define sha3_512_inc_absorb                             CROSS_NAMESPACE(sha3_512_inc_absorb)
#define sha3_512_inc_finalize                           CROSS_NAMESPACE(sha3_512_inc_finalize)

#define KeccakF1600_StateExtractBytes                   CROSS_NAMESPACE(KeccakF1600_StateExtractBytes)
#define KeccakF1600_StateXORBytes                       CROSS_NAMESPACE(KeccakF1600_StateXORBytes)
#define KeccakF1600_StatePermute                        CROSS_NAMESPACE(KeccakF1600_StatePermute)

#define KeccakP1600times4_InitializeAll                 CROSS_NAMESPACE(KeccakP1600times4_InitializeAll)
#define KeccakP1600times4_AddBytes                      CROSS_NAMESPACE(KeccakP1600times4_AddBytes)
#define KeccakP1600times4_AddLanesAll                   CROSS_NAMESPACE(KeccakP1600times4_AddLanesAll)
#define KeccakP1600times4_OverwriteBytes                CROSS_NAMESPACE(KeccakP1600times4_OverwriteBytes)
#define KeccakP1600times4_OverwriteLanesAll             CROSS_NAMESPACE(KeccakP1600times4_OverwriteLanesAll)
#define KeccakP1600times4_OverwriteWithZeroes           CROSS_NAMESPACE(KeccakP1600times4_OverwriteWithZeroes)
#define KeccakP1600times4_ExtractBytes                  CROSS_NAMESPACE(KeccakP1600times4_ExtractBytes)
#define KeccakP1600times4_ExtractLanesAll               CROSS_NAMESPACE(KeccakP1600times4_ExtractLanesAll)
#define KeccakP1600times4_ExtractAndAddBytes            CROSS_NAMESPACE(KeccakP1600times4_ExtractAndAddBytes)
#define KeccakP1600times4_ExtractAndAddLanesAll         CROSS_NAMESPACE(KeccakP1600times4_ExtractAndAddLanesAll)
#define KeccakP1600times4_PermuteAll_24rounds           CROSS_NAMESPACE(KeccakP1600times4_PermuteAll_24rounds)
#define KeccakP1600times4_PermuteAll_12rounds           CROSS_NAMESPACE(KeccakP1600times4_PermuteAll_12rounds)
#define KeccakP1600times4_PermuteAll_6rounds            CROSS_NAMESPACE(KeccakP1600times4_PermuteAll_6rounds)
#define KeccakP1600times4_PermuteAll_4rounds            CROSS_NAMESPACE(KeccakP1600times4_PermuteAll_4rounds)
#define KeccakF1600times4_FastLoop_Absorb               CROSS_NAMESPACE(KeccakF1600times4_FastLoop_Absorb)
#define KeccakP1600times4_12rounds_FastLoop_Absorb      CROSS_NAMESPACE(KeccakP1600times4_12rounds_FastLoop_Absorb)
#define KeccakP1600times4_KravatteCompress              CROSS_NAMESPACE(KeccakP1600times4_KravatteCompress)
#define KeccakP1600times4_KravatteExpand                CROSS_NAMESPACE(KeccakP1600times4_KravatteExpand)

#define keccak_x4_init                                  CROSS_NAMESPACE(keccak_x4_init)
#define keccak_x4_absorb                                CROSS_NAMESPACE(keccak_x4_absorb)
#define keccak_x4_finalize                              CROSS_NAMESPACE(keccak_x4_finalize)
#define keccak_x4_squeeze                               CROSS_NAMESPACE(keccak_x4_squeeze)

#define pseed                                           CROSS_NAMESPACE(pseed)
#define psalt                                           CROSS_NAMESPACE(psalt)
#define ptree                                           CROSS_NAMESPACE(ptree)