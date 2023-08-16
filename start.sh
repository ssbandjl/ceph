# ../src/vstart.sh --debug --new -o "osd_tracing = true"
# ../src/vstart.sh --debug --new
# cd build
FS=0 OSD=3 MON=3 MGR=3 ../src/vstart.sh --debug --new
echo -e "export CEPH_CONF=/home/xb/project/ceph/xb/ceph/build/ceph.conf"
echo -e "export PATH=/home/xb/project/ceph/xb/ceph/build/bin:$PATH"

echo -e "\ncreate_pool: ceph osd pool create p1 3"

# export PYTHONPATH=/home/xb/project/stor/ceph/xb/docker/ceph/src/pybind:/home/xb/project/stor/ceph/xb/docker/ceph/build/lib/cython_modules/lib.3:/home/xb/project/stor/ceph/xb/docker/ceph/src/python-common:$PYTHONPATH
# export LD_LIBRARY_PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
# alias cephfs-shell=/home/xb/project/stor/ceph/xb/docker/ceph/src/tools/cephfs/cephfs-shell
# CEPH_DEV=1