#./do_cmake.sh

function print(){
  echo -e  "\n\033[32m`date +'%Y/%m/%d %H:%M:%S'` $*\033[0m"
}

start_time=`date +%s`
print "start build"

cd build
make -j16
# make install

end_time=`date +%s`
time_cost=$((end_time-start_time))
print "end build, cost ${time_cost}s"

