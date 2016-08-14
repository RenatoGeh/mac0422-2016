#!/bin/bash

usr="$1"

if [[ -z "$1" ]]; then
  usr="renatolg"
fi

ssh -l $usr -p 2222 localhost
