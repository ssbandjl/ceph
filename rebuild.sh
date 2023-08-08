set -x 

rm -rf build
./do_cmake.sh

# 七牛云缓存加速, http://rz2fg6ogr.hn-bkt.clouddn.com/boost_1_72_0.tar.bz2
cp boost_1_72_0.tar.bz2 build/boost/src/boost_1_72_0.tar.bz2
# cp boost_1_72_0.tar.bz2_tgz build/boost/src/boost_1_72_0.tar.bz2

function print(){
  echo -e  "\n\033[32m`date +'%Y/%m/%d %H:%M:%S'` $*\033[0m"
}

start_time=`date +%s`
print "start build"

cd build
make -j64
# make install

# enable rdma
# cp perf/ceph.conf build/bin/

end_time=`date +%s`
time_cost=$((end_time-start_time))
print "end build, cost ${time_cost}s"

