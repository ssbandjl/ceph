rm -f rbd_write && gcc rbd_write.c  -lrbd -lrados  -g -Wall  -Wl,-rpath=/opt/h3c/lib -lrados -L/opt/h3c/lib/ -o rbd_write
gdb --args rbd_write --debug_objecter=30 --debug_ms=30
