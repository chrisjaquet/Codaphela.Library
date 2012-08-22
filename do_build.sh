#!/bin/bash

INST_DIR="/media/Data0/DevTest/0Libraries/0PreBuilt"

# GENERATOR="Unix Makefiles"
# GENERATOR="CodeBlocks - Unix Makefiles"
GENERATOR="Eclipse CDT4 - Unix Makefiles"

echo Generator is ${GENERATOR}

CUR_DIR=${PWD}
BUILD_DIR=${CUR_DIR}/../build/Codaphela.Library
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
mkdir -p Debug
cd Debug
cmake -G "${GENERATOR}" ${CUR_DIR} -DCMAKE_INSTALL_PREFIX=${INST_DIR} -DCodaphelaLibrary_BUILD_SHARED_LIBRARY=ON -DCMAKE_BUILD_TYPE="Debug"
# make install
# cd ${BUILD_DIR}
# mkdir -p Release
# cd Release
# cmake -G ${GENERATOR} ${CUR_DIR} -DCMAKE_INSTALL_PREFIX=${INST_DIR} -DCodaphelaLibrary_BUILD_SHARED_LIBRARY=ON -DCMAKE_BUILD_TYPE="Release"
# make install
cd ${CUR_DIR}
