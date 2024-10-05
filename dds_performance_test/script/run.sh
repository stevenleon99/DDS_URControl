# !/bin/bash

if [ ${#} -lt 3 ]; then
    echo "input params less than 3"
    echo "input #Node(e.g 3) Hz(e.g 10) MsgSize(e.g 1024) testtime(e.g. 1 (mins))"
    exit 0
else
    echo "start dds performance test ... "
fi

PubDir="../build/DDS_test_publisher"
SubDir="../build/DDS_test_subscriber"
topicBase="DDSTest_"

$PubDir -tr "a" -tw "b" &
$SubDir -tr "b" -tw "c" &


for ((i = 1; i <= $(($4*60)); i++)); do
    sleep "$i"   
done

exit 0 #success




