# Security

## Firewalld

### 1. Install Firewalld and NetworkManager integration

Install the core firewalld package along with `iptables-nft`; `firewall-config` is the GUI wrapper.

```sh
pacman -S firewalld iptables-nft firewall-config
```

### 2. Enable & start the service

Enable the service so it automatically starts on boot, and start it immediately:

```sh
sudo systemctl enable --now firewalld.service
```

### 3. Set default baseline zone

```sh
sudo firewall-cmd --set-default-zone=public
```

### 4. Allow outbound web browsing (HTTP/HTTPS) & limited SSH

```sh
sudo firewall-cmd --zone=public --add-service=http --permanent
sudo firewall-cmd --zone=public --add-service=https --permanent
sudo firewall-cmd --zone=public --add-rich-rule='rule family="ipv4" source address="192.168.1.0/24" service name="ssh" accept' --permanent
```

Reload for the permanent rules to take effect:

```sh
sudo firewall-cmd --reload
```

## AppArmor

### 1. Install AppArmor packages

Install `apparmor` along with `apparmor-utils`, which provides tools like `aa-status`, `aa-complain`, and `aa-enforce`.

```sh
sudo pacman -S apparmor apparmor-utils
```

### 2. Configure the bootloader

The Arch kernel has AppArmor compiled in, but you must instruct it to initialize at boot using the `lsm` parameter.

Open `/etc/default/grub` in an editor:

```sh
sudo vi /etc/default/grub
```

Find `GRUB_CMDLINE_LINUX_DEFAULT` and append `lsm=landlock,lockdown,yama,integrity,apparmor,bpf` to the existing parameters inside the quotes.

Regenerate the GRUB configuration:

```sh
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

---

Back: [GUI customisation](./06-gui-customisation.md)