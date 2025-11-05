#!/bin/bash

if [ -e "~/.bashrc" ]; then
echo "export HELLO=${HOSTNAME}" >> ~/.bashrc
echo "LOCAL=$(whoami)" >> ~/.bashrc
fi

gnome-terminal
