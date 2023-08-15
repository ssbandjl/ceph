#!/usr/bin/env bash
set -ex

# git submodule update --init --recursive

: ${BUILD_DIR:=build}
: ${CEPH_GIT_DIR:=..}

if [ -e $BUILD_DIR ]; then
    echo "'$BUILD_DIR' dir already exists; either rm -rf '$BUILD_DIR' and re-run, or set BUILD_DIR env var to a different directory name"
    exit 1
fi

PYBUILD="2"
if [ -r /etc/os-release ]; then
  source /etc/os-release
  case "$ID" in
      fedora)
          PYBUILD="3.7"
          if [ "$VERSION_ID" -eq "32" ] ; then
              PYBUILD="3.8"
          elif [ "$VERSION_ID" -ge "33" ] ; then
              PYBUILD="3.9"
          fi
          ;;
      rhel|centos)
          MAJOR_VER=$(echo "$VERSION_ID" | sed -e 's/\..*$//')
          if [ "$MAJOR_VER" -ge "8" ] ; then
              PYBUILD="3.6"
          fi
          ;;
      opensuse*|suse|sles)
          PYBUILD="3"
          ARGS+=" -DWITH_RADOSGW_AMQP_ENDPOINT=OFF"
          ARGS+=" -DWITH_RADOSGW_KAFKA_ENDPOINT=OFF"
          ;;
  esac
elif [ "$(uname)" == FreeBSD ] ; then
  PYBUILD="3"
  ARGS+=" -DWITH_RADOSGW_AMQP_ENDPOINT=OFF"
  ARGS+=" -DWITH_RADOSGW_KAFKA_ENDPOINT=OFF"
else
  echo Unknown release
  exit 1
fi

if [[ "$PYBUILD" =~ ^3(\..*)?$ ]] ; then
    ARGS+=" -DWITH_PYTHON3=${PYBUILD}"
fi

if type ccache > /dev/null 2>&1 ; then
    echo "enabling ccache"
    ARGS+=" -DWITH_CCACHE=ON"
fi

mkdir $BUILD_DIR
cd $BUILD_DIR
if type cmake3 > /dev/null 2>&1 ; then
    CMAKE=cmake3
else
    CMAKE=cmake
fi
# ARGS+=" -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m"
# ARGS+=" -DPYTHON_LIBRARY=/usr/lib64"
ARGS+=" -DWITH_EVENTTRACE=OFF"
# ARGS+=" -DWITH_OSD_INSTRUMENT_FUNCTIONS=ON"
ARGS+=" -DWITH_LTTNG=OFF"
ARGS+=" -DWITH_BLKIN=OFF"
# echo -e "cmake_cmd:${CMAKE} $ARGS $@ $CEPH_GIT_DIR"

# DWARF 提供了程序运行时信息(Runtime)到源码信息的映射(Source File)
# cmake -DWITH_EVENTTRACE=OFF -DWITH_LTTNG=OFF -DWITH_BLKIN=OFF '-DCMAKE_C_FLAGS=-O0 -g3 -gdwarf-4' '-DCMAKE_CXX_FLAGS=-O0 -g3 -gdwarf-4' ..
# ${CMAKE} $ARGS  -DCMAKE_C_FLAGS="-O0 -g3 -gdwarf-4" -DCMAKE_CXX_FLAGS="-O0 -g3 -gdwarf-4" "$@" $CEPH_GIT_DIR || exit 1
# ${CMAKE} $ARGS  -DCMAKE_C_FLAGS="-O0 -g3" -DCMAKE_CXX_FLAGS="-O0 -g3" "$@" $CEPH_GIT_DIR || exit 1
# ${CMAKE} $ARGS  -DCMAKE_C_FLAGS="-Og -g3" -DCMAKE_CXX_FLAGS="-Og -g3" "$@" $CEPH_GIT_DIR || exit 1
# ${CMAKE} $ARGS  -DCMAKE_C_FLAGS="-g" -DCMAKE_CXX_FLAGS="-g" "$@" $CEPH_GIT_DIR || exit 1

ARGS+=" -DWITH_FIO=ON"

# 谷歌单元测试
${CMAKE} $ARGS  -DCMAKE_C_FLAGS="-g" -DWITH_TESTS=ON -DCMAKE_CXX_FLAGS="-g" "$@" $CEPH_GIT_DIR || exit 1
cp -r fio build/src/


set +x
# minimal config to find plugins
cat <<EOF > ceph.conf
[global]
plugin dir = lib
erasure code dir = lib
EOF

echo done.

if [[ ! $ARGS =~ "-DCMAKE_BUILD_TYPE" ]]; then
  cat <<EOF

****
WARNING: do_cmake.sh now creates debug builds by default. Performance
may be severely affected. Please use -DCMAKE_BUILD_TYPE=RelWithDebInfo
if a performance sensitive build is required.
****
EOF
fi

