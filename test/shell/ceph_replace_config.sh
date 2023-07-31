sed -i 's|debug_ms = 1|debug_ms = 0|g' /etc/ceph/ceph.conf
grep debug_ms /etc/ceph/ceph.conf

