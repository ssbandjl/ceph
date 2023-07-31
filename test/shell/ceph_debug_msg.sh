#!/bin/bash

set -e


sed -i '/debug_ms/d' /etc/ceph/ceph.conf
sed -i "/^\[global/a debug_ms = 30" /etc/ceph/ceph.conf
cat /etc/ceph/ceph.conf|grep debug_ms
