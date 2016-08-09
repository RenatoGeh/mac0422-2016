#!/bin/bash

sudo mount /dev/sda10 /media/storage
sudo VBoxManage startvm "vm_minix" --type headless
