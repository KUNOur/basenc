TESTS = test_base32
check_PROGRAMS = test_base32 test_base64
test_base32_SOURCES = test_base32.c $(top_builddir)/src/base32.h
test_base32_CFLAGS = @CHECK_CFLAGS@
test_base32_LDADD = $(top_builddir)/src/libbasenc.a @CHECK_LIBS@
test_base64_SOURCES = test_base64.c $(top_builddir)/src/base64.h
test_base64_CFLAGS = @CHECK_FLAGS@
test_base64_LDADD = $(top_builddir)/src/libbasenc.a @CHECK_LIBS@
