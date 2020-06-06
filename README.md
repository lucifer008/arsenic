[![Build Status](https://travis-ci.org/Antidote1911/Arsenic.svg?branch=master)](https://travis-ci.org/Antidote1911/Arsenic)
[![Build status](https://ci.appveyor.com/api/projects/status/eid3dqq4c28u7sf4?svg=true)](https://ci.appveyor.com/project/Antidote1911/arsenic)

# Arsenic
**A simple tool to encrypt files and text with strong algorithms.**<br>
Tested with Windows 10 and all major Linux distributions. Arsenic is developed on Archlinux.

<img src='screenshots/main_dark.png'/>

*More screenshots at the and of this readme.*

## Simple Description: ##
Arsenic was intended as a lightweight, portable application, that would encode a list of local files using a pass-phrase. A simple text editor named "CryptoPad" can be useful for send encrypted text by email. CryptoPad and file encryption always use cascade triple encryption with this algorithms:
- [XChaCha20Poly1305](https://botan.randombit.net/handbook/api_ref/cipher_modes.html#chacha20poly1305)
- [AES256](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)/[EAX](https://en.wikipedia.org/wiki/EAX_mode)
- [Serpent](https://en.wikipedia.org/wiki/Serpent_(cipher))/[GCM](https://en.wikipedia.org/wiki/Galois/Counter_Mode)

Some useful tools are included. A file Hash calculator and a password generator.

## Technical description: ##

**Password Derivation :**<br>
A 96 bytes "Masterkey" is generated by Argon2 from the user pass-phrase and a 16 bytes random salt. This "Masterkey" is split in three keys for the triple encryption.

**initialization vectors (or nonces) :**<br>
A 72 bytes "MasterNonce" is generated by Botan random number generator. This master nonce is split in three 24 bytes nonces for the triple encryption. They are always incremented before all steps to ensure they are never reused with the same key.

**Arsenic encrypted file format**<br>
First, Arsenic triple encrypt a little header who contain the original file name and a randomized block of data. After that, the original file is encrypted in cascade chunk by chunk.

the output is :
- Magic number
- Arsenic version
- Argon memlimit
- Argon iterations
- original fileNameSize
- original fileSize
- Argon salt  (16 bytes)
- ivChaCha20 +  ivAES +  ivSerpent (24 bytes * 3)
- encrypted header  ( fileNameSize + randomBloc(IN_BUFFER_SIZE) + Authentication tag * 3)
- encrypted dataBlock1  ( BUFFER_SIZE + Authentication tag * 3 )
- encrypted dataBlock2  ( BUFFER_SIZE + Authentication tag * 3 )
- ....etc

**Text encryption with cryptopad**<br>

- version    (4 bytes)
- salt       (16 bytes) for Argon2
- ivChaCha20 +  ivAES +  ivSerpent (24 bytes * 3)
- ciphertext
- Authentication tag * 3

**Hash calculator**<br>
Supported algorithms: SHA-3, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512, SHA-512-256, Skein-512, Keccak-1600, Whirlpool, Blake2b, SHAKE-128, SHAKE-256, GOST-34.11, SM3, Tiger, Streebog-256, Streebog-512, RIPEMD-160, Adler32, MD4, MD5, CRC24, CRC32

## Command line mode: ##
**The command line interface doesn't support space in the arguments.**
This example encrypt a file named "test.mkv" with the secret passphrase "badpassphrase". Encryption produce the encrypted file "test.mkv.arsenic" but it can be renamed because the original file name is encrypted in the file.

```bash
    ./arsenic -e -p badpassphrase -n test.mkv
    # For decrypt this file :
    ./arsenic -d -p badpassphrase test.mkv.arsenic
    # View help :
    ./arsenic -h
    # View Arsenic version :
    ./arsenic -v
```

## Developers: ##
The application was primarily built around the Qt 5.14 framework.
To update Botan, you must regenerate the amalgamation build from source:

```bash
    # for linux clang
    ./configure.py --cc=clang --amalgamation --disable-shared --disable-modules=pkcs11
    # for linux gcc
    ./configure.py --cc=gcc --amalgamation --disable-shared --disable-modules=pkcs11
    # for Windows MinGW x86
    python configure.py --cpu=x86_64 --cc=gcc --os=mingw --amalgamation --disable-shared --disable-modules=pkcs11
    # for Windows MinGW x32
    python configure.py --cpu=x86_32 --cc=gcc --os=mingw --amalgamation --disable-shared --disable-modules=pkcs11
```

To build the program from source, the appropriate Qt version should be installed and configured.<br>
For Archlinux Arsenic is in AUR.
On other linux distributions you can run this command in the extracted source archive:
```bash
  qmake
  make
  sudo make install
```
Arsenic work well but it need some code simplifications, code comments, orthographic corrections ,etc.<br> Any suggestions or help are welcome.


Thanks to :
- [Jack Lloyd from randombit.net](https://botan.randombit.net) for the powerful Botan C++ cryptographic library. You can find the Github [here](https://github.com/randombit/botan).<br>
It is released under the permissive Simplified [BSD license](https://botan.randombit.net/license.txt)

## CAUTION: ##
A simple tool to encrypt file is not magic. If You use an insecure system, Arsenic (and all encryption tools) are useless. Arsenic do not protect you from key-logger, disk analyze, virus, vignetting cache etc...

## More Screenshots: ##

<img src='screenshots/pass_gen.png'/>
<img src='screenshots/hash.png'/>
<img src='screenshots/cryptopad_light.png'/>

## License: ##
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

<img src='https://www.gnu.org/graphics/gplv3-with-text-136x68.png'/>
