#!/bin/bash
host=$(hostname)
if [ "${host%%raplab*}" != "${host}" ]; then
  logs=logs_raplab
elif [ "${host%%cern.ch}" != "${host}" ] && [ "${host##b}" != "${host}" ]; then
  logs=logs_lxbatch
else
  logs=logs
fi
cmd="./check.exe -p 2048 256 12"
trace=$logs/eemumuAV_`date +%m%d_%H%M`
( time ${cmd} ) 2>&1 | tee ${trace}.txt
if [ "${host%%cern.ch}" != "${host}" ] && [ "${host##b}" != "${host}" ]; then
  /usr/local/cuda-11.0/bin/ncu -o ${trace} ${cmd}
  /usr/local/cuda-10.1/bin/nsys profile -o ${trace} ${cmd}
  echo ""
  echo "TO ANALYSE TRACE FILES:"
  echo "  /usr/local/cuda-11.0/bin/ncu-ui &"
  echo "  /usr/local/cuda-10.1/bin/nsight-sys &"
else
  ncu -o ${trace} ${cmd}
  nsys profile -o ${trace} ${cmd}
  echo ""
  echo "TO ANALYSE TRACE FILES:"
  echo "  ncu-ui &"
  echo "  nsight-sys &"
fi

