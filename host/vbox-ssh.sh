#!/bin/bash

sudo VBoxManage modifyvm "vm_minix" --natpf1 "guestssh,tcp,,2222,,22"
