# linux-runbook

This repo is an Arch Linux-focused reference manual covering installation commands, partitioning, dotfiles, and post-install setup, pairing documentation with actual config templates. Steps may not work on other distros.

![linux-runbook](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExejY4YWcweGNyMnN1b3dkY2ZubWUxNWoxcXZvbjNnazB0ZzNjamluNyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/jQQRWxSlW1tWvWigA9/giphy.gif)

---

## 📂 Repository Architecture

Guides, config templates, and deployment scripts are kept separate.

- **`docs/`** — step-by-step runbooks
  - [00-installer-preparation.md](docs/00-installer-preparation.md)
  - [01-os-installation.md](docs/01-os-installation.md)
  - [02-firstboot-setup.md](docs/02-firstboot-setup.md)
  - [03-tty-setup.md](docs/03-tty-setup.md)
  - [04-prompt-setup.md](docs/04-prompt-setup.md)
  - [05-gui-setup.md](docs/05-gui-setup.md)
  - [06-gui-customisation.md](docs/06-gui-customisation.md)
  - **`reference/`** — background concepts referenced by the runbooks
    - [etc-default.md](docs/reference/etc-default.md)
    - [etc-mkinitcpio-conf.md](docs/reference/etc-mkinitcpio-conf.md)
    - [pacman-cheatsheet.md](docs/reference/pacman-cheatsheet.md)
- **`configs/`** — config templates (mirror system paths)
  - `neovim/`
  - `tmux/`
  - `zsh/`
- **`scripts/`** — deployment helpers
  - `bootstrap.sh`
  - `backup.sh`
