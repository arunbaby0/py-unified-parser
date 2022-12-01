#! /bin/sh
###
### File ttsylb2.sh
### Shell script to proof-test tsylb2
###
# cd ..
# start=$(date +%s)
# time sleep 1
echo ${1} > temp
/Users/arunbaby/ZAPR/UnifiedParser/tsylb2-1.1/tsylb2 -n /Users/arunbaby/ZAPR/UnifiedParser/tsylb2-1.1/phon1ax.pcd 0 < temp

# /Users/arunbaby/ZAPR/UnifiedParser/tsylb2-1.1/tsylb2 -n /Users/arunbaby/ZAPR/UnifiedParser/tsylb2-1.1/phon1ax.pcd 0 < temp | grep "Basic pron" | cut -d'#' -f2 | sed 's#] \[#\- #g' | sed 's/]//g' | sed 's/\[//g' | sed "s/\'0//g"
# end=$(date +%s)
# echo Execution time was $(expr $end - $start) nanoseconds.
# diff testdata/test1n.out testdata/test1nx.out
# tsylb2 -f phon1ax.pcd 0 < testdata/test1.in > testdata/test1fx.out
# diff testdata/test1f.out testdata/test1fx.out
