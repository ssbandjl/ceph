ceph_perf_s(){
  export LD_LIBRARY_PATH=/root/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
  export PATH=/root/project/stor/ceph/xb/docker/ceph/build/bin:$PATH
  cd /root/project/stor/ceph/xb/docker/ceph/build/bin
  ./ceph_perf_msgr_server 172.17.0.2:10001 1 0
}
ceph_perf_c(){
  export LD_LIBRARY_PATH=/root/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
  export PATH=/root/project/stor/ceph/xb/docker/ceph/build/bin:$PATH
  cd /root/project/stor/ceph/xb/docker/ceph/build/bin
  #                                        线程数  每个线程最大消息数    每个线程发送IO个数    思考时间   消息长度
  ./ceph_perf_msgr_client 172.17.0.2:10001   10          1                    1                    0        4096
}
