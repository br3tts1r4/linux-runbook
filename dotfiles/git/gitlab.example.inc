# ~/.config/git/gitlab.inc
# Included automatically for repos under ~/projects/gitlab/

[user]
	name  = GitLabUserName
	email = gitlab-email@gitlab.com
	signingkey = XXXXXXXXXXXXXXXX

[commit]
	gpgsign = true

[url "git@gitlab.com:"]
	insteadOf = https://gitlab.com/
