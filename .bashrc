PROMPT_COMMAND=__prompt_command

__prompt_command(){
	ret=$?
	if [ $ret -ne 0 ]; then
		ARROW_COL="\e[31m"
	else
		ARROW_COL="\e[32m"
	fi

	#PS1="\e[33m\w$ARROW_COL →\e[37m "
	#PS1="\e[33m\w$ARROW_COL >\e[37m "
	PS1="\e[33m\w$ARROW_COL >>\e[37m "
}

__cd(){
	cd $@ && ls --color=auto
}

__junk(){
	for f in $@; do
		cp -aT $f ~/.Trash/$f && rm -rf $f
	done
	names=$(echo $@ | sed "s/ /, /g")
	echo "junked $names"
}

__newexec(){
	echo "#!$(which $2)" >> $1 && chmod +x $1 && micro $1
}

alias s="sudo"
alias c="clear"

#nano
alias n="nano"
alias sn="sudo nano"

#micro
alias m="micro"
alias sm="sudo micro"

#colors
alias ls="ls --color=auto"
alias diff='diff --color=auto'
alias grep='grep --color=auto'
alias ip='ip -color=auto'

export LESS=-R
export LESS_TERMCAP_mb=$'\E[1;31m'     # begin blink
export LESS_TERMCAP_md=$'\E[1;36m'     # begin bold
export LESS_TERMCAP_me=$'\E[0m'        # reset bold/blink
export LESS_TERMCAP_so=$'\E[01;44;33m' # begin reverse video
export LESS_TERMCAP_se=$'\E[0m'        # reset reverse video
export LESS_TERMCAP_us=$'\E[1;32m'     # begin underline
export LESS_TERMCAP_ue=$'\E[0m'        # reset underline

#verbosity
alias cp="cp -v"
alias mv="mv -v"

#utils
alias autoremove="sudo pacman -Rns $(pacman -Qtdq)"
alias cd="__cd"
alias junk="__junk"
alias newexec="__newexec"