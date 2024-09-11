#include <stdint.h>
#include "blake2b-ref.c"
#include <solana_sdk.h>

uint64_t entrypoint(uint8_t const *input) {
# define NUM_KA 1
  SolAccountInfo ka[NUM_KA];
  SolParameters params = (SolParameters) { .ka = ka };
  if (!sol_deserialize(input, &params, SOL_ARRAY_SIZE(ka))) {
    return ERROR_INVALID_ARGUMENT;
  }
  uint64_t data_len = ka[0].data_len;
  uint8_t * data = ka[0].data;
  uint8_t hash[32];
  blake2b(hash, 32, data, data_len, NULL, 0);
  return 0;
}
