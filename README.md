# linux-runbook

This repo is an Arch Linux-focused reference manual covering installation commands, partitioning, dotfiles, and post-install setup, pairing documentation with tracked dotfiles. Steps may not work on other distros.

![linux-runbook](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExejY4YWcweGNyMnN1b3dkY2ZubWUxNWoxcXZvbjNnazB0ZzNjamluNyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/jQQRWxSlW1tWvWigA9/giphy.gif)

---

## Index

### Runbooks

Follow in order from USB prep through desktop setup.

| Step | Guide | Topic |
|:---:|---|---|
| 00 | [Installer preparation](docs/00-installer-preparation.md) | Download ISO, flash USB |
| 01 | [OS installation](docs/01-os-installation.md) | Partition, pacstrap, chroot, GRUB |
| 02 | [Firstboot setup](docs/02-firstboot-setup.md) | Packages, GRUB boot messages |
| 03 | [TTY setup](docs/03-tty-setup.md) | GETTY or KMSCON, console fonts |
| 04 | [Prompt setup](docs/04-prompt-setup.md) | Shell prompt and tooling |
| 05 | [GUI setup](docs/05-gui-setup.md) | Drivers, Hyprland, desktop packages |
| 06 | [GUI customisation](docs/06-gui-customisation.md) | Themes and appearance |

### Reference

Background notes linked from the runbooks.

| Guide | Topic |
|---|---|
| [`/etc/default/`](docs/reference/etc-default.md) | System default overrides |
| [`mkinitcpio.conf`](docs/reference/etc-mkinitcpio-conf.md) | Initramfs configuration |
| [Pacman](docs/reference/pacman-cheatsheet.md) | Package manager commands |

### Dotfiles

Tracked configs deployed with GNU Stow.

| Path | Contents |
|---|---|
| [arch/pkgs.txt](dotfiles/arch/pkgs.txt) | Base package list |
| [tmux/](dotfiles/tmux/tmux.conf) | `tmux.conf` |
| [zsh/](dotfiles/zsh/.zshrc) | `.zshrc`, `.zshenv`, `.zprofile` |

### Scripts

| Script | Purpose |
|---|---|
| `bootstrap.sh` | Symlink dotfiles and install packages |
| `backup.sh` | Sync live changes back into the repo |
