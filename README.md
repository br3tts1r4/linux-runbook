# linux-runbook
This repo is an Arch Linux-focused reference manual covering installation commands, partitioning, dotfiles, and post-install setup, pairing documentation with actual config templates. Steps may not work on other distros.

---

## 📂 Repository Architecture
Guides, config templates, and deployment scripts are kept separate.
- **`docs/`** — step-by-step runbooks
  - [00-preparation.md](docs/00-preparation.md)
  - [01-os-installation.md](docs/01-os-installation.md)
  - [02-system-config.md](docs/02-system-config.md)
  - **`reference/`** — background concepts referenced by the runbooks
    - [etc-default.md](docs/reference/etc-default.md)
- **`configs/`** — config templates (mirror system paths)
  - `neovim/`
  - `tmux/`
  - `zsh/`
- **`scripts/`** — deployment helpers
  - `bootstrap.sh`
  - `backup.sh`
