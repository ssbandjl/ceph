date
# export LD_LIBRARY_PATH=xxx:$LD_LIBRARY_PATH
#gdb --args ceph_perf_msgr_server 10.132.33.30:10001 1 0
export PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/bin:$PATH
cd /home/xb/project/stor/ceph/xb/docker/ceph/perf
# ceph_perf_msgr_client 175.16.53.62:10001 1 1 1 0 4096
gdb --args ceph_perf_msgr_client 175.16.53.62:10001 1 1 1 0 4096



#Usage: ceph_perf_msgr_client [server ip:port] [numjobs] [concurrency] [ios] [thinktime us] [msg length]
#       [server ip:port]: connect to the ip:port pair
#       [numjobs]: how much client threads spawned and do benchmark
#       [concurrency]: the max inflight messages(like iodepth in fio)
#       [ios]: how much messages sent for each client
#       [thinktime]: sleep time when do fast dispatching(match client logic)
#       [msg length]: message data bytes


