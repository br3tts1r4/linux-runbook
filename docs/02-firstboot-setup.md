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

## Hype pacakage (optional)

```sh
sudo pacman -S fastfetch
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
```sh
sudo mkdir -p /etc/systemd/system/kmsconvt@tty2.service.d/
sudo vim /etc/systemd/system/kmsconvt@tty2.service.d/autologin.conf
```
Example of init file
```ini
[Service]
# Clear the inherited ExecStart before setting our own
ExecStart=

# Launch kmscon on this TTY with autologin via agetty
ExecStart=-/usr/bin/kmscon \
    --vt=%I \          # bind to the TTY passed by systemd (e.g. tty2)
    --seats=seat0 \    # target the default seat
    --no-switchvt \    # don't auto-switch to this VT on start
    --font-name "Fira Code" \
    --font-size 12 \
    --term xterm-256color \
    -- /sbin/agetty \      # hand off to agetty for login handling
        --autologin brett \ # skip password prompt for this user
        --noclear %I \      # don't clear screen before login
        $TERM
```

Back: [OS Installation](./01-os-installation.md) | Next: [TTY Setup](./03-tty-setup.md)
