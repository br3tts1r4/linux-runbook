# ~/.config/git/github.inc
# Included automatically for repos under ~/projects/github/

[user]
	name  = Your Name
	email = you@users.noreply.github.com
	# GPG key fingerprint (optional; remove signingkey + commit.gpgsign if unused)
	signingkey = XXXXXXXXXXXXXXXX

[commit]
	gpgsign = true

[url "git@github.com:"]
	insteadOf = https://github.com/
