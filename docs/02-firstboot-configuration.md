# System Config

Configure the base system after first boot.

## Show boot messages (optional)

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

## Set TTY font size (optional)

### List available fonts

```sh
# List all default available console fonts
ls /usr/share/kbd/consolefonts/
# List all Terminus variants specifically (if installed)
ls /usr/share/kbd/consolefonts/ | grep ter-
```

Default starting point: `ter-v24n` (size 24; `n` = normal, `b` = bold).

Fonts by display resolution:

| Font name               | Dimension (grid) | Target display           | Weight        | Height (px) | Width (px) |
| ----------------------- | ---------------- | ------------------------ | ------------- | ----------- | ---------- |
| `ter-v32b`              | 32×16            | 4K / 5K (high density)   | Bold          | 32          | 16         |
| `ter-v32n`              | 32×16            | 4K (thin styling)        | Normal        | 32          | 16         |
| `ter-v28b` / `ter-v28n` | 28×14            | 1440p / 4K compact       | Bold / Normal | 28          | 14         |
| `ter-v24b` / `ter-v24n` | 24×12            | Full HD (laptop) / 1440p | Bold / Normal | 24          | 12         |
| `Lat2-Terminus`         | 16×8             | Legacy display / low-res | Normal        | 16          | 8          |
| `sun`                   | 12×22            | Full HD (retro layout)   | Normal        | 22          | 12         |
| `cybercafe`             | 16×8             | Stylized setups          | Normal        | 16          | 8          |
| `ecca`                  | 16×8             | Matte glare resistance   | Double-struck | 16          | 8          |

### Install Terminus (if not present)

```sh
sudo pacman -S terminus-font
```

### Set font

```sh
sudo vim /etc/vconsole.conf
```

```txt
FONT=ter-v24n
```

### Apply

```sh
sudo systemctl restart systemd-vconsole-setup.service
```

### Apply font at boot (optional but recommended)
[what is `/etc/mkinitcpio.conf` ?](./reference/etc-mkinitcpio-conf.md)
```sh
sudo vim /etc/mkinitcpio.conf
```
Skip this step if `HOOKS` already includes `sd-vconsole` or `consolefont`.

In `HOOKS=(...)`, add `sd-vconsole` after `keyboard` (requires the `systemd` hook):

| Hook | Role |
|---|---|
| `consolefont` | Legacy — loads the TTY font via shell scripts during boot |
| `sd-vconsole` | Systemd — delegates font and keyboard layout to `systemd-vconsole-setup` |

```sh
# Example config
HOOKS=(systemd autodetect microcode modconf kms keyboard sd-vconsole block filesystems fsck)
                                                   |          |
                                             (1st: Input) -> (2nd: Font)
```

Rebuild after editing:

```sh
sudo mkinitcpio -P
```

---

Back: [OS Installation](./01-os-installation.md) | Next: [User software setup](./03-user-software-setup.md)
