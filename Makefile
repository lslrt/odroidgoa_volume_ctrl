
vol: a.c
	$(CC) $(shell pkg-config --cflags libevdev) $^ $(shell pkg-config --libs libevdev) -o $@

.PHONY:clean
clean:
	rm -rf *~ vol
