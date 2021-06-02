#!/bin/bash
###############################################################################
# Author: Savnick Patel and Maxwell Metzner
# Date: 02/13/2021
# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Description: A bash script to provide the basic functionality of a recycle bin. 
###############################################################################

#use readonly keyword when setting up the variable name for the .junk directory at the top of the script
readonly BIN="$HOME/.junk"
help_flag=0
list_flag=0
purge_flag=0
usage_message=$(cat << EOF 
Usage: $(basename "$0") [-hlp] [list of files]
    -h: Display help.
    -l: List junked files.
    -p: Purge all files.
    [list of files] with no other arguments to junk those files. 
EOF
)

#while loop to determine what flag the user used
#we can check for multiple flags used by chekcing
#if multiple variables were set to 1 (in which case we error)
#we can then test if the user puts in flags and files by
#checking if at least 1 flag was hit and the length of our file array is >=1
#-h: Display help.
#-l: List junked files.
#-p: Purge all files.
while getopts ":hlp" option; do    
	case "$option" in        
		h) help_flag=1           
			;;
		l) list_flag=1           
			;;
		p) purge_flag=1           
			;;        
		?) printf "Error: Unknown option '-%s'.\n" "$OPTARG" >&2
		 	echo "$usage_message"           
			exit 1     
			;;    
	esac
done

#adds the filenames the user inputs into the array filenames
declare -a filenames
shift "$((OPTIND-1))"
index=0
for f in "$@"; do   
	filenames[$index]="$f"   
	(( ++index ))
done


total_flags=$(( help_flag + list_flag + purge_flag ))

#sends out error if user puts in both flags and texts
if [ "${#filenames[@]}" -gt 0 ] && [ $total_flags -gt 0 ]; then   
	printf "Error: Too many options enabled.\n" >&2
	echo "$usage_message"        
	exit 1           
fi

#sends out error if user puts in multiple flags
if [ $total_flags -gt 1 ]; then
	printf "Error: Too many options enabled.\n" >&2
	echo "$usage_message"
	exit 1
fi

#checks if a .junk directory already exists
if [ ! -d "$HOME/.junk" ]; then
	mkdir "$BIN"
fi

#if no flags and no files are given, then print out usage message
if [ "${#filenames[@]}" -eq 0 ] && [ $total_flags -eq 0 ]; then   
	echo "$usage_message"        
	exit 0
fi

#if the user specifies the h flag, then print out usage message
if [ $help_flag -eq 1 ]; then
	echo "$usage_message"        
	exit 0
fi

#if the user specifies the l flag, then list junked files
if [ $list_flag -eq 1 ]; then
	ls -lAF "$BIN"  
	exit 0
fi

#if the user specifies the p flag, then purge all junked files
if [ $purge_flag -eq 1 ]; then
	rm -rf "$BIN"
	mkdir "$BIN"         
	exit 0
fi

#move files to .junk folder
for f in "${filenames[@]}"; do 
    if [ -f "$f" ] || [ -d "$f" ]; 
    then
        mv "$f" "$BIN"
    else
        printf "Warning: '%s' not found.\n" "$f"
    fi
done

exit 0
