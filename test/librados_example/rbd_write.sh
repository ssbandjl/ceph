# rm -f rbd_write && gcc rbd_write.c  -lrbd -lrados  -g -Wall  -Wl,-rpath=/opt/h3c/lib -lrados -L/opt/h3c/lib/ -o rbd_write
rm -f rbd_write && gcc rbd_write.c  -lrbd -lrados  -g -Wall -o rbd_write
# ./rbd_write --debug_objecter=30 --debug_ms=30 --debug_osd=30 --debug_client=30
gdb ./rbd_write


