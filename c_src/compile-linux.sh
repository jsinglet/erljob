gcc \
    -Wall  \
    -I /usr/lib/erlang/usr/include/ \
    -fPIC  \
    -shared \
    -o ../priv/utils.so  \
    *.c -lm
