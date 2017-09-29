### Readme ###
protoc --plugin=protoc-gen-nanopb=/home/vagrant/Desktop/airliner/tools/nanopb/generator/protoc-gen-nanopb --nanopb_out=. msg.proto
gcc c_test.c nanopb/pb_encode.c nanopb/pb_common.c msg.pb.c -o test
