#!/usr/bin/bash

DUNST_ID=9002

LAYOUTS=("en_US" "az" "ru")
LAYOUTS_MAX=2
LAYOUT=$(setxkbmap -query | grep layout)
LAYOUT=$(echo ${LAYOUT#"layout:"} | tr -d " ")

function get_name {
	case $1 in
		en_US)
			echo "en"
		;;
		az)
			echo "az"
		;;
		ru)
			echo "ru"
		;;
	esac
}

function set_next {
	LAY_INDEX=0
	
	for i in ${!LAYOUTS[@]}; do
		if [[ ${LAYOUTS[$i]} == $LAYOUT ]]; then
			LAY_INDEX=$i	
		fi
	done

	LAY_INDEX=$(($LAY_INDEX + 1))

	if [[ $LAY_INDEX -gt $LAYOUTS_MAX ]]; then
		LAY_INDEX=0
	fi
	
	setxkbmap ${LAYOUTS[$LAY_INDEX]}
}

# case $1 in
	# get)
		# echo $(get_name $LAYOUT) " "
	# ;;
	# set)
		# set_next
	# ;;
# esac

set_next
LAYOUT=$(setxkbmap -query | grep layout)
LAYOUT=$(echo ${LAYOUT#"layout:"} | tr -d " ")
dunstify "leyout set" $(get_name $LAYOUT) --replace $DUNST_ID
