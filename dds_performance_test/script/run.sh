# !/bin/bash

if [ ${#} -lt 3 ]; then
    echo "input params less than 3"
    echo "input #Node(e.g 3) Hz(e.g 10) testtime(e.g. 1 (mins))"
    exit 0
else
    echo "start dds performance test ... "
fi

PubDir="../build/DDS_test_publisher"
SubDir="../build/DDS_test_subscriber"
topicBase="DDSTest_"

$PubDir -tr "A" -tw "B" -n "1" -hz "${2}" &
$SubDir -tr "B" -tw "C" -n "2" -hz "${2}" &
$SubDir -tr "C" -tw "D" -n "3" -hz "${2}" &

for ((i = 1; i <= $(($4*60)); i++)); do
    sleep "$i"   
done

exit 0 #success




