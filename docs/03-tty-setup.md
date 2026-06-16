# TTY Setup

Configure the virtual TTY using one of two options:

- [GETTY](#getty) — built-in terminal (default)
- [KMSCON](#kmscon) — GPU-accelerated replacement

## KMSCON

[KMSCON](https://wiki.archlinux.org/title/KMSCON) (Kernel Mode Setting CONsole) replaces the built-in TTY. Features: UTF-8, KMS/DRM acceleration, 256 colours, adjustable font size.

### Install

```sh
sudo pacman -S kmscon
sudo pacman -S fontconfig
sudo pacman -S ttf-fira-code
```

### Configure

If `/usr/share/kmscon/kmscon.conf.example` exists, copy it as a starting point.

```sh
sudo mkdir -p /etc/kmscon
sudo vim /etc/kmscon/kmscon.conf
```

Essential settings:

```txt
font-name=Fira Code
font-size=18
xkb-layout=us
no-mouse

# GPU acceleration (recommended)
hwaccel
render-engine=gl
```

### Test on tty1

```sh
# Tune on tty1 first; move to tty2 once settings are correct
sudo systemctl restart kmsconvt@tty1.service
```

### Verify

```sh
sudo reboot
ps aux | grep kmscon
echo $TERM  # should be: xterm-256color
tput colors  # should return: 256
```

### Assign to tty2

Typical Arch TTY layout:

| TTY | Role |
|---|---|
| tty1 | Main login / display manager |
| tty2 | kmscon |
| tty3–6 | Spare getty terminals |
| tty7+ | Historically used by X11 |

Disable getty on tty1 (during kmscon testing on tty1):

```sh
sudo systemctl disable getty@tty1.service
```

Permanent layout — kmscon on tty2, getty on tty1 and tty3:

```sh
# Enable kmscon only on tty2
sudo systemctl enable kmsconvt@tty2.service

# Enable getty on tty1 and tty3; tty2 is reserved for kmscon
sudo systemctl enable getty@tty1.service
sudo systemctl enable getty@tty3.service
```

### Switch TTY

```sh
sudo chvt 1
sudo chvt 2
```

### Apply to all TTYs (optional, not recommended)

Replacing every TTY with kmscon risks losing shell access if kmscon fails.

```sh
sudo ln -s /usr/lib/systemd/system/kmsconvt@.service /etc/systemd/system/autovt@.service
```

Revert:

```sh
sudo rm -f /etc/systemd/system/autovt@.service
```

### How KMSCON renders

```txt
GPU hardware
  ↓
KMS/DRM  (kernel subsystem)
  ↓
kmscon  (draws directly to framebuffer)
  ↓
TTY screen
```

kmscon and Hyprland are separate KMS clients — they cannot share the same TTY session.

```txt
┌─────────────────┐    ┌──────────────────────┐
│  kmscon (TTY)   │    │  Hyprland/Sway/Xorg  │
│  on tty2        │    │  on tty1             │
└────────┬────────┘    └──────────┬───────────┘
         └──────────┬─────────────┘
                    ↓
              KMS / DRM
                    ↓
               GPU
```

Both need exclusive KMS access on their TTY — starting Hyprland inside kmscon will conflict:

```txt
# This cannot work:
kmscon (holds KMS on tty2)
    └── tries to start Hyprland  ← conflict: Hyprland also needs KMS
```

---

## GETTY

getty is the built-in terminal service on `/dev/ttyN`. Limited to 16 colours (8 + 8 bright).

```sh
# Check service
systemctl status getty@tty1.service
# Disable
sudo systemctl disable getty@tty1.service
# Enable
sudo systemctl enable getty@tty1.service
```

### List available fonts

```sh
# List all default available console fonts
ls /usr/share/kbd/consolefonts/
# List all Terminus variants specifically (if installed)
ls /usr/share/kbd/consolefonts/ | grep ter-
```

Default starting point: `ter-v24n` (size 24; `n` = normal, `b` = bold).

Fonts by display resolution:

| Font name | Dimension (grid) | Target display | Weight | Height (px) | Width (px) |
|---|---|---|---|---|---|
| `ter-v32b` | 32×16 | 4K / 5K (high density) | Bold | 32 | 16 |
| `ter-v32n` | 32×16 | 4K (thin styling) | Normal | 32 | 16 |
| `ter-v28b` / `ter-v28n` | 28×14 | 1440p / 4K compact | Bold / Normal | 28 | 14 |
| `ter-v24b` / `ter-v24n` | 24×12 | Full HD (laptop) / 1440p | Bold / Normal | 24 | 12 |
| `Lat2-Terminus` | 16×8 | Legacy display / low-res | Normal | 16 | 8 |
| `sun` | 12×22 | Full HD (retro layout) | Normal | 22 | 12 |
| `cybercafe` | 16×8 | Stylized setups | Normal | 16 | 8 |
| `ecca` | 16×8 | Matte glare resistance | Double-struck | 16 | 8 |

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

FONT=default
```

### Apply

```sh
sudo systemctl restart systemd-vconsole-setup.service
```

### Apply font at boot (optional)

[What is `/etc/mkinitcpio.conf`?](./reference/etc-mkinitcpio-conf.md)

```sh
sudo vim /etc/mkinitcpio.conf
```

Skip if `HOOKS` already includes `sd-vconsole` or `consolefont`.

In `HOOKS=(...)`, add `sd-vconsole` after `keyboard` (requires the `systemd` hook):

| Hook | Role |
|---|---|
| `consolefont` | Legacy — loads the TTY font via shell scripts during boot |
| `sd-vconsole` | Systemd — delegates font and keyboard layout to `systemd-vconsole-setup` |

```sh
# Example config
HOOKS=(systemd autodetect microcode modconf kms keyboard sd-vconsole block filesystems fsck)
```

Rebuild after editing:

```sh
sudo mkinitcpio -P
```

---

Back: [Firstboot setup](./02-firstboot-setup.md) | Next: [Prompt setup](./04-prompt-setup.md)
