# Firstboot Setup

Setup the system after first boot.

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

## Change TTY after boot (optional | can skip | back after done tty setup)

Show the configuration of replacing default TTY1.
Ideally, it need to change the `systemd` service for `getty.target` to point to `kmscon@tty2`(prerequisite KMSCON) instead `getty@tty1`(default).

### Change TTY1 to TTY2

Create autologin init by copying the template from [autologin.conf](../scripts/systemd/autologin.conf)

```sh
sudo mkdir -p /etc/systemd/system/kmsconvt@tty2.service.d/
sudo vim /etc/systemd/system/kmsconvt@tty2.service.d/autologin.conf
```

Memory Reload

```sh
sudo systemctl daemon-reload
```

### Change back to TTY1 (optional)

Remove autologin init

```sh
sudo rm -r /etc/systemd/system/kmsconvt@tty2.service.d/
```

Manage getty serivce

```sh
# sudo systemctl disable kmsconvt@tty2.service # Skip this if dont want to disable tty2
sudo systemctl unmask getty@tty1.service
sudo systemctl enable getty@tty1.service
```

Memory Reload

```sh
sudo systemctl daemon-reload
```

Back: [OS Installation](./01-os-installation.md) | Next: [TTY Setup](./03-tty-setup.md)
