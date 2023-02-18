out := /usr

all: ./build/libplacek.so ./build/placek.h

clean:
	rm -rf ./build/*

install: install-lib(libplacek.so) install-include(placek.h)

test: $(out)/lib/libplacek.so $(out)/include/placek.h ./main.py ./examples/factorial.pson ./build/examples/
	python3 ./main.py ./examples/factorial.pson -o ./build/examples/factorial.c
	$(CC) -o ./build/examples/factorial -fPIC ./build/examples/factorial.c -lplacek -lgc
	test `./build/examples/factorial` -eq 120

%/:
	mkdir -p $@

build/%.o: src/%.c build/
	$(CC) -c -fPIC -o $@ $<

build/%.h: src/%.h build/
	cp $< $@

install-lib(%): ./build/%
	cp $< $(out)/lib/$%

install-include(%): ./build/%
	cp $< $(out)/include/$%

./build/libplacek.so: ./build/placek.o ./build/placek_ops.o
	$(CC) -shared -fPIC -lgc -o $@ $^
