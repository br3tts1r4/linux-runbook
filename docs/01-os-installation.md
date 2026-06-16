# OS Installation

After booting into the Arch installer shell on the target machine.

## Partition the disk

```sh
fdisk -l                    # list available disks
cfdisk /dev/nvme0n1         # example for an M.2 NVMe disk
```

In `cfdisk`, create two partitions:
- Bootloader: ~1G, type **EFI System**
- Linux: rest of disk, type **Linux filesystem**

## Format partitions

```sh
mkfs.vfat -F 32 /dev/nvme0n1p1   # bootloader
mkfs.ext4 /dev/nvme0n1p2         # linux root
```

## Mount partitions

Mount the new partitions onto the installer.

```sh
mount /dev/nvme0n1p2 /mnt
mount /dev/nvme0n1p1 /mnt/boot
```

## Install core packages
[`pacstrap`](./reference/pacman-cheatsheet.md) installs the following into the mounted target: Base system, Linux kernel, Firmware, Editor, Network tools.

```sh
pacstrap -K /mnt base linux linux-firmware vim networkmanager
```

**Skip if no error** — if you hit `Error failed to install package to new root`, the installer's package-signing keys are outdated. Refresh them and retry:

```sh
pacman -Sy archlinux-keyring
rm -rf /mnt/var/lib/pacman/sync/*   # clear cache
```

Generate the filesystem table:

```sh
genfstab -U /mnt >> /mnt/etc/fstab
```

## Configure the new system

Chroot into the install:

```sh
arch-chroot /mnt
```

Set timezone and hardware clock:

```sh
ln -sf /usr/share/zoneinfo/Region/City /etc/localtime   # replace Region/City
hwclock --systohc
```

Configure localisation:

```sh
vim /etc/locale.gen                  # uncomment your locale, e.g. en_US.UTF-8
locale-gen
echo "LANG=en_US.UTF-8" > /etc/locale.conf
```

Set hostname and enable networking:

```sh
echo "your-hostname" > /etc/hostname
systemctl enable NetworkManager
```

Install sudo and grant the wheel group access:

```sh
pacman -S sudo
EDITOR=vim visudo                    # uncomment: %wheel ALL=(ALL:ALL) ALL
```

Set passwords and create your user:

```sh
passwd                               # root password
useradd -m -G wheel user             # replace `user` with your username
passwd user
```

## Install bootloader

Still inside `arch-chroot`:

```sh
pacman -S grub efibootmgr
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB
```

## Exit and reboot

```sh
exit
umount -R /mnt
reboot
```

---
Back: [Installer preparation](./00-installer-preparation.md) | Next: [Firstboot setup](./02-firstboot-setup.md)
