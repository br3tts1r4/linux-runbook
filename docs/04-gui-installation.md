# GUI Installation

## Install graphics drivers

### Intel

```sh
sudo pacman -S --needed mesa vulkan-intel intel-ucode
```

`intel-ucode` provides essential microcode security and stability patches from Intel.

### AMD

```sh
sudo pacman -S --needed mesa vulkan-radeon
```

### Nvidia

Check GPU generation, then install the matching driver package:

| Generation     | GPUs                                                     | Package                                           |
| -------------- | -------------------------------------------------------- | ------------------------------------------------- |
| Turing & newer | RTX 20/30/40/50-series, GTX 16-series                    | `nvidia-open-dkms`                                |
| Pascal & older | GTX 10-series (e.g. 1080, 1060), GTX 900-series, Titan X | `nvidia-dkms` (required — open modules will fail) |

**Pascal and older:**

```sh
sudo pacman -S --needed linux-headers nvidia-utils egl-wayland nvidia-dkms
```

**Turing and newer:**

```sh
sudo pacman -S --needed linux-headers nvidia-utils egl-wayland nvidia-open-dkms
```

| Package            | Purpose                                                                                |
| ------------------ | -------------------------------------------------------------------------------------- |
| `linux-headers`    | Kernel interface files needed to compile out-of-tree driver modules                    |
| `nvidia-utils`     | User-space libraries for 3D APIs (Vulkan, GLX, etc.)                                   |
| `egl-wayland`      | Bridges NVIDIA EGL to Wayland for modern compositors (Hyprland, Sway, GNOME)           |
| `nvidia-dkms`      | Closed-source kernel driver for Pascal and older GPUs; DKMS rebuilds on kernel updates |
| `nvidia-open-dkms` | Open-source kernel modules for Turing and newer GPUs; DKMS rebuilds on kernel updates  |

### Configure graphics driver (KMS)

Enable Early Kernel Mode Setting (KMS) so graphics drivers load during boot, before the display manager starts.

**Step 1** — open the initramfs configuration file:

```sh
sudo vim /etc/mkinitcpio.conf
```

**Step 2** — locate `MODULES=(...)` and add the module(s) for the installed GPU:

```txt
# Intel
MODULES=(i915)

# AMD
MODULES=(amdgpu)

# Nvidia
MODULES=(nvidia nvidia_modeset nvidia_uvm nvidia_drm)
```

**Step 3** — rebuild the initramfs:

```sh
sudo mkinitcpio -P
```

**Step 4** — mandatory for Nvidia: configure the driver for Wayland cooperation.

```sh
sudo vim /etc/modprobe.d/nvidia.conf
```

Set these options:

- `modeset=1` — enables kernel mode-setting so Wayland/Hyprland can control monitor resolution and refresh rate
- `fbdev=1` — creates a framebuffer device so the TTY displays at native resolution during boot

```txt
options nvidia_drm modeset=1 fbdev=1
```

Rebuild the initramfs:

```sh
sudo mkinitcpio -P
```

## Install GUI

### Install Hyprland (tiling window manager)

This guide uses [Hyprland](https://wiki.hypr.land/Getting-Started/).

```sh
sudo pacman -S --needed hyprland xdg-desktop-portal-hyprland
```

### Configure Hyprland environment

Add to `~/.config/hypr/hyprland.conf`:

```ini
#########################################
# UNIVERSAL WAYLAND TOOLKIT INTEGRATIONS #
#########################################

# Core Wayland Environment
env = XDG_SESSION_TYPE,wayland
env = XDG_CURRENT_DESKTOP,Hyprland
env = XDG_SESSION_DESKTOP,Hyprland

# Hardware Acceleration Pipelines
# Uncomment for Nvidia
# env = LIBVA_DRIVER_NAME,nvidia
# env = GBM_BACKEND,nvidia-drm
# env = __GLX_VENDOR_LIBRARY_NAME,nvidia

# Smooth UI Sync (Eliminates Toolkit Flickering)
env = ELECTRON_OZONE_PLATFORM_HINT,auto

# GTK Toolkit (GNOME apps, Firefox, etc.)
env = GDK_BACKEND,wayland,x11,*

# Qt Toolkit (KDE apps, VLC, OBS, etc.)
env = QT_QPA_PLATFORM,wayland;xcb
env = QT_QPA_PLATFORMTHEME,qt5ct # Change to qt6ct if using Qt6 components

# Electron / Chromium Apps (Discord, VS Code, Spotify)
env = ELECTRON_OZONE_PLATFORM_HINT,auto

# Clutter (Older GTK-adjacent graphics library)
env = CLUTTER_BACKEND,wayland
```

### Hyprland default keybindings

| Shortcut             | Action                                |
| -------------------- | ------------------------------------- |
| `Super + Q`          | Open terminal                         |
| `Super + R`          | Open the application menu launcher    |
| `Super + M`          | Exit Hyprland back to the TTY console |
| `Super + Arrow keys` | Move focus between windows            |

## Install GUI environment

### Audio

```sh
sudo pacman -S pipewire pipewire-pulse
```

### Auth prompt

Required for apps that request sudo elevation graphically.

```sh
sudo pacman -S hyprpolkitagent
```

### Notification

Handles on-screen system and app notifications.

```sh
# Control centre style (similar to macOS)
sudo pacman -S swaync
# Simple notification boxes
sudo pacman -S mako
```

### Status bar

```sh
sudo pacman -S waybar
```

## Install desktop applications

### Terminal emulator

```sh
sudo pacman -S kitty
```

### Copy & Paste

```sh
sudo pacman -S wl-clipboard
```

### Other

```sh
sudo pacman -S firefox obsidian
```

---

Back: [User software setup](./03-user-software-setup.md) | Next: [GUI customisation](./05-gui-customisation.md)
