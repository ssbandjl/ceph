#!/bin/bash

set -e


sed -i '/debug_dse/d' /etc/ceph/ceph.conf
sed -i "/^\[global/a debug_dse = 30" /etc/ceph/ceph.conf
cat /etc/ceph/ceph.conf|grep debug_dse
