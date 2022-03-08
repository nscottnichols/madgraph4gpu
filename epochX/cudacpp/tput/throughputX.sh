#!/bin/bash

set +x # not verbose
set -e # fail on error

scrdir=$(cd $(dirname $0); pwd)
bckend=$(basename $(cd $scrdir; cd ..; pwd)) # cudacpp or alpaka
topdir=$(cd $scrdir; cd ../../..; pwd)

# This is no longer necessary as check/gcheck/runTest.exe are now built using rpath
###export LD_LIBRARY_PATH_start=$LD_LIBRARY_PATH
###export DYLD_LIBRARY_PATH_start=$DYLD_LIBRARY_PATH

function usage()
{
  echo "Usage: $0 <processes[-eemumu] [-ggtt] [-ggttg] [-ggttgg] [-ggttggg]> [-nocpp|[-omp][-avxall][-nocuda]] [-auto|-autoonly] [-noalpaka] [-flt|-fltonly] [-inl|-inlonly] [-hrd|-hrdonly] [-common|-curhst] [-rmbhst|-bridge] [-makeonly|-makeclean|-makecleanonly] [-makej] [-3a3b] [-div] [-req] [-detailed] [-gtest] [-v]"
  exit 1
}

##########################################################################
# PART 0 - decode command line arguments
##########################################################################

eemumu=0
ggtt=0
ggttg=0
ggttgg=0
ggttggg=0
suffs="/"

omp=0
avxall=0
cpp=1
cuda=1
alpaka=1

fptypes="d"
helinls="0"
hrdcods="0"
rndgen=""
rmbsam=""

maketype=
makej=

ab3=0
div=0
req=0
detailed=0
gtest=0
verbose=0

if [ "$bckend" != "alpaka" ]; then alpaka=0; fi # alpaka mode is only available in the alpaka directory

while [ "$1" != "" ]; do
  if [ "$1" == "-eemumu" ]; then
    eemumu=1
    shift
  elif [ "$1" == "-ggtt" ]; then
    ggtt=1
    shift
  elif [ "$1" == "-ggttg" ]; then
    ggttg=1
    shift
  elif [ "$1" == "-ggttgg" ]; then
    ggttgg=1
    shift
  elif [ "$1" == "-ggttggg" ]; then
    ggttggg=1
    shift
  elif [ "$1" == "-auto" ]; then
    if [ "${suffs}" == ".auto/" ]; then echo "ERROR! Options -auto and -autoonly are incompatible"; usage; fi
    suffs="/ .auto/"
    shift
  elif [ "$1" == "-autoonly" ]; then
    if [ "${suffs}" == "/ .auto/" ]; then echo "ERROR! Options -auto and -autoonly are incompatible"; usage; fi
    suffs=".auto/"
    shift
  elif [ "$1" == "-omp" ]; then
    if [ "${cpp}" == "0" ]; then echo "ERROR! Options -omp and -nocpp are incompatible"; usage; fi
    omp=1
    shift
  elif [ "$1" == "-avxall" ]; then
    if [ "${cpp}" == "0" ]; then echo "ERROR! Options -avxall and -nocpp are incompatible"; usage; fi
    avxall=1
    shift
  elif [ "$1" == "-nocuda" ]; then
    if [ "${cpp}" == "0" ]; then echo "ERROR! Options -nocuda and -nocpp are incompatible"; usage; fi
    cuda=0
    shift
  elif [ "$1" == "-nocpp" ]; then
    if [ "${omp}" == "1" ]; then echo "ERROR! Options -omp and -nocpp are incompatible"; usage; fi
    if [ "${avxall}" == "1" ]; then echo "ERROR! Options -avxall and -nocpp are incompatible"; usage; fi
    if [ "${cuda}" == "0" ]; then echo "ERROR! Options -nocuda and -nocpp are incompatible"; usage; fi
    cpp=0
    shift
  elif [ "$1" == "-noalpaka" ]; then
    alpaka=0
    shift
  elif [ "$1" == "-flt" ]; then
    if [ "${fptypes}" == "f" ]; then echo "ERROR! Options -flt and -fltonly are incompatible"; usage; fi
    fptypes="d f"
    shift
  elif [ "$1" == "-fltonly" ]; then
    if [ "${fptypes}" == "d f" ]; then echo "ERROR! Options -flt and -fltonly are incompatible"; usage; fi
    fptypes="f"
    shift
  elif [ "$1" == "-inl" ]; then
    if [ "${helinls}" == "1" ]; then echo "ERROR! Options -inl and -inlonly are incompatible"; usage; fi
    helinls="0 1"
    shift
  elif [ "$1" == "-inlonly" ]; then
    if [ "${helinls}" == "0 1" ]; then echo "ERROR! Options -inl and -inlonly are incompatible"; usage; fi
    helinls="1"
    shift
  elif [ "$1" == "-hrd" ]; then
    if [ "${hrdcods}" == "1" ]; then echo "ERROR! Options -hrd and -hrdonly are incompatible"; usage; fi
    hrdcods="0 1"
    shift
  elif [ "$1" == "-hrdonly" ]; then
    if [ "${hrdcods}" == "0 1" ]; then echo "ERROR! Options -hrd and -hrdonly are incompatible"; usage; fi
    hrdcods="1"
    shift
  elif [ "$1" == "-common" ]; then
    rndgen=" -${1}"
    shift
  elif [ "$1" == "-curhst" ]; then
    rndgen=" -${1}"
    shift
  elif [ "$1" == "-rmbhst" ]; then
    rmbsmp=" -${1}"
    shift
  elif [ "$1" == "-bridge" ]; then
    rmbsmp=" -${1}"
    shift
  elif [ "$1" == "-makeonly" ] || [ "$1" == "-makeclean" ] || [ "$1" == "-makecleanonly" ]; then
    if [ "${maketype}" != "" ] && [ "${maketype}" != "$1" ]; then
      echo "ERROR! Options -makeonly, -makeclean and -makecleanonly are incompatible"; usage
    fi
    maketype="$1"
    shift
  elif [ "$1" == "-makej" ]; then
    makej=-j
    shift
  elif [ "$1" == "-3a3b" ]; then
    ab3=1
    shift
  elif [ "$1" == "-div" ]; then
    div=1
    shift
  elif [ "$1" == "-req" ]; then
    req=1
    shift
  elif [ "$1" == "-detailed" ]; then
    detailed=1
    shift
  elif [ "$1" == "-gtest" ]; then
    # For simplicity a gtest runTest.exe is executed for each build where check.exe is executed
    if [ "${cpp}" == "0" ]; then echo "ERROR! Options -gtest and -nocpp are incompatible"; usage; fi
    gtest=1
    shift
  elif [ "$1" == "-v" ]; then
    verbose=1
    shift
  else
    usage
  fi
