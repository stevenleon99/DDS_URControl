cd /home/steve/rticonnextdds-getting-started/2_hello_world
rtiddsgen -language c++11 -platform x64Linux4gcc7.3.0 -create makefiles -create typefiles -d c++11 hello_world.idl
cd c++11
make -f makefile_hello_world_x64Linux4gcc7.3.0 DEBUG=1