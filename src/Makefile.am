lib_LTLIBRARIES = libbasenc.la
libbasenc_la_SOURCES = base32.c base64.c base32.h base64.h

bin_PROGRAMS = base32enc base64enc

base32enc_SOURCES = base32enc.c base32.h
base32enc_LDADD = libbasenc.la

base64enc_SOURCES = base64enc.c base64.h
base64enc_LDADD = libbasenc.la
