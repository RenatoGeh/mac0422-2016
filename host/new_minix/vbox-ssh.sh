#!/bin/bash

sudo mount /dev/sda10 /media/storage
sudo VBoxManage modifyvm "vm_minix" --natpf1 "guestssh,tcp,,2222,,22"
sudo umount /media/storage
