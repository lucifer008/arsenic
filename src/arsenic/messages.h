#ifndef MESSAGES_H
#define MESSAGES_H

#include <QString>

enum : int {
    CRYPT_SUCCESS,
    DECRYPT_SUCCESS,
    NOT_AN_ARSENIC_FILE,
    SRC_NOT_FOUND,
    SRC_CANNOT_OPEN_READ,
    PASS_HASH_FAIL,
    DES_HEADER_ENCRYPT_ERROR,
    DES_FILE_EXISTS,
    DES_CANNOT_OPEN_WRITE,
    DES_HEADER_WRITE_ERROR,
    SRC_BODY_READ_ERROR,
    DATA_ENCRYPT_ERROR,
    DES_BODY_WRITE_ERROR,
    SRC_HEADER_READ_ERROR,
    SRC_HEADER_INVALID_TAG,
    SRC_HEADER_INTEGRITY_FAILURE,
    INVALID_TAG,
    INTEGRITY_FAILURE,
    ABORTED_BY_USER,
    INVALID_CRYPTOBOX_IMPUT,
    BAD_CRYPTOBOX_VERSION,
    BAD_CRYPTOBOX_PEM_HEADER
};

QString errorCodeToString(int error_code);

#endif // MESSAGES_H
