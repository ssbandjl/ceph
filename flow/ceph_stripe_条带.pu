'在线渲染: https://www.planttext.com/'
'使用文档: https://plantuml.com/zh/sequence-diagram'

'fio_rados 命令行参数: https://fio.readthedocs.io/en/latest/fio_doc.html, 或查看参考配置:fio_rado 参考配置, https://blog.csdn.net/DeamonXiao/article/details/120879653, fio源码解读测试: https://blog.csdn.net/weixin_38428439/article/details/121642171, '



@startuml

title FIO_RADOS
header 参考测试命令: neonfio -name=tcase -ioengine=qbd -bs=4k -volume=vol/vol1 -runtime=600 -config_file=/etc/neonsan/qbd.conf -rw=write -time_based -use_tcp=1 -group_reporting -iodepth=16 -numjobs=1  \n\
rados_fio_engine: .name = "rados" \n\
fio -name=xxx -ioengine=rados -bs=4k -rw=randwrite -clustername=admin -clientname=admin conf=/etc/ceph/ceph.conf -busy_poll=1 -touch_objects=1 -pool=xxx -iodepth=32 -size=128m -nr_files=32




start

:fio.c -> main
initialize_fio 时钟, 小池(mmap), 大小端检查, cpu架构, 文件锁, 保留关键字
parse_options 解析参数, 注册回调, 填充定义的线程数据, 设置共享线程区域
fio_time_init;

:fio_backend;
:run_threads(sk_out);
:if (setup_files(td));
:fio_rados_setup 初始化;
:_fio_setup_rados_data(td, &rados) 设置rados数据;
:_fio_rados_connect;

if (有集群名) then(Y)
  :rados_create2(&rados->cluster, o->cluster_name, client_name, 0) 连接集群;
else
  :rados_create(&rados->cluster, o->client_name); 
endif

:(init_io_u(td));
:do_io(td, bytes_done);
:td_io_queue(td, io_u);
:fio_rados_queue;
:fio_ro_check;


if (数据方向) then(写 DDIR_WRITE)
  :rados_aio_create_completion(fri, complete_callback;
  :rados_aio_write(rados->io_ctx, object, fri->completion, io_u->xfer_buf, io_u->xfer_buflen, io_u->offset);
elseif (读 DDIR_READ)
  :rados_aio_create_completion(fri, complete_callback;
  :rados_aio_read(rados->io_ctx, object, fri->completion, io_u->xfer_buf, io_u->xfer_buflen, io_u->offset);
elseif (修剪 DDIR_TRIM,被get_io_u调用)
  :rados_aio_create_completion(fri, complete_callback;
  :rados_create_write_op;
  :rados_write_op_zero(fri->write_op, io_u->offset, io_u->xfer_buflen);
  :rados_aio_write_op_operate;
endif

:io_u_queued_complete;
:td_io_getevents;


stop

@enduml
