
GENFLAGS := -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal 
OPTIM := $(GENFLAGS) -O3

SANITIZE := $(GENFLAGS) -g3 -fsanitize=address -fsanitize=undefined
CC := clang

md: driver.c md.c md.h mydefs.h
	$(CC) driver.c md.c $(OPTIM) -o md

md_d: driver.c md.c md.h mydefs.h
	$(CC) driver.c md.c $(SANITIZE) -o md_d

all: md md_d

run:
	./md

clean:
	rm -f md md_d md.zip

zip: 
	zip -r md.zip md.c mydefs.h