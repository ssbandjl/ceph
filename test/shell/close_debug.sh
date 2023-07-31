#!/bin/bash

set -e


sed -i 's|debug_client = 1/5|debug_client = 0/0|g' /etc/ceph/ceph.conf
sed -i 's|debug_objecter = 2|debug_objecter = 0|g' /etc/ceph/ceph.conf


