QT       -= core gui

TARGET = botan
TEMPLATE = lib
# Use this for static botan rather than the default dynamic
CONFIG += static c++14
CONFIG += warn_off

unix {

        equals(QMAKE_CXX, clang++) {
             message(Botan clang)
             SOURCES += linux_clang64/botan_all.cpp \
                        linux_clang64/botan_all_aesni_sse2_ssse3.cpp \
                        linux_clang64/botan_all_avx2.cpp \
                        linux_clang64/botan_all_bmi2.cpp \
                        linux_clang64/botan_all_rdrand.cpp \
                        linux_clang64/botan_all_rdseed_sse2.cpp \
                        linux_clang64/botan_all_sha_sse2_sse41_ssse3.cpp \
                        linux_clang64/botan_all_sha_sse2_ssse3.cpp \
                        linux_clang64/botan_all_sse2_ssse3.cpp
             
             HEADERS += linux_clang64/botan_all.h \
                        linux_clang64/botan_all_internal.h
    
                    }
     
        equals(QMAKE_CXX, g++) {
            message(Botan gcc)
            SOURCES += linux_gcc64/botan_all.cpp \
                       linux_gcc64/botan_all_aesni_sse2_ssse3.cpp \
                       linux_gcc64/botan_all_avx2.cpp \
                       linux_gcc64/botan_all_bmi2.cpp \
                       linux_gcc64/botan_all_rdrand.cpp \
                       linux_gcc64/botan_all_rdseed_sse2.cpp \
                       linux_gcc64/botan_all_sha_sse2_sse41_ssse3.cpp \
                       linux_gcc64/botan_all_sha_sse2_ssse3.cpp \
                       linux_gcc64/botan_all_sse2_ssse3.cpp
             
            HEADERS += linux_gcc64/botan_all.h \
                       linux_gcc64/botan_all_internal.h
            }

}#end linux

win32-g++ {
    QMAKE_CXXFLAGS += -Wa,-mbig-obj

             SOURCES += win_mingw64/botan_all.cpp \
                        win_mingw64/botan_all_aesni_sse2_ssse3.cpp \
                        win_mingw64/botan_all_avx2.cpp \
                        win_mingw64/botan_all_bmi2.cpp \
                        win_mingw64/botan_all_rdrand.cpp \
                        win_mingw64/botan_all_rdseed_sse2.cpp \
                        win_mingw64/botan_all_sse2_ssse3.cpp

             HEADERS += win_mingw64/botan_all.h \
                        win_mingw64/botan_all_internal.h
               

}

win32-msvc {
    LIBS += -ladvapi32 -luser32 -lws2_32 -lpthread

    QMAKE_CXXFLAGS += -bigobj -arch:AVX2

             SOURCES += win_msvc_64/botan_all.cpp \
                        win_msvc_64/botan_all_aesni_sse2_ssse3.cpp \
                        win_msvc_64/botan_all_avx2.cpp \
                        win_msvc_64/botan_all_rdrand.cpp \
                        win_msvc_64/botan_all_rdseed_sse2.cpp \
                        win_msvc_64/botan_all_sse2_ssse3.cpp

             HEADERS += win_msvc_64/botan_all.h \
                        win_msvc_64/botan_all_internal.h


}

QMAKE_CXXFLAGS += -fstack-protector -maes -mpclmul -mssse3 -mavx2
QMAKE_LFLAGS += -fstack-protector

CONFIG += warn_off

