# (NOT STABLE) Systemd change default TTY
## Change TTY after boot (prerequisite KMSCON)

Show the configuration of replacing default TTY1.
Ideally, it need to change the `systemd` service for `getty.target` to point to `kmscon@tty2`(prerequisite KMSCON) instead `getty@tty1`(default).

### Change TTY1 to TTY2

Create autologin init by copying the template from [autologin.conf](../../scripts/systemd/autologin.conf)

```sh
sudo mkdir -p /etc/systemd/system/kmsconvt@tty2.service.d/
sudo vim /etc/systemd/system/kmsconvt@tty2.service.d/autologin.conf
```
Disable block tty1 for making tty2 start as default
```sh
sudo systemctl disable getty@tty1.service
sudo systemctl mask getty@tty1.service
```
Memory Reload

```sh
sudo systemctl daemon-reload
sudo systemctl restart kmsconvt@tty2.service
```

### Change back to TTY1 (optional)

Remove autologin init

```sh
sudo rm -r /etc/systemd/system/kmsconvt@tty2.service.d/
```

Manage getty serivce

```sh
# sudo systemctl disable kmsconvt@tty2.service # Skip this if dont want to disable tty2
sudo systemctl unmask getty@tty1.service
sudo systemctl enable getty@tty1.service
```

Memory Reload

```sh
sudo systemctl daemon-reload
```
