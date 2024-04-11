#!/bin/bash

FILE="/usr/share/dict/words"
WORDS=()
COUNTWRONG=1
PRINTWRONG=1

function writeHelp() {
    helptext=""
    helptext+="default dictonary|$FILE\n"
    helptext+="-h, --help|show avalaiable options\n"
    helptext+="-d, --dir|change dictionary\n"
    helptext+="-s, --show|hide invalid words\n"
    helptext+="-n, --noscore|don't score invalid words\n"
    echo -e "$helptext" | column -t -s '|'
}

function calc() {
    local word=$1
    local -i score=0
    declare -i -A value=(
        [a]=1 [b]=3 [c]=3 [d]=2 [e]=1 [f]=4 [g]=2 [h]=4 [i]=1 [j]=8 [k]=5 [l]=1 [m]=3
        [n]=1 [o]=1 [p]=3 [q]=10 [r]=1 [s]=1 [t]=1 [u]=1 [v]=4 [w]=4 [x]=8 [y]=4 [z]=10 
    )
    for (( idx = 0; idx < ${#word}; idx++ )); do
        local -i p=value[${word:idx:1}]
        score+=${p}
    done
	point=$score
}

while [[ $# -gt 0 ]]; do
	case $1 in
		-h|--help)
			writeHelp
			exit 0;;
		-d|--dir)
			FILE=$2
			if [[ ! -e $FILE ]]; then
				echo "${FILE} does not exist!"
				exit 1
			fi
			shift 2;;
        -s|--show)
            PRINTWRONG=0
            shift;;
        -n|--noscore)
            COUNTWRONG=0
            shift;;
		-*|--*)
			echo "Unknown option"
			exit 1;;
		*)
			WORDS+=("${1,,}")
			shift;;
	esac
done
if [[ ${#WORDS[*]} -eq 0 ]]; then
	echo "Enter words, if you are done, press CTRL+D"
	while read WORD; do
		WORDS+=("${WORD,,}")
	done
fi

output='Word|IsValid|Points\n'
for word in ${WORDS[*]}
do
	if grep -qwi "${word}" "${FILE}"; then
		isValid=1
	else
		isValid=0
	fi
	calc "$word"
	if [[ $isValid -eq 1 || $PRINTWRONG -eq 1 ]]; then
		output+="${word}"
		output+='|'
		if [[ isValid -eq 1 ]]; then
			output+='yes|'
			output+="${point}"
			output+='\n'
		else
			output+='no|'
			if [[ $COUNTWRONG -eq 1 ]]; then
				output+="${point}"
			fi
            output+='\n'
		fi
	fi
done
echo -e "$output" | column -t -s '|'