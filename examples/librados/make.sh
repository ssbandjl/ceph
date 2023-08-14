g++ -g -c hello_world.cc -o ceph-client.o
g++ -g ceph-client.o -lrados -o ceph-client

# or 

#make

# g++ -std=c++11 -Wno-unused-parameter -Wall -Wextra -Werror -g -I../../src/include -L../../build/lib/ -Wl,-rpath,../../build/lib -o hello_world_cpp hello_world.cc -lrados -lradosstriper
# g++ -std=c++11 -Wno-unused-parameter -Wall -Wextra -Werror -g -I../../src/include -L../../build/lib/ -Wl,-rpath,../../build/lib -o hello_radosstriper_cpp hello_radosstriper.cc -lrados -lradosstriper
# cc -Wno-unused-parameter -Wall -Wextra -Werror -g -I../../src/include -L../../build/lib/ -Wl,-rpath,../../build/lib -o hello_world_c hello_world_c.c -lrados