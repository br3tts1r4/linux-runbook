# System Config

Configure the base system after first boot.

## Show boot messages (optional)

By default GRUB hides kernel logs during boot. Toggle this in `/etc/default/grub` ([what is `/etc/default/`?](./reference/etc-default.md)):

```sh
sudo vim /etc/default/grub
```

Set `GRUB_CMDLINE_LINUX_DEFAULT` to one of:

| Behaviour | Value |
|---|---|
| Quiet boot (default) | `"quiet loglevel=3"` |
| Show full boot status | `""` |

Regenerate the GRUB config to apply:

```sh
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

---

Back: [OS Installation](./01-os-installation.md)