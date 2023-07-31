#!/bin/bash

set -e

#delete and add 
sed -i '/ms_cluster_type/d' /etc/ceph/ceph.conf
sed -i "/^ms_public_type/a ms_cluster_type = async+rdma" /etc/ceph/ceph.conf

sed -i '/ms_public_io_type/d' /etc/ceph/ceph.conf
sed -i "/^ms_public_type/a ms_public_io_type = async+rdma" /etc/ceph/ceph.conf

#hugepage
sed -i '/ms_async_rdma_enable_hugepage/d' /etc/ceph/ceph.conf
sed -i "/^ms_public_type/a ms_async_rdma_enable_hugepage = False" /etc/ceph/ceph.conf

sed -i '/ms_async_rdma_wr_hugepage/d' /etc/ceph/ceph.conf
sed -i "/^ms_public_type/a ms_async_rdma_wr_hugepage = True" /etc/ceph/ceph.conf

cat <<EOF>>/etc/ceph/ceph.conf

[dse]
dse_restart_frequence_check = false
EOF


cat /etc/ceph/ceph.conf|grep rdma
cat /etc/sysctl.conf|grep -i huge
# vm.nr_hugepages = 8192

# sed -i "/^ms_public_type/a ms_async_rdma_wr_hugepage = True" /etc/ceph/ceph.conf

