CC:=clang
OUT:=main.exe
CFLAGS:=-g -Wall -std=c17
RFLAGS:=-std=c17 -DNDEBUG -O3
CFILES:=$(wildcard src/*.c)
HFILES:=$(wildcard src/*.h)
OBJS:=$(patsubst src/%.c, obj/%.o, $(CFILES))

debug: $(OBJS)
	$(CC) $(CFLAGS) -o bin/debug/$(OUT) $(OBJS)

release: $(CFILES)
	$(CC) $(RFLAGS) -o bin/release/$(OUT) $(CFILES)

$(OBJS): $(CFILES)
	$(CC) $(CFLAGS) -c $(patsubst obj/%.o, src/%.c, $@) -o $@

clean:
	del $(patsubst obj/%, obj\\%, $(OBJS))
