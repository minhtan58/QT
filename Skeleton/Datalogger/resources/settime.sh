#!/bin/bash
sudo timedatectl set-ntp false
sudo timedatectl set-time '$1-$2-$3 $4:$5'