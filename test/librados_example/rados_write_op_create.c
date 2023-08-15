#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <rados/librados.h>
// #include </opt/h3c/include/rados/librados.h>

// gcc rados_write_op_create.c  -lrados -lrados  -g3 -Og -Wall -Wl,-rpath=/home/xb/project/ceph/xb/ceph/build/lib -lrados -L/home/xb/project/ceph/xb/ceph/build/lib/ -o rados_write_op_create
int main (int argc, const char* argv[])
{
        /* Declare the cluster handle and required arguments. */
        rados_t cluster;
        char cluster_name[] = "ceph";
        // char cluster_name[] = "neo-neo";
        char user_name[] = "client.admin";
        uint64_t flags = 0;

        /* Initialize the cluster handle with the "ceph" cluster name and the "client.admin" user */
        int err;
        err = rados_create2(&cluster, cluster_name, user_name, flags);

        if (err < 0) {
                fprintf(stderr, "%s: Couldn't create the cluster handle! %s\n", argv[0], strerror(-err));
                exit(EXIT_FAILURE);
        } else {
                printf("\nCreated a cluster handle.\n");
        }


        /* Read a Ceph configuration file to configure the cluster handle. */
        //err = rados_conf_read_file(cluster, "/etc/ceph/ceph.conf");
        // err = rados_conf_read_file(cluster, "/etc/ceph/ceph.conf");
        err = rados_conf_read_file(cluster, "/home/xb/project/ceph/xb/ceph/build/ceph.conf");
        if (err < 0) {
                fprintf(stderr, "%s: cannot read config file: %s\n", argv[0], strerror(-err));
                exit(EXIT_FAILURE);
        } else {
                printf("\nRead the config file.\n");
        }

        /* Read command line arguments */
        err = rados_conf_parse_argv(cluster, argc, argv);
        if (err < 0) {
                fprintf(stderr, "%s: cannot parse command line arguments: %s\n", argv[0], strerror(-err));
                exit(EXIT_FAILURE);
        } else {
                printf("\nRead the command line arguments.\n");
        }

        /* Connect to the cluster */
        err = rados_connect(cluster);
        sleep(5);
        if (err < 0) {
                fprintf(stderr, "%s: cannot connect to cluster: %s\n", argv[0], strerror(-err));
                exit(EXIT_FAILURE);
        } else {
                printf("\nConnected to the cluster.\n");
        }

	/*
         * Continued from previous C example, where cluster handle and
         * connection are established. First declare an I/O Context.
         */

        rados_ioctx_t io;
        //char *poolname = "data";
        // char *poolname = ".disk_pool1.rbd";
        char *poolname = "p1"; // ceph osd pool create p1 3 && ceph osd lspools && rados bench -p p1 5 write

        err = rados_ioctx_create(cluster, poolname, &io);
        if (err < 0) {
                fprintf(stderr, "%s: cannot open rados pool %s: %s\n", argv[0], poolname, strerror(-err));
                rados_shutdown(cluster);
                exit(EXIT_FAILURE);
        } else {
                printf("\nCreated I/O context.\n");
        }

        // TEST(LibRadosCWriteOps, Write) {
        // rados_t cluster;
        // rados_ioctx_t ioctx;
        // std::string pool_name = get_temp_pool_name();
        // ASSERT_EQ("", create_one_pool(pool_name, &cluster));
        // rados_ioctx_create(cluster, pool_name.c_str(), &ioctx);

        // Create an object, write and write full to it
        rados_write_op_t op = rados_create_write_op();
        rados_write_op_create(op, LIBRADOS_CREATE_EXCLUSIVE, NULL);
        rados_write_op_write(op, "four", 4, 0);
        // rados_write_op_write_full(op, "hi", 2);
        ASSERT_EQ(0, rados_write_op_operate(op, io, "test", NULL, 0));
        rados_release_write_op(op);
}



