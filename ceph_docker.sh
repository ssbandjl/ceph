

export PYTHONPATH=/home/xb/project/ceph/xb/ceph/src/pybind:/home/xb/project/ceph/xb/ceph/build/lib/cython_modules/lib.3:/home/xb/project/ceph/xb/ceph/src/python-common:$PYTHONPATH
export LD_LIBRARY_PATH=/home/xb/project/ceph/xb/ceph/build/lib:$LD_LIBRARY_PATH
alias cephfs-shell=/home/xb/project/ceph/xb/ceph/src/tools/cephfs/cephfs-shell
CEPH_DEV=1

ceph -s

