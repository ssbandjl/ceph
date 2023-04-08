
# bashrc
# ceph_server(){
#   cd /home/xb/project/stor/ceph/xb/docker/ceph/build/bin
#   bash s.sh
# }


date
export LD_LIBRARY_PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
#gdb --args ceph_perf_msgr_server 10.132.33.30:10001 1 0
export PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/bin:$PATH
#gdb --args ceph_perf_msgr_server 175.16.53.61:10001 1 0
export CEPH_CONF=./ceph.conf
./ceph_perf_msgr_server 175.16.53.62:10001 1 0


# 1. The first argument is ip:port pair which is telling the destination address the client need to specified. 
# 2. The second argument configures the server threads. 
# 3. The third argument tells the "think time"(us) when dispatching messages. After Giant, CEPH_OSD_OP message which is the actual client read/write io request is fast dispatched without queueing to Dispatcher, in order to achieve better performance.So CEPH_OSD_OP message will be processed inline, "think time" is used by mock this "inline process" process.
