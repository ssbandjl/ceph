CC=gcc
CFLAGS=-Og -g3 -Wl,-rpath=/opt/h3c/lib -lrados -L/opt/h3c/lib/

all:rados_write
rados_write:rados_write.c
	$(CC) $< $(CFLAGS) -o $@
rbd_write:rbd_write.c
	$(CC) $< $(CFLAGS) -o $@
rados_read:rados_read.c
	$(CC) $< $(CFLAGS) -o $@
rados_rm:rados_rm.c
	$(CC) $< $(CFLAGS) -o $@

clean:
	rm -rf rados_write rados_read rados_rm
