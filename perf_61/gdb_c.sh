# ceph_perf_c(){
#   export LD_LIBRARY_PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
#   export PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/bin:$PATH
#   export CEPH_CONF=./ceph.conf
#   cd /home/xb/project/stor/ceph/xb/docker/ceph/build/bin
#   #                                        线程数  每个线程最大消息数    每个线程发送IO个数    思考时间   消息长度
#   ./ceph_perf_msgr_client 175.16.53.62:10001   10          1                    1                    0        4096
# }


date
gdb --args ceph_perf_msgr_client 175.16.53.62:10001   10          1                    1                    0        4096
# gdb --args ceph_perf_msgr_client 175.16.53.62:10001 1 1 1 4096
