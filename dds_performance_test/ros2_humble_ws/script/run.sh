# node_name, node_number, topic_sub, topic_pub, hz
# numberOfNode hertz

source ../install/setup.bash

cd ../build/rostest_subpub

./pub "pub_1" "1" "topic_0" "topic_1" ${2} &

for (( i=1; i<$1; i++ ))
do
    ./sub "sub_${i}" "$(($i+1))" "topic_${i}" "topic_$(($i+1))" ${2} &

done

# ./sub "sub1" "2" "topic1" "topic2" 1 &
# ./sub "sub2" "3" "topic2" "topic3" 1 &

