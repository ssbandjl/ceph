============================
 Messenger notes
============================

Messenger is the Ceph network layer implementation. Currently Ceph supports
one messenger type: "async".

ceph_perf_msgr
==============

ceph_perf_msgr is used to do benchmark for messenger module only and can help
to find the bottleneck or time consuming within messenger moduleIt just like
"iperf", we need to start server-side program firstly:
ceph_perf_msgr 仅用于对 messenger 模块进行基准测试，可以帮助发现 messenger 模块内部的瓶颈或耗时它就像“iperf”一样，我们需要先启动服务器端程序：
编译:
if(WITH_TESTS)
 add_subdirectory(test)
endif()

# ./ceph_perf_msgr_server 172.16.30.181:10001 1 0

1. The first argument is ip:port pair which is telling the destination address the client need to specified. 
2. The second argument configures the server threads. 
3. The third argument tells the "think time"(us) when dispatching messages. After Giant, CEPH_OSD_OP message which is the actual client read/write io request is fast dispatched without queueing to Dispatcher, in order to achieve better performance.So CEPH_OSD_OP message will be processed inline, "think time" is used by mock this "inline process" process.
第三个参数：模拟dispatch调度每个消息的耗时（“思考时间”(think_time)--代码中： usleep(think_time);）。在Giant之后，CEPH_OSD_OP消息（即实际的客户端读/写io请求）将快速分派，而无需排队到Dispatcher，以实现更好的性能。因此，CEPH_OSD_OP消息将进行内联处理，模拟“内联过程”过程将使用“思考时间”
参考: https://www.cnblogs.com/bandaoyu/p/16752306.html


客户端:
#                                        2.线程数  3.每个线程最大并发飞行消息数    4.每个线程发送IO个数    5.思考时间   6.消息长度
ceph_perf_msgr_client 175.16.53.62:10001   10            1                            1                    0        4096
# ./ceph_perf_msgr_client 172.16.30.181:10001 1 32 10000 10 4096 

1. The first argument is specified the server ip:port, 
2. and the second argument is used to specify client threads. 
3. The third argument specify the concurrency(the max inflight messages for each client thread), 
4. the fourth argument specify the io numbers will be issued to server per client thread. 
5. The fifth argument is used to indicate the "think time" for client thread when receiving messages, this is also used to mock the client fast dispatch process. 
6. The last argument specify the message data length to issue.
