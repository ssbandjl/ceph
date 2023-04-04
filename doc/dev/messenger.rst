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

# ./ceph_perf_msgr_server 172.16.30.181:10001 1 0

1. The first argument is ip:port pair which is telling the destination address the client need to specified. 
2. The second argument configures the server threads. 
3. The third argument tells the "think time"(us) when dispatching messages. After Giant, CEPH_OSD_OP message which is the actual client read/write io request is fast dispatched without queueing to Dispatcher, in order to achieve better performance.So CEPH_OSD_OP message will be processed inline, "think time" is used by mock this "inline process" process.

# ./ceph_perf_msgr_client 172.16.30.181:10001 1 32 10000 10 4096 

1. The first argument is specified the server ip:port, 
2. and the second argument is used to specify client threads. 
3. The third argument specify the concurrency(the max inflight messages for each client thread), 
4. the fourth argument specify the io numbers will be issued to server per client thread. 
5. The fifth argument is used to indicate the "think time" for client thread when receiving messages, this is also used to mock the client fast dispatch process. 
6. The last argument specify the message data length to issue.
