# !/bin/bash

# move this file to build folder; need to run under
# the same folder with test_qos_file.xml

if [ ${#} -lt 3 ]; then
    echo "input params less than 3"
    echo "input #Node(e.g 3) Hz(e.g 10) testtime(e.g. 1 (mins))"
    exit 0
else
    echo "start dds performance test ... "
fi

PubDir="./DDS_test_publisher"
SubDir="./DDS_test_subscriber"
topicBase="DDSTest_"

$PubDir -tr "1" -tw "2" -n "1" -hz "${2}" >/dev/null 2>&1 &
for (( i=3; i<=$1; ))
do
    $SubDir -tr "${i}" -tw "$((${i}+1))" -n "${i}" -hz "${2}" >/dev/null 2>&1 &
    i=$((${i}+2))
done

for ((i = 1; i <= $(($3*60)); i++)); do
    echo "count time sec: '$i'"
    sleep "$i"   
done

exit 0 #success




