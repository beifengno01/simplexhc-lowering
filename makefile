CC=clang

CPPFLAGS = `llvm-config --cflags `
LDFLAGS = `llvm-config --cxxflags --ldflags --libs core executionengine interpreter analysis native bitwriter --system-libs`

install: lib
	cp out/liblowering.so /usr/local/lib

lib:
	-mkdir out
	clang -Wall -Werror lowering.c -c -o out/lowering.o $(CPPFLAGS)
	ar -rcs out/liblowering.a out/lowering.o
	clang -shared -o out/liblowering.so out/lowering.o  $(LDFLAGS)


clean:
	-rm -rf out/


