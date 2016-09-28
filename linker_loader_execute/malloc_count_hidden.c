#include  <stdio.h>
#include  <stdlib.h>
#include  <dlfcn.h>
#include  <stdint.h>
#include  <unistd.h>
#include  <string.h>
#include  <inttypes.h>

//  gcc -D_GNU_SOURCE -shared -ldl -fPIC -o /tmp/libmcount.so malloc_count.c
//  D_PRELOAD=/tmp/libmcount.so ls 
//
//  netstat: symbol lookup error: /tmp/libmcount.so: undefined symbol: dlsym
//
//  Your command need support libdl.so.2
//  You can use ldd check	
//  aidrifter@aidrifter-Surface-Pro-3$ ldd /bin/ls
//          linux-vdso.so.1 =>  (0x00007ffc30933000)
//          libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007f5a3231a000)
//          libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f5a31f51000)
//          libpcre.so.3 => /lib/x86_64-linux-gnu/libpcre.so.3 (0x00007f5a31ce0000)
//          libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f5a31adc000)
//          /lib64/ld-linux-x86-64.so.2 (0x00005563048e0000)
//          libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f5a318bf000)


__attribute__((visibility("hidden"))) void *malloc(size_t size)
{
    char buf[32];
    static void *(*real_malloc)(size_t) = NULL;
    if (real_malloc == NULL) {
		// load malloc symbol
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    sprintf(buf, "malloc called, size = %zu\n", size);
    write(2, buf, strlen(buf));
    return real_malloc(size);
}
