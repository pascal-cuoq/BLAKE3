#include "blake3.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  const char *path = "input.data";
  int oflags = O_RDONLY;
  int fd = open(path, oflags);
  if(fd < 0) return -1;

  // Initialize the hasher.
  blake3_hasher hasher;
  blake3_hasher_init(&hasher);

  // Read input bytes from the input file.
  unsigned char buf[65536];
  ssize_t n;
  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    blake3_hasher_update(&hasher, buf, n);
  }
  close(fd);

  // Finalize the hash. BLAKE3_OUT_LEN is the default output length, 32 bytes.
  uint8_t output[BLAKE3_OUT_LEN];
  blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

  // Print the hash as hexadecimal.
  for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) {
    printf("%02x", output[i]);
  }
  printf("\n");
  return 0;
}
