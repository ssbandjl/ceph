# bashrc
# ceph_client(){
#   cd /home/xb/project/stor/ceph/xb/docker/ceph/build/bin
#   bash c.sh
# }

date
export LD_LIBRARY_PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/lib:$LD_LIBRARY_PATH
PATH=/home/xb/project/stor/ceph/xb/docker/ceph/build/bin:$PATH

#                                        线程数  每个线程最大消息数    每个线程发送IO个数    思考时间   消息长度
ceph_perf_msgr_client 175.16.53.62:10001   10          1                    1                0        4096

# 1. The first argument is specified the server ip:port, 
# 2. and the second argument is used to specify client threads. 
# 3. The third argument specify the concurrency(the max inflight messages for each client thread), 
# 4. the fourth argument specify the io numbers will be issued to server per client thread. 
# 5. The fifth argument is used to indicate the "think time" for client thread when receiving messages, this is also used to mock the client fast dispatch process. 
# 6. The last argument specify the message data length to issue.