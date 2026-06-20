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

---

Back: [OS Installation](./01-os-installation.md) | Next: [TTY Setup](./03-tty-setup.md)
