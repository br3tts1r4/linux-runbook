# `/etc/default/`

A centralised "control panel" of plain-text files that override the defaults of core system tools — GRUB, `useradd`, `locale`, network services, etc. You don't edit the system scripts themselves; they read these files at startup and apply your overrides:

```text
[system binary]  →  reads /etc/default/<name>  →  applies overrides  →  starts up
```

## Common files

| File | Controls |
|---|---|
| `grub` | Boot screen, kernel arguments (e.g. `quiet`), resolution, timeout |
| `useradd` | Defaults for new accounts (shell, home dir, skel) |
| `locale` | System-wide language, time format, keyboard layout |
| `nss` / `nsswitch` | Hostname and network-name resolution order |

---

Back: [System Config](../02-system-config.md)
