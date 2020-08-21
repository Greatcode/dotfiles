BAT=$(acpi -b | awk '{ print $4 }' | tr -d ',%')
BAT_STATUS=$(acpi -b | awk '{ print $3 }' | tr -d ',')

# if [[ BAT -gt 75 ]]; then
	# BAT_ICON=""
# elif [[ BAT -gt 50 && BAT -le 75 ]]; then
	# BAT_ICON=""
# elif [[ BAT -gt 25 && BAT -le 50 ]]; then
	# BAT_ICON=""
# elif [[ BAT -gt 0 && BAT -le 25 ]]; then
	# BAT_ICON=""
# 
	# if [[ BAT -le 15 && ! BAT_WARNING_SENT ]]; then
		# dunstify "Battery too low" "Connect to charger" -u CRITICAL
		# BAT_WARNING_SENT = true
	# elif [[ BAT -gt 15 && BAT_WARNING_SENT ]]; then
		# BAT_WARNING_SENT = false
	# fi
	# 
# elif [[ BAT -le 0 ]]; then
	# BAT_ICON=""
# fi
# 
# if [[ "$BAT_STATUS" == "Discharging" ]]; then
	# BAT_STATUS_TEXT=" "
# elif [[ "$BAT_STATUS" == "Charging" ]]; then
	# BAT_STATUS_TEXT=""
# fi

if [[ BAT -gt 90 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 80 && BAT -le 90 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 70 && BAT -le 80 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 60 && BAT -le 70 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 50 && BAT -le 60 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 40 && BAT -le 50 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 30 && BAT -le 40 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 20 && BAT -le 30 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 10 && BAT -le 20 ]]; then
	BAT_ICON=""
elif [[ BAT -gt 0 && BAT -le 10 ]]; then
	BAT_ICON=""
elif [[ BAT -le 0 ]]; then
	BAT_ICON=""
fi

if [[ BAT -le 15 && ! BAT_WARNING_SENT ]]; then
	dunstify "Battery too low" "Connect to charger" -u CRITICAL
	BAT_WARNING_SENT = true
elif [[ BAT -gt 15 && BAT_WARNING_SENT ]]; then
	BAT_WARNING_SENT = false
fi

if [[ "$BAT_STATUS" == "Discharging" ]]; then
	BAT_STATUS_TEXT=" "
elif [[ "$BAT_STATUS" == "Charging" ]]; then
	BAT_STATUS_TEXT=""
fi

echo "$BAT_ICON $BAT%$BAT_STATUS_TEXT "
