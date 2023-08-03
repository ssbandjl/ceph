# ../src/vstart.sh --debug --new -o "osd_tracing = true"
# ../src/vstart.sh --debug --new
FS=0 OSD=3 MON=3 MGR=3 ../src/vstart.sh --debug --new


# export PYTHONPATH=/home/xb/project/stor/ceph/xb/docker/ceph/src/pybind:/home/xb/project/stor/ceph/xb/docker/ceph/build/lib/cython_modules/lib.3:/home/xb/project/stor/ceph/xb/docker/ceph/src/python-common:$PYTHONPATH
# export LD_LIBRARY_PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
# alias cephfs-shell=/home/xb/project/stor/ceph/xb/docker/ceph/src/tools/cephfs/cephfs-shell
# CEPH_DEV=1