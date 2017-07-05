#clang -o test_xslt -L /usr/local/lib -lxml2 -lxslt -I/usr/local/include/libxml2 -I /usr/local/include xslt.c
rm *.mak
rm testgraphics
rm testxslt
rm c_xslt
qmake -o testxslt.mak testxslt.pro
gmake -f testxslt.mak clean
gmake -f testxslt.mak

qmake -o testgraphics.mak testgraphics.pro
gmake -f testgraphics.mak clean
gmake -f testgraphics.mak

clang -o  c_xslt -L /usr/local/lib -lxml2 -lxslt -I/usr/local/include/libxml2 -I/usr/local/include  xslt.c
