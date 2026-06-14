# Pacman

- **`pacman`** — package manager for a running Arch system; installs, updates, and removes packages into the live root (`/`).
- **`pacstrap`** — installer helper used from the live ISO; bootstraps packages into a mounted target (e.g. `/mnt`) before the system exists.

## Flag structure

Uppercase letters select the operation; lowercase letters modify it.

| Command | Action | Use | Notes |
|---|---|---|---|
| `sudo pacman -Syu` | Sync & upgrade | Refresh repos and upgrade all out-of-date packages | Avoid `pacman -Sy` alone before install — partial upgrades can break dependencies |
| `sudo pacman -S <pkg>` | Install | Install from official repos | Add `--needed` to skip packages already up to date |
| `sudo pacman -Rns <pkg>` | Clean remove | Remove package, unused deps, and global config files | Prefer over bare `-R`, which leaves config behind |

---

## Local database (`-Q`)

Queries the local package database (installed packages).

**Package metadata** — size, install date, explicit vs dependency:

```sh
pacman -Qi <package_name>
```

**File ownership** — which package owns a path:

```sh
pacman -Qo /path/to/file
```

**Installed files** — all files from a package:

```sh
pacman -Ql <package_name>
```

**Local search** — filter installed packages by keyword:

```sh
pacman -Qs <keyword>
```

---

## Remote mirrors (`-S`)

Queries configured remote repositories (available packages).

**Remote search** — names and descriptions by keyword:

```sh
pacman -Ss <keyword>
```

**Remote info** — dependencies and requirements before install:

```sh
pacman -Si <package_name>
```

**Group contents** — packages in a meta-group (e.g. `gnome`, `plasma`, `base-devel`):

```sh
pacman -Sg <group_name>
```

---

## Backup and restore

When migrating or replicating a system, export official and AUR packages separately to avoid broken dependency chains.

**Export native packages (official repos):**

```sh
pacman -Qqen > native_packages.txt
```

**Export foreign packages (AUR):**

```sh
pacman -Qqem > aur_packages.txt
```

**Restore native packages:**

```sh
sudo pacman -S --needed - < native_packages.txt
```

**Restore AUR packages** (via AUR helper such as `yay` or `paru`):

```sh
yay -S --needed - < aur_packages.txt
```

---

## System maintenance

Arch does not auto-clean package clutter; manual maintenance keeps root partition usage in check.

### Orphaned packages

Orphans are dependencies left behind after their parent package was removed.

**List orphans:**

```sh
pacman -Qdt
```

**Remove all orphans and their configs:**

```sh
sudo pacman -Rns $(pacman -Qdtq)
```

### Package cache

Downloaded tarballs are kept in `/var/cache/pacman/pkg/` by default. Nothing is deleted automatically — useful for rollbacks, but storage grows over time.

**Trim cache (recommended)** — keep current and previous versions of installed packages; remove uninstalled caches. Requires `pacman-contrib`:

```sh
sudo paccache -r
```

**Clear entire cache** — use only when storage is critically low:

```sh
sudo pacman -Scc
```

---

## Local rollback

If an upgrade breaks a component, downgrade from the local cache without network access:

```sh
sudo pacman -U /var/cache/pacman/pkg/package_name-version.pkg.tar.zst
```
