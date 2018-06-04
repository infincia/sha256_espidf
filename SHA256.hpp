
#ifndef SHA256_CPP_H_
#define SHA256_CPP_H_

#include <mbedtls/sha256.h>
#include <iostream>
#include <sstream>
#include <iomanip>

class SHA256 {
  public:
    SHA256() {
        mbedtls_sha256_init(&context);
        mbedtls_sha256_starts(&context, 0);
    }

    virtual ~SHA256() {
        mbedtls_sha256_free(&context);
    }

    void update(uint8_t *buf, size_t len) {
        mbedtls_sha256_update(&context, buf, len);
    }

    void finish(uint8_t *out) {
        _finish();
        memcpy(out, result, 256);
    }

    void finish(std::string &out) {
        _finish();

        std::stringstream stream;
        stream << std::setfill('0') << std::setw(64);
        stream << std::hex;

        int i;

        for (i = 0; i <= 31; i++) {
            stream << result[i];
        }
        
        stream << std::endl;

        out = std::string(stream.str());
    }

  private:
    void _finish() {
        if (!finished) {
            mbedtls_sha256_finish(&context, result);
            finished = true;
        }
    }

  private:
    mbedtls_sha256_context context;
    uint8_t result[32];
    bool finished = false;
};

#endif /* SHA256_CPP_H_ */
