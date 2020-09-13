
vol: a.c
	$(CC) $(shell pkg-config --cflags libevdev) $^ $(shell pkg-config --libs libevdev) -o $@

install: vol volmgr.service
	cp vol /usr/bin
	cp volmgr.service /etc/systemd/system
	systemctl daemon-reload

.PHONY:clean
clean:
	rm -rf *~ vol
