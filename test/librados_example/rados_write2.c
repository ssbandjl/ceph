#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rados/librados.h>
    
int main (int argc, const char* argv[])
{ 
        rados_t cluster;
        char cluster_name[] = "ceph";           // 集群名字，默认为ceph
        char user_name[] = "client.admin";      // 用户名称
        char conf_file[] = "/home/user/ceph/build/ceph.conf";  // 配置文件路径
        char poolname[] = "default.rgw.meta";                   // 存储池名字
        char objname[] = "test-write";                          // 对象名字
        char obj_content[] = "Hello World,ceph!";                  // 对象内容
        uint64_t flags;
    
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
        err = rados_conf_read_file(cluster, conf_file);
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
        err = rados_ioctx_create(cluster, poolname, &io);
        if (err < 0) {
                fprintf(stderr, "%s: cannot open rados pool %s: %s\n", argv[0], poolname, strerror(-err));
                rados_shutdown(cluster);
                exit(EXIT_FAILURE);
        } else {
                printf("\nCreated I/O context.\n");
        }
    
        /* Write data to the cluster synchronously. */
        err = rados_write(io, objname, obj_content, 16, 0);
        if (err < 0) {
                fprintf(stderr, "%s: Cannot write object \"test-write\" to pool %s: %s\n", argv[0], poolname, strerror(-err));
                rados_ioctx_destroy(io);
                rados_shutdown(cluster);
                exit(1);
        } else {
                printf("\nWrote \"Hello World\" to object \"test-write\".\n");
        }
    
        char xattr[] = "en_US";
        err = rados_setxattr(io, "test-write", "lang", xattr, 5);
        if (err < 0) {
                fprintf(stderr, "%s: Cannot write xattr to pool %s: %s\n", argv[0], poolname, strerror(-err));
                rados_ioctx_destroy(io);
                rados_shutdown(cluster);
                exit(1);
        } else {
                printf("\nWrote \"en_US\" to xattr \"lang\" for object \"test-write\".\n");
        }
    
}
