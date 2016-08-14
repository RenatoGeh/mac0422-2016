#!/bin/bash

sudo VBoxManage controlvm "vm_minix" poweroff
/bin/sleep 5
sudo umount /media/storage
