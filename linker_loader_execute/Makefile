all: # compiler new malloc to shared libraries
	gcc -D_GNU_SOURCE -shared -ldl -fPIC -o /tmp/libmcount.so malloc_count.c
	gcc -D_GNU_SOURCE -shared -ldl -fPIC -o /tmp/libmcount_hidden.so malloc_count_hidden.c
	gcc -o syms -c syms.c

check: # run ls with our new shared libraries
	LD_PRELOAD=/tmp/libmcount.so ls
	readelf --syms /tmp/libmcount.so | grep malloc

local_check: # run ls with our new local shared libraries
	LD_PRELOAD=/tmp/libmcount_hidden.so ls
	readelf --syms /tmp/libmcount_hidden.so | grep malloc

weak_check:
	LC_ALL=C readelf --syms ./syms

clean:
	rm /tmp/libmcount.so