done
###exit 1

# Check that at least one process has been selected
if [ "${eemumu}" == "0" ] && [ "${ggtt}" == "0" ] && [ "${ggttg}" == "0" ] && [ "${ggttgg}" == "0" ] && [ "${ggttggg}" == "0" ]; then usage; fi

# Use only the .auto process directories in the alpaka directory
if [ "$bckend" == "alpaka" ]; then
  echo "WARNING! alpaka directory: using .auto process directories only"
  suffs=".auto/"
fi

# Use only HRDCOD=0 in the alpaka directory (old epochX-golden2 code base)
if [ "$bckend" == "alpaka" ]; then
  echo "WARNING! alpaka directory: using HRDCOD=0 only"
  hrdcods="0"
fi

# Check whether Alpaka should and can be run
if [ "${alpaka}" == "1" ]; then
  if [ "${CUPLA_ROOT}" == "" ]; then echo "ERROR! CUPLA_ROOT is not set!"; exit 1; fi
  echo "CUPLA_ROOT=$CUPLA_ROOT"
  if [ ! -d "${CUPLA_ROOT}" ]; then echo "ERROR! $CUPLA_ROOT does not exist!"; exit 1; fi
  if [ "${ALPAKA_ROOT}" == "" ]; then echo "ERROR! ALPAKA_ROOT is not set!"; exit 1; fi
  echo "ALPAKA_ROOT=$ALPAKA_ROOT"
  if [ ! -d "${ALPAKA_ROOT}" ]; then echo "ERROR! $ALPAKA_ROOT does not exist!"; exit 1; fi
  if [ "${BOOSTINC}" == "" ]; then echo "ERROR! BOOSTINC is not set!"; exit 1; fi
  echo "BOOSTINC=$BOOSTINC"
  if [ ! -d "${BOOSTINC}" ]; then echo "ERROR! $BOOSTINC does not exist!"; exit 1; fi  
else
  export CUPLA_ROOT=none
fi

###echo -e "\n********************************************************************************\n"
printf "\n"

