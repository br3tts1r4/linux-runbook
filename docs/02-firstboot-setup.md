# Firstboot Setup

Setup the system after first boot.

## Install daily use packages

```sh
sudo pacman -S git tmux zsh nvim lshw htop gcc
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

Back: [OS Installation](./01-os-installation.md) | Next: [TTY Setup](./03-tty-setup.md)
