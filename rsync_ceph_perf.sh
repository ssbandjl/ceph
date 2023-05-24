ssh -o LogLevel=quiet root@c62 'mkdir -p /home/xb/project/stor/ceph/xb/docker/ceph/build/bin/'
ssh -o LogLevel=quiet root@c62 'mkdir -p /home/xb/project/stor/ceph/xb/docker/ceph/build/lib/'
ssh -o LogLevel=quiet root@c62 'mkdir -p /home/xb/project/stor/ceph/xb/docker/ceph/perf/'

cd /home/xb/project/stor/ceph/xb/docker/ceph/build/bin && rsync -upv ceph_perf_* root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/build/bin/
cd /home/xb/project/stor/ceph/xb/docker/ceph/build/lib && rsync -upv libceph-common.so.2 root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/build/lib/
# cd /home/xb/project/stor/ceph/xb/docker/ceph/build/lib && rsync -urpval /lib64/libtcmalloc.so.4 root@c62:/lib64/libtcmalloc.so.4
# cd /home/xb/project/stor/ceph/xb/docker/ceph/build/lib && rsync -urpval /lib64/libtcmalloc.so.4 root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/build/lib/
rsync -upv /home/xb/project/stor/ceph/xb/docker/ceph/perf/s.sh root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/perf/s.sh
