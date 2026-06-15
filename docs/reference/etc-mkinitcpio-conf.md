# `/etc/mkinitcpio.conf`

**mkinitcpio** (Make Initial RAM disk CPIO) builds the `initramfs` — a temporary root filesystem loaded into memory at boot.

## Why it exists

At boot, the flow is: firmware → bootloader → kernel. The kernel alone may not yet access the real root disk — common when the setup includes:

- LUKS (full-disk encryption)
- LVM
- RAID
- Btrfs

mkinitcpio packs the drivers, scripts, and binaries needed to find, unlock, and mount the real root partition into a small initramfs image. Once the real root is mounted, control passes to the full system.

```text
bootloader  →  kernel + initramfs  →  mount real root  →  switch to full OS
```

## Configuration file

`/etc/mkinitcpio.conf` defines what goes into the initramfs. Key settings are Bash arrays:

| Array | Purpose |
|---|---|
| `MODULES=(...)` | Kernel modules loaded early — e.g. `amdgpu`, `i915`, or `nvidia_drm` for KMS to avoid flicker or blank screens at boot |
| `BINARIES=(...)` | Extra executables copied into the initramfs — usually left empty |
| `FILES=(...)` | Extra files included in the image — e.g. a LUKS key file for unattended decryption |
| `HOOKS=(...)` | Build scripts run in order (left to right) that add boot features — encryption, LVM, filesystem support, etc. The most important array |

After editing, rebuild the initramfs:

```sh
sudo mkinitcpio -P
```

---
