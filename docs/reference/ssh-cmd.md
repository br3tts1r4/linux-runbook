# SSH Commands

## Connecting

| Command | Purpose |
|---|---|
| `ssh user@host` | Basic connection |
| `ssh -p 2222 user@host` | Connect on a non-default port |
| `ssh -i ~/.ssh/keys/work_ed25519 user@host` | Specify a key explicitly |
| `ssh work` | Connect using a Host alias from config |
| `ssh -v user@host` | Verbose — debug connection issues |
| `ssh -J bastion user@host` | Jump through a bastion host |

## Key management

| Command | Purpose |
|---|---|
| `ssh-keygen -t ed25519 -C "label" -f ~/.ssh/keys/name` | Generate a new key pair |
| `ssh-copy-id -i ~/.ssh/keys/work_ed25519.pub user@host` | Install public key on server |
| `ssh-keygen -p -f ~/.ssh/keys/work_ed25519` | Change passphrase on existing key |
| `ssh-keygen -l -f ~/.ssh/keys/work_ed25519` | Show key fingerprint |
| `ssh-keygen -y -f ~/.ssh/keys/work_ed25519` | Recover public key from private |

## ssh-agent

| Command | Purpose |
|---|---|
| `eval "$(ssh-agent -s)"` | Start agent and export env vars |
| `ssh-add ~/.ssh/keys/work_ed25519` | Add key to agent (prompted for passphrase) |
| `ssh-add -l` | List keys currently in agent |
| `ssh-add -D` | Remove all keys from agent |
| `ssh-add -t 3600 ~/.ssh/keys/name` | Add key with 1h expiry |

## Tunnelling & forwarding

| Command | Purpose |
|---|---|
| `ssh -L 8080:localhost:80 user@host` | Local forward — reach remote port locally |
| `ssh -R 9090:localhost:3000 user@host` | Remote forward — expose local port on server |
| `ssh -D 1080 user@host` | Dynamic SOCKS5 proxy |
| `ssh -N -f -L 5432:db:5432 user@host` | Background tunnel, no shell (`-N -f`) |

## File transfer

| Command | Purpose |
|---|---|
| `scp file.txt user@host:~/` | Copy file to remote home dir |
| `scp -r ./dir user@host:~/` | Copy directory recursively |
| `rsync -avz ./dir user@host:~/dir` | Sync directory (preferred over scp) |
| `rsync -avz --delete ./dir user@host:~/dir` | Sync and delete removed files (destructive) |

## Run commands remotely

| Command | Purpose |
|---|---|
| `ssh user@host 'uptime'` | Run a single command, no shell |
| `ssh user@host 'bash -s' < script.sh` | Pipe a local script to remote bash |
| `ssh -t user@host 'sudo htop'` | Force TTY allocation (for interactive cmds) |

## Config & known_hosts

| Command | Purpose |
|---|---|
| `ssh -G work` | Show effective config for a Host alias |
| `ssh-keyscan -H host >> ~/.ssh/known_hosts` | Pre-trust a host's key |
| `ssh-keygen -R host` | Remove host from known_hosts |
