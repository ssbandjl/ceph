#!/bin/bash

set -e


sed -i '/dse_restart_frequence_check/d' /etc/ceph/ceph.conf
sed -i "/^\[global/a dse_restart_frequence_check = False" /etc/ceph/ceph.conf
cat /etc/ceph/ceph.conf|grep dse_restart_frequence_check
