#!/bin/bash
# Copyright (C) 2020-2023 CERN and UCLouvain.
# Licensed under the GNU Lesser General Public License (version 3 or later).
# Created by: A. Valassi (Oct 2023) for the MG5aMC CUDACPP plugin.
# Further modified by: A. Valassi (2023) for the MG5aMC CUDACPP plugin.

# Verbose script
###set -x

# Automatic exit on error
###set -e

# Path to the top directory of madgraphgpu
# In the CI this would be simply $(pwd), but allow the script to be run also outside the CI
echo "Executing $0 $*"; echo
topdir=$(cd $(dirname $0)/../..; pwd)

#----------------------------------------------------------------------------------------------------------------------------------

# Welcome
function welcome() {
  cd ${topdir}
  echo "Current directory is $(pwd)"
  echo "Current git commit is $(git log --oneline -n1 | cut -d' ' -f1)"
  #echo
  #echo "Contents of . (start)"
  #ls
  #echo "Contents of . (end)"
  #echo
  #echo "Contents of MG5aMC/mg5amcnlo (start)"
  #ls MG5aMC/mg5amcnlo
  #echo "Contents of MG5aMC/mg5amcnlo (end)"
}

#----------------------------------------------------------------------------------------------------------------------------------

# Code generation stage
function codegen() {
  cd ${topdir}/epochX/cudacpp
  echo "Current directory is $(pwd)"
  ###processes="$(git ls-tree --name-only HEAD *.mad *.sa)"
  processes="gg_tt.mad" # FOR QUICK TESTS
  for proc in $processes; do
    echo 
    echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
    echo "Code generation for ${proc}"
    echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
    if [ "${proc%.mad}" != "${proc}" ]; then
      # Generate code and check clang formatting
      ./CODEGEN/generateAndCompare.sh -q ${proc%.mad} --mad
    elif [ "${proc%.sa}" != "${proc}" ]; then
      # Generate code and check clang formatting
      ./CODEGEN/generateAndCompare.sh -q ${proc%.sa}
    else
      echo "WARNING! SKIP process directory '${proc}' because it does not end in .mad or .sa"
    fi
    # Check if there are any differences to the current repo
    git checkout HEAD ${proc}/CODEGEN*.txt
    if [ "${proc%.mad}" != "${proc}" ]; then
      git checkout HEAD ${proc}/Cards/me5_configuration.txt
      ###sed -i 's/DEFAULT_F2PY_COMPILER=f2py.*/DEFAULT_F2PY_COMPILER=f2py3/' ${proc}/Source/make_opts
      git checkout HEAD ${proc}/Source/make_opts
    fi
    echo
    echo "git diff (start)"
    git diff --exit-code
    echo "git diff (end)"
  done
}

#----------------------------------------------------------------------------------------------------------------------------------

function setup_ccache {
  # Set up ccache environment
  export PATH=${topdir}/BIN:$PATH
  export CCACHE_DIR=${topdir}/CCACHE_DIR
}

#----------------------------------------------------------------------------------------------------------------------------------

function tput_ini() {
  # Install and configure ccache
  mkdir ${topdir}/BIN
  cd ${topdir}/BIN
  echo "Current directory is $(pwd)"
  echo
  echo "wget -q https://github.com/ccache/ccache/releases/download/v4.8.3/ccache-4.8.3-linux-x86_64.tar.xz"
  wget -q https://github.com/ccache/ccache/releases/download/v4.8.3/ccache-4.8.3-linux-x86_64.tar.xz
  echo
  echo "tar -xvf ccache-4.8.3-linux-x86_64.tar.xz"
  tar -xvf ccache-4.8.3-linux-x86_64.tar.xz
  ln -sf ccache-4.8.3-linux-x86_64/ccache .
  # Set up ccache environment
  setup_ccache
  # Create the CCACHE_DIR directory if it was not retrieved from the cache
  echo
  if [ -d ${CCACHE_DIR} ]; then
    echo "Directory CCACHE_DIR=${CCACHE_DIR} already exists (retrieved from cache)"
  else
    echo "Directory CCACHE_DIR=${CCACHE_DIR} does not exist: create it"
    mkdir ${CCACHE_DIR}
  fi
  # Dump ccache status before the builds
  echo
  echo "ccache --version | head -1"
  ccache --version | head -1
  echo
  echo "CCACHE_DIR=${CCACHE_DIR}"
  echo "du -sm ${CCACHE_DIR}"
  du -sm ${CCACHE_DIR}
  echo
  echo "ccache -s (before the builds)"
  ccache -s
}

#----------------------------------------------------------------------------------------------------------------------------------

# Tput test stage (build, runTest.exe, check.exe, gcheck.exe)
function tput_run() {
  cd ${topdir}/epochX/cudacpp
  echo "Current directory is $(pwd)"
  # Set up ccache environment
  setup_ccache
  # Dump g++ environment
  echo
  echo "g++ --version"
  g++ --version
  # Build and test
  export CXX=g++ # set up CXX that is needed by cudacpp.mk
  export USECCACHE=1 # enable ccache in madgraph4gpu builds
  echo "./tput/teeThroughputX.sh -makej -ggtt -makeclean"
  ./tput/teeThroughputX.sh -makej -ggtt -makeclean
}

#----------------------------------------------------------------------------------------------------------------------------------

function tput_fin() {
  # Set up ccache environment
  setup_ccache
  # Dump ccache status after the builds
  echo
  echo "CCACHE_DIR=${CCACHE_DIR}"
  echo "du -sm ${CCACHE_DIR}"
  du -sm ${CCACHE_DIR}
  echo
  echo "ccache -s (after the builds)"
  ccache -s
}

#----------------------------------------------------------------------------------------------------------------------------------

# Usage
function usage() {
  echo "Usage: $(basename $0) <${stages// /|}>"
  exit 1
}

#----------------------------------------------------------------------------------------------------------------------------------

# Valid stages
stages="welcome codegen tput_ini tput_run tput_fin"

# Check input arguments
for astage in $stages; do
  if [ "$1" == "$astage" ]; then
    stage=$1; shift; break
  fi
done
if [ "$stage" == "" ] || [ "$1" != "" ]; then usage; fi

# Start
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "[manual.sh] $stage starting at $(date)"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

# Execute stage
( set -e; $stage ) # execute this within a subprocess and fail immediately on error
status=$?

# Finish
echo
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
if [ $status -eq 0 ]; then
  echo "[manual.sh] $stage finished with status=$status (OK) at $(date)"
else
  echo "[manual.sh] $stage finished with status=$status (NOT OK) at $(date)"
fi
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
exit $status
