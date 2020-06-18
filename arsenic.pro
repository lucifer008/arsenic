#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T19:06:31
#
#-------------------------------------------------

TEMPLATE      = subdirs
CONFIG += ordered

SUBDIRS += thirdparty \
           arsenic \
           tests

arsenic.depends = thirdparty
tests.depends = thirdparty

OTHER_FILES += \
    defaults.pri


DISTFILES += \
    .appveyor.yml \
    .travis.yml \
    .clang-format \
    LICENSE \
    README.md \
    botan_license.txt \
    screenshots/main_dark.png \
    screenshots/hash.png \
    screenshots/cryptopad_light.png \
    screenshots/pass_gen.png
