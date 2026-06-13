# Preparation OS Installer

Download the ISO from https://archlinux.org/download/ and verify it before flashing.

```sh
sha256sum archlinux-x86_64.iso          # compare with sha256sums.txt
gpg --keyserver-options auto-key-retrieve --verify archlinux-x86_64.iso.sig
```

Identify the USB, wipe old signatures, then flash. No format step — `dd` writes the raw ISO over the whole disk.

**Linux** (example: `/dev/sdz`)

```sh
lsblk
sudo wipefs -a /dev/sdz
sudo dd bs=4M if=path/to/arch.iso of=/dev/sdz status=progress oflag=sync
```

**macOS** (example: `/dev/disk9`; use `rdisk` for speed; press `Ctrl+T` for progress)

```sh
diskutil list
diskutil unmountDisk /dev/disk9
sudo dd bs=4m if=path/to/arch.iso of=/dev/rdisk9
sync && diskutil eject /dev/disk9 # sync tells the kernel to flush all pending writes from RAM  cache to actual disk 
```

`dd` breakdown:

| Flag | Purpose |
|------|---------|
| `if=` | Input ISO path |
| `of=` | Target USB device (verify before running) |
| `bs=4M` | Block size; faster transfer |
| `status=progress` | Progress bar (GNU `dd` only) |
| `oflag=sync` | Flush cache before exit (Linux only) |

---

Next: [OS Installation](./01-os-installation.md)
