add_library (basenc base32.c base64.c)

add_executable (base32enc base32enc.c)
target_link_libraries (base32enc basenc)

add_executable (base64enc base64enc.c)
target_link_libraries (base64end basenc)
