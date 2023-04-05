date
#export LD_LIBRARY_PATH=xxx:$LD_LIBRARY_PATH
#gdb --args ceph_perf_msgr_server 10.132.33.30:10001 1 0
export PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/bin:$PATH
gdb --args ceph_perf_msgr_server 175.16.53.61:10001 1 0
handle all nostop