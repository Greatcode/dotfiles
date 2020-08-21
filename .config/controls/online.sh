#if [[ $(nm-online -t 1) ]]; then
if [[ $(ping -c1 google.com) ]]; then
	ONLINE="直"
else
	ONLINE="睊"
fi

echo "  $ONLINE   "
