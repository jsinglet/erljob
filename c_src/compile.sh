gcc \
    -Wall  \
    -arch i386 -arch x86_64  \
    -I/opt/local/lib/erlang/usr/include  \
    -I /usr/local/lib/erlang/usr/include/ \
    -fPIC  \
    -bundle -flat_namespace -undefined suppress  \
    -o ../priv/utils.so  \
    *.c
