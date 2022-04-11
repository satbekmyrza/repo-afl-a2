#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "library.h"

void lib_echo(char *data, ssize_t len){
	if(strlen(data) == 0) {
		return;
	}
	char *buf = calloc(1, len);
	strncpy(buf, data, len);
	printf("%s",buf);
	free(buf);

	// A crash so we can tell the harness is working for lib_echo
	if(data[0] == 'b') {
		if(data[1] == 'u') {
			if(data[2] =='g') {
				if(data[3] == '!') {
					assert(0);
				}
			}
		}
	}
}

int lib_mul(int x, int y){
	if(x % 2 == 0) {
		return y << x;
	} else if (y % 2 == 0) {
		return x << y;
	} else if (x == 0) {
		return 0;
	} else if (y == 0) {
		return 0;
	} else {
		return x * y;
	}
}
