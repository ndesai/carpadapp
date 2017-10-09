#!/usr/bin/env bash

set -e

DIR_SCRIPT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Generate QRC

fn_usage() {
	echo "USAGE: ./${BASH_SOURCE[0]} [directory] [outputQrcFilename]"
	exit 1
}

if [ -z ${1} ]; then
	fn_usage
fi

if [ -z ${2} ]; then
	fn_usage
fi

BASE_DIRECTORY="${1}"
QRC_NAME="${2}"
QRC_FILENAME="${QRC_NAME}"
TEMP_QRC_FILENAME="${QRC_FILENAME}.tmp"

if [ ! -d "${BASE_DIRECTORY}" ]; then
	echo "Folder does not exist: ${BASE_DIRECTORY}"
	fn_usage
fi

#<RCC>
#    <qresource prefix="/">
#        <file>main_ios.qml</file>
#        <file>home.qml</file>
#        <file>dev.qml</file>
#        <file>img/triangular.png</file>
#    </qresource>
#</RCC>

{
	echo "<RCC>"
	echo -ne '\t'
	echo "<qresource prefix=\"/\">"
	for i in `find ${BASE_DIRECTORY} -type f | grep -v .DS_Store`; 
		do
			echo -ne '\t\t'
			echo "<file>${i}</file>"
	done;
	echo -ne '\t'
	echo "</qresource>"
	echo "</RCC>"
} >> ${TEMP_QRC_FILENAME}


mv ${TEMP_QRC_FILENAME} ${QRC_FILENAME} 
cat ${QRC_FILENAME}
