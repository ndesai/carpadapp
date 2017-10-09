#!/usr/bin/env bash

set -e

DIR_SCRIPT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DIR_SOURCE=$(cd ${DIR_SCRIPT}/../ && pwd)
DIR_CURRENT=$PWD

cd ${DIR_SOURCE} && (${DIR_SCRIPT}/generate-qrc.sh qml ${DIR_SOURCE}/qml.qrc)
cd ${DIR_SOURCE} && (${DIR_SCRIPT}/generate-qrc.sh img ${DIR_SOURCE}/img.qrc)

cd ${DIR_CURRENT}/
qmake ${DIR_SOURCE}/
make -j10