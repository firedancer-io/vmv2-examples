#include <stdint.h>
#include "blake2b-ref.c"

struct account_meta {
  /* 0x00 */ uint8_t pubkey[0x20];
  /* 0x20 */ uint8_t owner[0x20];
  /* 0x40 */ uint64_t lamports;
  /* 0x48 */ uint64_t data_len;
  /* 0x50 */ uint8_t unused[0x30];
};
typedef struct account_meta account_meta_t;

uint64_t entrypoint(
    account_meta_t const * accounts,
    uint64_t               account_cnt,
    uint8_t const *        data,
    uint64_t               data_len
) {
  uint8_t hash[32];
  blake2b(hash, 32, data, data_len, NULL, 0);
  return 0UL;
}
