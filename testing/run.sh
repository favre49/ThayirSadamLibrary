#! /bin/bash
# Usage:
# run.sh solution.cpp gen.cpp [checker.cpp]
# 
# How checker.cpp works:
# First it takes test input, and then the solution output. If the solution output is ok,
# print 1. Otherwise, print 0. You can print anything after that, since this script will
# only check the first character.
#
# Other notes:
# This creates the following files:
# test_solution (Solution executable)
# test_gen (Test generator executable)
# test_checker (Checker executable)
# tin (Test input)
# tout_solution (solution output)
# tout_checker (checker output)
# They will be removed if AC, otherwise they will persist for testing purposes.

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

#Typeface
BOLD=$(tput bold)
NORM=$(tput sgr0)

if [[ $# -lt 2 ]]; then 
  echo "Pass at least 2 arguments"
  exit 2
fi

echo "${BOLD}Solution: ${NORM}$1"
echo "${BOLD}Test Generator: ${NORM}$2"
if [[ -z "$3" ]]; then
  echo "${BOLD}No Checker given${NORM}"
else
  echo "${BOLD}Checker: ${NORM}$3"
fi

# Optional, consider removing. Currenly only exists because Abhinav uses
# -D ONLINE_JUDGE which wouldn't work well with piping
echo "${BOLD}Compiling...${NORM}"
g++ $1 -O2 -o test_solution
g++ $2 -O2 -o test_gen
if [[ ! -z "$3" ]]; then
  g++ $3 -O2 -o test_checker
fi

for i in {1..100}
do 
  echo -e "${NC}${BOLD}Test $i:${NORM}"
  ./test_gen > tin 
  start_time=`date +%s%N`
  ./test_solution < tin > tout_solution
  end_time=`date +%s%N`
  runtime=$(($end_time-$start_time))
  runtime=$(($runtime/1000000))
  if [[ $? -ge 128 ]]; then
    echo -e "${RED}Runtime Error"
    exit 2
  fi
  if [[ ! -z "$3" ]]; then
    # Checker given.
    cat tin > temp_in
    cat tout_solution >> temp_in
    ./test_checker < temp_in > tout_checker
    if read -n1 char < tout_checker; [[ $char = "0" ]]; then
      echo -e "${RED}Wrong Answer"
      exit 2
    fi
  fi
  echo -e "${GREEN}OK! Passed Tests in $runtime ms"
done
rm tin tout_solution test_solution test_gen
if [[ ! -z "$3" ]]; then
  rm temp_in tout_checker test_checker
fi
echo -e "${GREEN}All tests done!"