##########################################################################
# PART 1 - compile the list of the executables which should be run
##########################################################################

exes=

for suff in $suffs; do

  #=====================================
  # CUDA   (epochX - manual/auto)
  # ALPAKA (epochX - manual/auto)
  #=====================================
  if [ "${cuda}" == "1" ]; then
    if [ "${eemumu}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/ee_mumu${suff}SubProcesses/P1_Sigma_sm_epem_mupmum
    elif [ "${ggtt}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_tt${suff}SubProcesses/P1_Sigma_sm_gg_ttx
    elif [ "${ggttg}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_ttg${suff}SubProcesses/P1_Sigma_sm_gg_ttxg
    elif [ "${ggttgg}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_ttgg${suff}SubProcesses/P1_Sigma_sm_gg_ttxgg
    elif [ "${ggttggg}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_ttggg${suff}SubProcesses/P1_Sigma_sm_gg_ttxggg
    fi
    for hrdcod in $hrdcods; do
      hrdsuf=_hrd${hrdcod}
      if [ "$bckend" == "alpaka" ]; then hrdsuf=""; fi
      for helinl in $helinls; do
        for fptype in $fptypes; do
          exes="$exes ${dir}/build.none_${fptype}_inl${helinl}${hrdsuf}/gcheck.exe"
          if [ "${alpaka}" == "1" ]; then
            exes="$exes ${dir}/build.none_${fptype}_inl${helinl}${hrdsuf}/alpcheck.exe"
          fi
        done
      done
    done
  fi
  
  #=====================================
  # C++ (eemumu/epochX - manual/auto)
  #=====================================
  if [ "${cpp}" == "1" ]; then 
    if [ "${eemumu}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/ee_mumu${suff}SubProcesses/P1_Sigma_sm_epem_mupmum
    elif [ "${ggtt}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_tt${suff}SubProcesses/P1_Sigma_sm_gg_ttx
    elif [ "${ggttg}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_ttg${suff}SubProcesses/P1_Sigma_sm_gg_ttxg
    elif [ "${ggttgg}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_ttgg${suff}SubProcesses/P1_Sigma_sm_gg_ttxgg
    elif [ "${ggttggg}" == "1" ]; then 
      dir=$topdir/epochX/${bckend}/gg_ttggg${suff}SubProcesses/P1_Sigma_sm_gg_ttxggg
    fi
    for hrdcod in $hrdcods; do
      hrdsuf=_hrd${hrdcod}
      if [ "$bckend" == "alpaka" ]; then hrdsuf=""; fi
      for helinl in $helinls; do
        for fptype in $fptypes; do
          exes="$exes $dir/build.none_${fptype}_inl${helinl}${hrdsuf}/check.exe"
          if [ "${avxall}" == "1" ]; then 
            exes="$exes $dir/build.sse4_${fptype}_inl${helinl}${hrdsuf}/check.exe"
            exes="$exes $dir/build.avx2_${fptype}_inl${helinl}${hrdsuf}/check.exe"
          fi
          if [ "$(grep -m1 -c avx512vl /proc/cpuinfo)" == "1" ]; then 
            exes="$exes $dir/build.512y_${fptype}_inl${helinl}${hrdsuf}/check.exe"
            if [ "${avxall}" == "1" ]; then 
              exes="$exes $dir/build.512z_${fptype}_inl${helinl}${hrdsuf}/check.exe"
            fi
          fi
        done
      done
    done
  fi

done

##########################################################################
# PART 2 - build the executables which should be run
##########################################################################

###echo "exes=$exes"

for suff in $suffs; do

  if [ "${eemumu}" == "1" ]; then 
    dir=$topdir/epochX/${bckend}/ee_mumu${suff}SubProcesses/P1_Sigma_sm_epem_mupmum
  elif [ "${ggtt}" == "1" ]; then 
    dir=$topdir/epochX/${bckend}/gg_tt${suff}SubProcesses/P1_Sigma_sm_gg_ttx
  elif [ "${ggttg}" == "1" ]; then 
    dir=$topdir/epochX/${bckend}/gg_ttg${suff}SubProcesses/P1_Sigma_sm_gg_ttxg
  elif [ "${ggttgg}" == "1" ]; then 
    dir=$topdir/epochX/${bckend}/gg_ttgg${suff}SubProcesses/P1_Sigma_sm_gg_ttxgg
  elif [ "${ggttggg}" == "1" ]; then 
    dir=$topdir/epochX/${bckend}/gg_ttggg${suff}SubProcesses/P1_Sigma_sm_gg_ttxggg
  fi

  export USEBUILDDIR=1
  pushd $dir >& /dev/null
  pwd
  if [ "${maketype}" == "-makeclean" ]; then make cleanall; echo; fi
  if [ "${maketype}" == "-makecleanonly" ]; then make cleanall; echo; continue; fi
  for hrdcod in $hrdcods; do
    export HRDCOD=$hrdcod
    for helinl in $helinls; do
      export HELINL=$helinl
      for fptype in $fptypes; do
        export FPTYPE=$fptype
        if [ "${avxall}" == "1" ]; then
          make ${makej} avxall; echo
        else
          make ${makej} AVX=none; echo
          make ${makej} AVX=512y; echo
        fi
      done
    done
  done
  popd >& /dev/null
  export USEBUILDDIR=
  export HRDCOD=
  export HELINL=
  export FPTYPE=

done

if [ "${maketype}" == "-makecleanonly" ]; then printf "MAKE CLEANALL COMPLETED\n"; exit 0; fi
if [ "${maketype}" == "-makeonly" ]; then printf "MAKE COMPLETED\n"; exit 0; fi

##########################################################################
# PART 3 - run all the executables which should be run
##########################################################################

printf "DATE: $(date '+%Y-%m-%d_%H:%M:%S')\n\n"

function runExe() {
  exe=$1
  args="$2"
  args="$args$rndgen$rmbsmp"
  echo "runExe $exe $args OMP=$OMP_NUM_THREADS"
  pattern="Process|fptype_sv|OMP threads|EvtsPerSec\[MECalc|MeanMatrix|FP precision|TOTAL       :"
  # Optionally add other patterns here for some specific configurations (e.g. clang)
  if [ "${exe%%/gcheck*}" != "${exe}" ]; then pattern="${pattern}|EvtsPerSec\[Matrix"; fi
  pattern="${pattern}|Workflow"
  ###pattern="${pattern}|CUCOMPLEX"
  ###pattern="${pattern}|COMMON RANDOM|CURAND HOST \(CUDA"
  pattern="${pattern}|ERROR"
  pattern="${pattern}|WARNING"
  pattern="${pattern}|EvtsPerSec\[Rmb" # TEMPORARY! for rambo timing tests
  pattern="${pattern}|EvtsPerSec\[Matrix" # TEMPORARY! OLD C++/CUDA CODE
  if [ "${ab3}" == "1" ]; then pattern="${pattern}|3a|3b"; fi
  if [ "${req}" == "1" ]; then pattern="${pattern}|memory layout"; fi
  if perf --version >& /dev/null; then
    # -- Newer version using perf stat
    pattern="${pattern}|instructions|cycles"
    pattern="${pattern}|elapsed"
    if [ "${detailed}" == "1" ]; then pattern="${pattern}|#"; fi
    if [ "${verbose}" == "1" ]; then set -x; fi
    ###perf stat -d $exe $args 2>&1 | grep -v "Performance counter stats"
    perf stat -d $exe $args 2>&1 | egrep "(${pattern})" | grep -v "Performance counter stats"
    set +x
  else
    # -- Older version using time
    # For TIMEFORMAT see https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html
    if [ "${verbose}" == "1" ]; then set -x; fi
    TIMEFORMAT=$'real\t%3lR' && time $exe $args 2>&1 | egrep "(${pattern})"
    set +x
  fi
}

function cmpExe() {
  exe=$1
  exef=${exe/\/check//gcheck}
  exef=${exef/\/gcheck//fgcheck}
  argsf="2 64 2"
  args="--common -p ${argsf}"
  echo "cmpExe $exe $args"
  echo "cmpExe $exef $argsf"
  tmp=$(mktemp)
  me1=$(${exe} ${args} 2>${tmp} | grep MeanMatrix | awk '{print $4}'); cat ${tmp}
  me2=$(${exef} ${argsf} 2>${tmp} | grep Average | awk '{print $4}'); cat ${tmp}
  if [ "${exe%%/gcheck*}" != "${exe}" ]; then tag="/CUDA)"; else tag="/C++) "; fi
  echo -e "Avg ME (C++${tag}   = ${me1}\nAvg ME (F77${tag}   = ${me2}"
  if [ "${me2}" == "NaN" ]; then
    echo "ERROR! Fortran calculation (F77${tag} returned NaN"
  elif [ "${me2}" == "" ]; then
    echo "ERROR! Fortran calculation (F77${tag} crashed"
  else
    # NB skip python comparison if Fortran returned NaN or crashed, otherwise python returns an error status and the following tests are not executed
    python -c "me1=${me1}; me2=${me2}; reldif=abs((me2-me1)/me1); print('Relative difference =', reldif); ok = reldif <= 2E-4; print ( '%s (relative difference %s 2E-4)' % ( ('OK','<=') if ok else ('ERROR','>') ) )"
  fi
}

# Profile #registers and %divergence only
function runNcu() {
  exe=$1
  args="$2"
  args="$args$rndgen$rmbsmp"
  ###echo "runNcu $exe $args"
  if [ "${verbose}" == "1" ]; then set -x; fi
  #$(which ncu) --metrics launch__registers_per_thread,sm__sass_average_branch_targets_threads_uniform.pct --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args | egrep '(sigmaKin|registers| sm)' | tr "\n" " " | awk '{print $1, $2, $3, $15, $17; print $1, $2, $3, $18, $20$19}'
  out=$($(which ncu) --metrics launch__registers_per_thread,sm__sass_average_branch_targets_threads_uniform.pct --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args | egrep '(sigmaKin|registers| sm)' | tr "\n" " ")
  ###echo $out
  echo $out | awk -v key1="launch__registers_per_thread" '{val1="N/A"; for (i=1; i<=NF; i++){if ($i==key1 && $(i+1)!="(!)") val1=$(i+2)}; print $1, $2, $3, key1, val1}'
  echo $out | awk -v key1="sm__sass_average_branch_targets_threads_uniform.pct" '{val1="N/A"; for (i=1; i<=NF; i++){if ($i==key1 && $(i+1)!="(!)") val1=$(i+2)$(i+1)}; print $1, $2, $3, key1, val1}'
  set +x
}

# Profile divergence metrics more in detail
# See https://www.pgroup.com/resources/docs/18.10/pdf/pgi18profug.pdf
# See https://docs.nvidia.com/gameworks/content/developertools/desktop/analysis/report/cudaexperiments/kernellevel/branchstatistics.htm
# See https://docs.nvidia.com/gameworks/content/developertools/desktop/analysis/report/cudaexperiments/sourcelevel/divergentbranch.htm
function runNcuDiv() {
  exe=$1
  args="-p 1 32 1"
  args="$args$rndgen$rmbsmp"
  ###echo "runNcuDiv $exe $args"
  if [ "${verbose}" == "1" ]; then set -x; fi
  ###$(which ncu) --query-metrics $exe $args
  ###$(which ncu) --metrics regex:.*branch_targets.* --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args
  ###$(which ncu) --metrics regex:.*stalled_barrier.* --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args
  ###$(which ncu) --metrics sm__sass_average_branch_targets_threads_uniform.pct,smsp__warps_launched.sum,smsp__sass_branch_targets.sum,smsp__sass_branch_targets_threads_divergent.sum,smsp__sass_branch_targets_threads_uniform.sum --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args | egrep '(sigmaKin| sm)' | tr "\n" " " | awk '{printf "%29s: %-51s %s\n", "", $18, $19; printf "%29s: %-51s %s\n", "", $22, $23; printf "%29s: %-51s %s\n", "", $20, $21; printf "%29s: %-51s %s\n", "", $24, $26}'
  #$(which ncu) --metrics sm__sass_average_branch_targets_threads_uniform.pct,smsp__warps_launched.sum,smsp__sass_branch_targets.sum,smsp__sass_branch_targets_threads_divergent.sum,smsp__sass_branch_targets_threads_uniform.sum,smsp__sass_branch_targets.sum.per_second,smsp__sass_branch_targets_threads_divergent.sum.per_second,smsp__sass_branch_targets_threads_uniform.sum.per_second --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args | egrep '(sigmaKin| sm)' | tr "\n" " " | awk '{printf "%29s: %-51s %-10s %s\n", "", $18, $19, $22$21; printf "%29s: %-51s %-10s %s\n", "", $28, $29, $32$31; printf "%29s: %-51s %-10s %s\n", "", $23, $24, $27$26; printf "%29s: %-51s %s\n", "", $33, $35}'
  out=$($(which ncu) --metrics sm__sass_average_branch_targets_threads_uniform.pct,smsp__warps_launched.sum,smsp__sass_branch_targets.sum,smsp__sass_branch_targets_threads_divergent.sum,smsp__sass_branch_targets_threads_uniform.sum,smsp__sass_branch_targets.sum.per_second,smsp__sass_branch_targets_threads_divergent.sum.per_second,smsp__sass_branch_targets_threads_uniform.sum.per_second --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args | egrep '(sigmaKin| sm)' | tr "\n" " ")
  ###echo $out
  echo $out | awk -v key1="smsp__sass_branch_targets.sum" '{key2=key1".per_second"; val1="N/A"; val2=""; for (i=1; i<=NF; i++){if ($i==key1 && $(i+1)!="(!)") val1=$(i+1); if ($i==key2 && $(i+1)!="(!)") val2=$(i+2)$(i+1)}; printf "%29s: %-51s %-10s %s\n", "", key1, val1, val2}'
  echo $out | awk -v key1="smsp__sass_branch_targets_threads_uniform.sum" '{key2=key1".per_second"; val1="N/A"; val2=""; for (i=1; i<=NF; i++){if ($i==key1 && $(i+1)!="(!)") val1=$(i+1); if ($i==key2 && $(i+1)!="(!)") val2=$(i+2)$(i+1)}; printf "%29s: %-51s %-10s %s\n", "", key1, val1, val2}'
  echo $out | awk -v key1="smsp__sass_branch_targets_threads_divergent.sum" '{key2=key1".per_second"; val1="N/A"; val2=""; for (i=1; i<=NF; i++){if ($i==key1 && $(i+1)!="(!)") val1=$(i+1); if ($i==key2 && $(i+1)!="(!)") val2=$(i+2)$(i+1)}; printf "%29s: %-51s %-10s %s\n", "", key1, val1, val2}'
  echo $out | awk -v key="smsp__warps_launched.sum" '{val1="N/A"; for (i=1; i<=NF; i++){if ($i==key && $(i+1)!="(!)") val1=$(i+2)}; printf "%29s: %-51s %s\n", "", key, val1}'
  set +x
}

# Profiles sectors and requests
function runNcuReq() {
  exe=$1
  ncuArgs="$2"
  ncuArgs="$ncuArgs$rndgen$rmbsmp"
  if [ "${verbose}" == "1" ]; then set -x; fi
  for args in "-p 1 1 1" "-p 1 4 1" "-p 1 8 1" "-p 1 32 1" "$ncuArgs"; do
    ###echo "runNcuReq $exe $args"
    # NB This will print nothing if $args are invalid (eg "-p 1 4 1" when neppR=8)
    $(which ncu) --metrics l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum,l1tex__t_requests_pipe_lsu_mem_global_op_ld.sum,launch__registers_per_thread,sm__sass_average_branch_targets_threads_uniform.pct --target-processes all --kernel-id "::sigmaKin:" --kernel-base mangled $exe $args | egrep '(sigmaKin|registers| sm|l1tex)' | tr "\n" " " | awk -vtag="[$args]" '{print $1, $2, $3, $16"s", $17";", $19"s", $20, tag}'
  done
  set +x
}

if nvidia-smi -L > /dev/null 2>&1; then gpuTxt="$(nvidia-smi -L | wc -l)x $(nvidia-smi -L | awk '{print $3,$4}' | sort -u)"; else gpuTxt=none; fi
unamep=$(uname -p)
if [ "${unamep}" == "ppc64le" ]; then 
  cpuTxt=$(cat /proc/cpuinfo | grep ^machine | awk '{print substr($0,index($0,"Power"))", "}')$(cat /proc/cpuinfo | grep ^cpu | head -1 | awk '{print substr($0,index($0,"POWER"))}')
else
  cpuTxt=$(cat /proc/cpuinfo | grep '^model name' |& head -1 | awk '{i0=index($0,"Intel"); if (i0==0) i0=index($0,"AMD"); i1=index($0," @"); if (i1>0) {print substr($0,i0,i1-i0)} else {print substr($0,i0)}}')
fi
echo -e "On $HOSTNAME [CPU: $cpuTxt] [GPU: $gpuTxt]:"

lastExe=
for exe in $exes; do
  ###echo EXE=$exe; continue
  exeArgs2=""
  if [ ! -f $exe ]; then echo "Not found: $exe"; continue; fi
  if [ "${exe%%/gcheck*}" != "${exe}" ] && [ "$gpuTxt" == "none" ]; then continue; fi
  if [ "${exe%%/gg_ttggg*}" != "${exe}" ]; then 
    # For ggttggg: this is far too little for GPU (4.8E2), but it keeps the CPU to a manageble level (1sec with 512y)
    exeArgs="-p 1 256 1"
    ncuArgs="-p 1 256 1"
    # For ggttggg: on GPU test also "64 256" to reach the plateau (only ~5% lower than "2048 256": 1.18E4 vs 1.25E4 on cuda116/gcc102)
    exeArgs2="-p 64 256 1"
  elif [ "${exe%%/gg_ttgg*}" != "${exe}" ]; then 
    # For ggttgg (OLD): this is a good GPU middle point: tput is 1.5x lower with "32 256 1", only a few% higher with "128 256 1"
    exeArgs="-p 64 256 1"
    ncuArgs="-p 64 256 1"
    # For ggttgg (NEW): on GPU test both "64 256" and "2048 256" for ggttgg as the latter gives ~10% higher throughput on cuda110/gcc92
    exeArgs2="-p 2048 256 1"
  elif [ "${exe%%/gg_ttg*}" != "${exe}" ]; then 
    # For ggttg, as on ggttgg: this is a good GPU middle point: tput is 1.5x lower with "32 256 1", only a few% higher with "128 256 1"
    exeArgs="-p 64 256 1"
    ncuArgs="-p 64 256 1"
    # For ggttg, as on ggttgg: on GPU test both "64 256" and "2048 256" for ggttg as the latter gives ~10% higher throughput on cuda110/gcc92
    exeArgs2="-p 2048 256 1"
  elif [ "${exe%%/gg_tt*}" != "${exe}" ]; then 
    exeArgs="-p 2048 256 1"
    ncuArgs="-p 2048 256 1"
  else # eemumu
    exeArgs="-p 2048 256 12"
    ncuArgs="-p 2048 256 1"
  fi
  if [ "$(basename $exe)" != "$lastExe" ]; then
    echo "========================================================================="
    lastExe=$(basename $exe)
  else
    echo "-------------------------------------------------------------------------"
  fi
  exeDir=$(dirname $exe)
  cd $exeDir/.. # workaround for reading '../../Cards/param_card.dat' without setting MG5AMC_CARD_PATH
  # This is no longer necessary as check/gcheck/runTest.exe are now built using rpath
  ###libDir=$exeDir/../../../lib/$(basename $exeDir)
  ###if [ ! -d $libDir ]; then echo "WARNING! $libDir not found"; else libDir=$(cd $libDir; pwd -P); fi
  ###export LD_LIBRARY_PATH=$libDir:$LD_LIBRARY_PATH_start
  ###export DYLD_LIBRARY_PATH=$libDir:$DYLD_LIBRARY_PATH_start
  ###echo "LD_LIBRARY_PATH=$libDir:..."
  unset OMP_NUM_THREADS
  runExe $exe "$exeArgs"
  if [ "${exe%%/check*}" != "${exe}" ]; then 
    obj=${exe%%/check*}/CPPProcess.o; $scrdir/simdSymSummary.sh -stripdir ${obj}
    if [ "${omp}" == "1" ]; then 
      echo "-------------------------------------------------------------------------"
      export OMP_NUM_THREADS=$(nproc --all)
      runExe $exe "$exeArgs"
      unset OMP_NUM_THREADS
    fi
    if [ "${gtest}" == "1" ]; then
      echo "-------------------------------------------------------------------------"
      exe2=${exe/check/runTest}
      echo "runExe $exe2"
      $exe2 2>&1 | tail -1
    fi
  elif [ "${exe%%/gcheck*}" != "${exe}" ] ||  [ "${exe%%/alpcheck*}" != "${exe}" ]; then 
    runNcu $exe "$ncuArgs"
    if [ "${div}" == "1" ]; then runNcuDiv $exe; fi
    if [ "${req}" == "1" ]; then runNcuReq $exe "$ncuArgs"; fi
    if [ "${exeArgs2}" != "" ]; then echo "........................................................................."; runExe $exe "$exeArgs2"; fi
  fi
  if [ "${bckend}" != "alpaka" ]; then
    echo "-------------------------------------------------------------------------"
    cmpExe $exe
  fi
done
echo "========================================================================="

# Workaround for reading of data files
popd >& /dev/null
printf "\nTEST COMPLETED\n"