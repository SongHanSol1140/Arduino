// SHA512.cpp

#include "SHA512.h"
#include "variables.h"
#include "mbedtls/md.h"  // sha512 해시용
#include <string.h>


String sha512(const char*input) {
  const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
  unsigned char output[64];
  mbedtls_md_context_t ctx;
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, md_info, 0);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char*)input, strlen(input));
  mbedtls_md_finish(&ctx, output);
  mbedtls_md_free(&ctx);

  // hex 문자열로 변환
  char hexBuf[129];
  for (int i = 0; i < 64; i++) {
    sprintf(hexBuf + i*2, "%02x", output[i]);
  }
  hexBuf[128] = 0;
  return String(hexBuf);
}
