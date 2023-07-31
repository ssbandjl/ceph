 //compile: 
 //gcc ceph_test_v2.c  -lrbd -lrados  -g -Wall
 //gcc rbd_write.c  -lrbd -lrados  -g -Wall  -Wl,-rpath=/opt/h3c/lib -lrados -L/opt/h3c/lib/
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
//  #include <rados/librados.h>
//  #include <rbd/librbd.h>
//  #include <assert.h>
//#include <rados/librados.h>
#include </opt/h3c/include/rados/librados.h>
#include </opt/h3c/include/rbd/librbd.h>
 
//  static int print_progress_percent(uint64_t offset, uint64_t src_size,void *data)
//  {
//      float percent = ((float)offset*100)/src_size;
//      printf("%3.2f%% done\n", percent);
//      return 0;
//  }
 
 int main(int argc, char** argv)
 {
     rados_t cluster;
     char cluster_name[] = "ceph";
     char user_name[] = "client.admin";
     uint64_t flags = 0;
     int i=0;
    
    printf("main rdb write start pid %d\n", getpid());
     rados_ioctx_t io; 
    //  char *poolname = "p0"; rados lspools
    //  char *poolname = ".d.rbd";
     char *poolname = ".d0.rbd";
 
     //Initialize the cluster handle with the "ceph" cluster name 
     //and the "client.admin" user name
     int rt_num;
     rt_num = rados_create2(&cluster, cluster_name, user_name, flags);
     if(rt_num<0){
         printf("%s: Couldn't create the cluster handle! %s\n", argv[0], strerror(-rt_num));
         return -1; 
     }else{
         printf("\nCreated a cluster handle success. \n");
     }   
     
     //Read a ceph configuration file to configure the cluster handle
     rt_num = rados_conf_read_file(cluster, "/etc/ceph/ceph.conf");
     if(rt_num<0){
         printf("%s:can't read config file: %s\n", argv[0], strerror(-rt_num));
         return -1;
     }else{
         printf("\nRead the config file. \n");
     }
 
     //Read command line arguments
     /*
     rt_num = rados_conf_parse_argv(cluster, argc, argv);
     if(rt_num<0){
         printf("%s:cannot parse command line arguments:%s\n", argv[0], strerror(-rt_num));
         return -1;
     }else{
         printf("\nRead the command line arguments.\n");
     }*/
 
     //Connect to the cluster
     printf("connect to cluster %p\n", cluster);
     rt_num = rados_connect(cluster);
     if(rt_num<0){
         printf("%s:cannot connect to cluster:%s\n", argv[0], strerror(-rt_num));
         return -1;
     }else{
         printf("\nConnected to the cluster.\n");
     }
 
     //create io handle
     rt_num = rados_ioctx_create(cluster, poolname, &io);
     if(rt_num<0){
         printf("%s:cannot open rados pool %s:%s", argv[0], poolname, strerror(-rt_num));
         rados_shutdown(cluster);
         return -1;
     }else{
         printf("\nCreated I/O context. \n");
     }
 
     const char* name = "500G";
    //  const char* name_01 = "img2";
    //  const char* name_02 = "rbd_test_02.img";
    //  uint64_t size = 1073741824;
    //  uint64_t features = 1073741824;
    //  int order = 22;     //warning
    //  int rbd_create2(rados_ioctx_t io, const char *name, uint64_t size, uint64_t features, int *order);
    //  rt_num = rbd_create( io, name, size, &order);
    //  if( rt_num ==0 ){
    //      printf("\nrbd_create success !!\n");
    //  }else{
    //      printf("\nrbd_create failed !!%s\n", strerror(-rt_num));
    //  }
 
 
     rbd_image_t image;
     //rbd_image_info_t info;
     //size_t  infosize;
 
     //rt_num = rbd_stat(image, &info, sizeof(info));
     //if(rt_num < 0){
     //  printf("rbd_stat error !!\n");
     //}
     //printf("rbd_stat rt_num:%d, size:%d", rt_num, (int)info.size);
 
     //int rbd_remove_with_progress(rados_ioctx_t io, const char *name,librbd_progress_fn_t cb, void *cbdata);
     //librbd_progress_fn_t cb;
     //void* cbdata = NULL;


    //  printf("\nremove img name:%s\n", name_01);
    //  rt_num = rbd_remove_with_progress(io, name_01, print_progress_percent, NULL);
    //  if(rt_num ==0){
    //      printf("\nrbd_remove success !!\n");
    //  }
 
     //int rbd_open(rados_ioctx_t io, const char *name, rbd_image_t *image, const char *snap_name);
     printf("rdb_open image %s\n", name);
     rt_num = rbd_open( io, name, &image, NULL);
                                                      if( rt_num ==0 ){
         printf("\nrbd_open img:%s success !!\n\n", name);
     }else{
         printf("\nrbd_open img:%s failed !!%s\n", name, strerror(-rt_num));
     }
 
    //  size_t num = 1000<<20;
     size_t num = 1<<20;
    //  size_t num = 1<<16; // 1<<16=4M
     char* buf = (char*)malloc(num);
     sprintf((char *) buf, "Hello_world!\n");
    //  char buf1[30]="";
     uint64_t ofs = 0;
     ssize_t  ok_size = 0;
    //  i = 10;
     int count = 1;
    //  int count2 = 1;
     //ssize_t rbd_write(rbd_image_t image, uint64_t ofs, size_t len, const char *buf);
     for(; count > 0; count--){
         printf("start rbd_write count:%d, offset:%lu, len:%lu, buf_ptr:%p\n", count, ofs, num, buf);
         ok_size = rbd_write(image, ofs, num , buf);
         if(ok_size == num){
             ofs = ok_size + ofs;
             printf("index:%d rbd_write ok, ofs:%lu, \n", count, ofs);
         }else{
             printf("index:%d rbd_write fail!! \n", i);
         }
     }
 
    
    //  rbd_image_info_t info_tmp;
    //  rt_num = rbd_stat(image, &info_tmp, sizeof(info_tmp));
    //  if(rt_num < 0){
    //      printf("\nrbd_stat failed %s\n", name);
    //  }else{
    //      printf("\nrbd_stat size :%d\n", (int)info_tmp.size);
    //  }
 
 
    //  ofs = 0;
    //  rt_num = rbd_get_size(image, &ofs);
    //  if(rt_num >= 0){
    //      printf("\nrbd_get_size %d\n", (int)ofs);
    //  }
    //  printf("\nrbd_get_size return_num: %d\n", rt_num);
    //  ofs = 0;
    //  //ssize_t rbd_read(rbd_image_t image, uint64_t ofs, size_t len, char *buf);
    //  for(i=0; i<count2; i++){
    //      ok_size = rbd_read(image, ofs, 10, buf1);
    //      if(ok_size >0){
    //          ofs = 10+ofs;
    //          printf("\nthe content is:%s", buf1);
    //      }else{
    //          printf("rbd_read fail!!\n");
    //      }
    //  }
 
     //int rbd_aio_write(rbd_image_t image, uint64_t off, size_t len, const char *buf, rbd_completion_t c);
     //int rbd_aio_read(rbd_image_t image, uint64_t off, size_t len, char *buf, rbd_completion_t c);
 
     /*
      rt_num = rbd_open_read_only( io, name_01, image, NULL);
      if(rt_num == 0){
         printf("\nrbd_open_read_only success !!\n");
      }else{
         printf("\nrbd_open_read_only fail !!\n");
      }
     */
 
 
 
     rt_num = rbd_close(image);
     if(rt_num == 0){
         printf("\nrbd_close success !!\n");
     }else{
         printf("\nrbd_close failed !!%s\n", strerror(-rt_num));
     }
 
     printf("\nClosing the connection\n");
     rados_ioctx_destroy(io);
     printf("\nShut down the handle\n");
     rados_shutdown(cluster);
     return 0;
 }
