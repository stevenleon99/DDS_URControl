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

$PubDir -tr "1" -tw "2" -n "1" -hz "${2}" &
for (( i=2; i<=$1; i++ ))
do
    $SubDir -tr "${i}" -tw "$((${i}+1))" -n "${i}" -hz "${2}" &
done

for ((i = 1; i <= $(($3*60)); i++)); do
    sleep "$i"   
done

exit 0 #success




