if [[ $# -lt 1 ]];then
   echo "./$0 file"
   exit 0
fi

lib_rados='/opt/h3c/lib/librados.so.2.0.0'
lib_rbd='/opt/h3c/lib/librbd.so.1.12.0'
tgz='so.tgz'


source /root/.bashrc

cd /root/ceph/

file=$1
rm -f *.so*
rm -f $tgz 
wget "ftp://rd-itproduct:h3c-rd-itproduct@10.132.206.121:$file"

# for ip in 182.200.53.73  182.200.53.74;do scp $tgz root@$ip:/root/ceph/;done
# #for ip in 182.200.53.73  182.200.53.74;do scp libceph-common.so.0 root@$ip:/root/ceph/;done
# #echo -e ""
# run_cmd "cd /root/ceph/ && tar -zxvf $tgz && \
#    rm -rf ${lib_comm}.bak;cp $lib_comm ${lib_comm}.bak && cp libceph-common.so.0 $lib_comm && echo old;md5sum ${lib_comm}.bak;echo new;md5sum ${lib_comm}; \
#    rm -rf ${lib_rados}.bak;cp $lib_rados ${lib_rados}.bak && cp librados.so.2.0.0 $lib_rados && echo old;md5sum ${lib_rados}.bak;echo new;md5sum ${lib_rados}"
# #run_cmd "cd /root/ceph/ && rm -rf ${lib_comm}.bak;cp $lib_comm ${lib_comm}.bak && cp libceph-common.so.0 $lib_comm && echo old;md5sum ${lib_comm}.bak;echo new;md5sum ${lib_comm}"

tar -zxvf so.tgz && cd so
md5sum librados.so.2.0.0
md5sum librbd.so.1.12.0
rsync -ruplv librados.so.2.0.0 /opt/h3c/lib/
rsync -ruplv librbd.so.1.12.0 /opt/h3c/lib/
md5sum $lib_rados
md5sum $lib_rbd
