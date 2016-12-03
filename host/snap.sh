#!/bin/bash

if [ -z "$1" ]; then
  echo "Requires snapshot name."
  exit 1
fi

sudo VBoxManage snapshot "vm_minix" take $1
