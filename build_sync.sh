function print(){
  echo -e  "\n\033[32m`date +'%Y/%m/%d %H:%M:%S'` $*\033[0m"
}

start_time=`date +%s`
print "start build"

cd build
make -j16
# make ceph_perf_msgr_client
# make ceph_perf_msgr_server
# make common

end_time=`date +%s`
time_cost=$((end_time-start_time))
print "end build, cost ${time_cost}s"

rsync -up bin/ceph_perf_msgr_server root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/build/bin/
rsync -up bin/ceph_perf_msgr_client root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/build/bin/
rsync -up lib/libceph-common.so.2 root@c62:/home/xb/project/stor/ceph/xb/docker/ceph/build/lib/
