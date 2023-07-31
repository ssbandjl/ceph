#!/bin/bash

set -e

#front
addr=$(cat /etc/ceph/ceph.conf 2>/dev/null|grep public_addr|awk '{print$3}')
show_gids_result=$(show_gids|grep $addr|grep v2)
dev_name=$(echo $show_gids_result|awk '{print$1}')
dev_port=$(echo $show_gids_result|awk '{print$2}')
dev_gid_index=$(echo $show_gids_result|awk '{print$3}')
sed -i '/ms_async_rdma_front_device_name/d' /etc/ceph/ceph.conf
sed -i "/^public_addr/a ms_async_rdma_front_device_name = $dev_name" /etc/ceph/ceph.conf

sed -i '/ms_async_rdma_front_device_gid_idx/d' /etc/ceph/ceph.conf
sed -i "/^public_addr/a ms_async_rdma_front_device_gid_idx = $dev_gid_index" /etc/ceph/ceph.conf

sed -i '/ms_async_rdma_front_device_port_num/d' /etc/ceph/ceph.conf
sed -i "/^public_addr/a ms_async_rdma_front_device_port_num = $dev_port" /etc/ceph/ceph.conf

#back
addr=$(cat /etc/ceph/ceph.conf 2>/dev/null|grep cluster_addr|awk '{print$3}')
show_gids_result=$(show_gids|grep $addr|grep v2)
dev_name=$(echo $show_gids_result|awk '{print$1}')
dev_port=$(echo $show_gids_result|awk '{print$2}')
dev_gid_index=$(echo $show_gids_result|awk '{print$3}')
sed -i '/ms_async_rdma_back_device_name/d' /etc/ceph/ceph.conf
sed -i "/^cluster_addr/a ms_async_rdma_back_device_name = $dev_name" /etc/ceph/ceph.conf

sed -i '/ms_async_rdma_back_device_gid_idx/d' /etc/ceph/ceph.conf
sed -i "/^cluster_addr/a ms_async_rdma_back_device_gid_idx = $dev_gid_index" /etc/ceph/ceph.conf

sed -i '/ms_async_rdma_back_device_port_num/d' /etc/ceph/ceph.conf
sed -i "/^cluster_addr/a ms_async_rdma_back_device_port_num = $dev_port" /etc/ceph/ceph.conf