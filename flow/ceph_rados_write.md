'参考: https://plantuml.com/zh/sequence-diagram'

@startuml

app -> librados: rados_create2 创建集群
librados -> librados: rados_create_cct 创建上下文 \n\
日志,asock,性能统计,新建rados客户端   \n\
new librados::RadosClient 新建rados客户端   \n\

app -> librados: rados_conf_read_file 读配置
librados -> librados: 解析配置文件


app -> librados: rados_conf_parse_argv 解析参数
librados -> librados: 解析命令行参数


app -> librados: rados_connect 连接集群
librados -> librados: 实例化rados客户端 librados::RadosClient *client
librados -> librados: create_client_messenger(cct, "radosclient") 创建rados客户端消息对象
librados -> librados: 实例化monitor客户端 \n\
创建mon临时客户端消息msg对象 \n\
启动3个work线程 \n\
MonC初始化 \n\
启动MonC定时任务 \n\


app -> librados: rados_ioctx_create 基于池和集群创建IO上下文
librados -> librados: 解析命令行参数



app -> librados: rados_write 同步写
librados -> librados: 追加IO数据(将数据追加到_buffers尾部) \n\
librados -> librados: librados::IoCtxImpl::write \n\
librados -> librados: ::ObjectOperation op 实例化OP  \n\
librados -> librados: op.write(off, mybl) 添加数据 \n\
librados -> librados: librados::IoCtxImpl::operate 执行操作 \n\
librados -> librados: oid, oloc

librados -> osdc_objecter: objecter->op_submit(objecter_op) 提交OP
osdc_objecter -> osdc_objecter: _op_submit_with_budget 预算操作 \n\
Objecter::_op_submit 提交OP \n\
_calc_target(&op->target, nullptr) crush算法    \n\
_get_session(op->target.osd, &s, sul) 获取会话    \n\
connect_to_osd 连接目标OSD   \n\
Objecter::_send_op(Op *op) 发送OP   \n\


osdc_objecter -> msg: op->session->con->send_message(m) 发送消息 \n\
osd处理消息,落盘, 回复等


osdc_objecter -> osdc_objecter: cond.wait(l, [&done] { return done;}) 等待OP返回


msg -> osdc_objecter: handle_osd_op_reply OSD返回消息

osdc_objecter -> osdc_objecter: void Objecter::handle_osd_op_reply 处理回复





app -> librados: rados_ioctx_destroy 销毁IO上下文
app -> librados: rados_shutdown 关闭rados




@enduml
