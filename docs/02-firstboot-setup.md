# Firstboot Setup

Setup the system after first boot.

## (Optional | can skip) Check boot level
check boot level
 ```sh
 sudo systemctl get-default 
 ```
 set boot level
 ```sh
sudo systemctl set-default graphical.target
 ```
| Target | Legacy runlevel | Description |
|---|---|---|
| `multi-user.target` | 3 | Console, no GUI |
| `graphical.target` | 5 | GUI / display manager |
| `rescue.target` | 1 | Single user, minimal |

## Install daily use packages

Install pacakge from [Arch package file](../dotfiles/arch/pkgs.txt)

```sh
# Current explicitly-installed packages
pacman -Qqe > pkgs.txt

# Reinstall on a new machine
pacman -S --needed - < pkgs.txt
```

## Change shell to zsh (prerequisite zsh)

check shell location

```sh
pacman -Ql zsh | grep '/zsh$'
```

change shell

```sh
chsh -s /usr/bin/zsh      # user shell
sudo chsh -s /usr/bin/zsh # root shell
```

verify

```sh
grep "^$USER" /etc/passwd
```

## Create hushlogin file

```sh
touch ~/.hushlogin
```

## Show boot messages

By default GRUB hides kernel logs during boot. Toggle this in `/etc/default/grub` ([what is `/etc/default/`?](./reference/etc-default.md)):

```sh
sudo vim /etc/default/grub
```

Set `GRUB_CMDLINE_LINUX_DEFAULT` to one of:

| Behaviour             | Value                |
| --------------------- | -------------------- |
| Quiet boot (default)  | `"quiet loglevel=3"` |
| Show full boot status | `""`                 |

Regenerate the GRUB config to apply:

```sh
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

## Organise SSH directory
Setup SSH directory
```sh
mkdir -p ~/.ssh/keys
chmod 700 ~/.ssh
chmod 700 ~/.ssh/keys
touch ~/.ssh/config
chmod 600 ~/.ssh/config
```
Ideally for directory layout
| Path | Permission |
|---|---|
| `~/.ssh/` | `700` |
| `~/.ssh/config` | `600` |
| `~/.ssh/keys/*` (private) | `600` |
| `~/.ssh/keys/*.pub` | `644` |
| `~/.ssh/known_hosts` | `644` |
| `~/.ssh/authorized_keys` | `600` |

[SSH template configuration file](../scripts/ssh/config)
[SSH command cheatsheet](./reference/ssh-cmd.md)

---

## Sync dotfiles

Run from the `dotfiles/` directory in this repo.

**Create symlinks:**

```sh
stow --target="$HOME/.config" .
```

**Remove symlinks:**

```sh
stow --delete --target="$HOME/.config" .
```

After the initial sync, add a shell alias to re-run stow quickly:

```sh
alias dotsync="stow --target=$HOME/.config ."
```

If stow reports a `locale` error or warning, follow the next section.

---

## Set locale

Edit `/etc/locale.gen` and uncomment:

```text
en_US.UTF-8 UTF-8
```

Generate locales:

```sh
sudo locale-gen
```

Set system-wide default:

```sh
sudo localectl set-locale LANG=en_US.UTF-8
```

Verify:

```sh
locale -a
```

## Change zsh config
Create zsh config dir (If no directory)
```sh
sudo mkdir -p /etc/zsh
```

Edit `/etc/zsh/zshenv`
```text
export ZDOTDIR="$HOME/.config/zsh"
```
Verify:
```sh
source /etc/zsh/zshenv
echo $ZDOTDIR
```

---
Back: [OS Installation](./01-os-installation.md) | Next: [TTY Setup](./03-tty-setup.md)
