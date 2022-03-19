[![License: GPL3](https://img.shields.io/badge/License-GPL3-green.svg)](https://opensource.org/licenses/GPL-3.0)
[![Build Status](https://app.travis-ci.com/Antidote1911/arsenic.svg?branch=master)](https://app.travis-ci.com/Antidote1911/arsenic)
[![Build status](https://ci.appveyor.com/api/projects/status/eid3dqq4c28u7sf4?svg=true)](https://ci.appveyor.com/project/Antidote1911/arsenic)
[![GitHub release](https://img.shields.io/github/release/Antidote1911/arsenic)](https://github.com/Antidote1911/arsenic/releases/)


# Arsenic
**A simple tool to encrypt files and text with strong algorithms.**<br>
Tested with Windows 10 and all major Linux distributions. Arsenic is developed on Archlinux with [JetBrains CLion](https://www.jetbrains.com/clion).

Latest Windows x64 release 3.5.5 is [here](https://github.com/Antidote1911/arsenic/releases/latest).

<img src='screenshots/main_dark.png'/>

*More screenshots at the and of this readme.*

### Thanks to JetBrains for open source support

<a href="https://www.jetbrains.com/"><img src="./screenshots/jetbrains.png" alt="jetbrains" width="150"></a>
<img src='https://www.gnu.org/graphics/gplv3-with-text-136x68.png'/>

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


## Developers: ##
The application was primarily built around the Qt 5 framework.
Botan 2.19.1 is automatically downloaded by qmake, and an amalgamation build is generated (botan_all.cpp and botan_all.h).
If you want to update botan, simply delete the folder 3rdparty/botan/botan, and modify the version you want in the three scripts:

- for Windows : 3rdparty/botan/update-botan.bat
- for unix : 3rdparty/botan/update-botan.sh
- for mac : 3rdparty//botan/update_botan_osx.sh

Run Qmake and the new version was downloaded and amalgamation was generated.

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
- [JetBrains](https://www.jetbrains.com/) for supporting open source.<br>
Arsenic use JetBrains [Clion](https://www.jetbrains.com/clion/) C/C++ EDI.

- [Jack Lloyd from randombit.net](https://botan.randombit.net) for the powerful Botan C++ cryptographic library. You can find the Github [here](https://github.com/randombit/botan).<br>
It is released under the permissive Simplified [BSD license](https://botan.randombit.net/license.txt)

- [KeepassXC](https://github.com/keepassxreboot/keepassxc) for some big portions of code. Including password generator (modified for use Botan Random Number Generator) and the QSettings wrapper class.

## CAUTION: ##
A simple tool to encrypt file is not magic. If You use an insecure system, Arsenic (and all encryption tools) are useless. Arsenic do not protect you from key-logger, disk analyze, virus, vignetting cache etc...

## More Screenshots: ##
<img src='screenshots/main_dark.png'/>
<img src='screenshots/pass_gen.png'/>

*The password generator by the KeepassXC project. modified to use Botan RNG.*

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
