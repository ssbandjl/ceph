# rm -f rados_write && gcc rados_write.c  -lrados -lrados  -g3 -Og -Wall  -Wl,-rpath=/opt/h3c/lib -lrados -L/opt/h3c/lib/ -o rados_write
# cd test/librados_example
rm -f rados_write && gcc rados_write.c  -lrados -lrados  -g3 -Og -Wall  -Wl,-rpath=/home/xb/project/ceph/xb/ceph/build/lib -lrados -L/home/xb/project/ceph/xb/ceph/build/lib/ -o rados_write

# ceph osd pool create ec_pool 3
gdb --args ./rados_write --debug_objecter=30 --debug_ms=30


# ./rados_write --debug_objecter=30 --debug_ms=30
