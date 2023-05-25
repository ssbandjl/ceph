rm -rf build
./do_cmake.sh
cp boost_1_72_0.tar.bz2 build/boost/src/boost_1_72_0.tar.bz2

function print(){
  echo -e  "\n\033[32m`date +'%Y/%m/%d %H:%M:%S'` $*\033[0m"
}

start_time=`date +%s`
print "start build"

cd build
make -j64
# make install

cp perf/ceph.conf build/bin/

end_time=`date +%s`
time_cost=$((end_time-start_time))
print "end build, cost ${time_cost}s"

