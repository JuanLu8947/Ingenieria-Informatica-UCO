#!/bin/bash

d=FicherosEjercicio3/home

users=(eva isa jose javi maria victor)

for u in ${users[@]}
do
    mkdir -p $d/$u/.ssh
    cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 128 > $d/$u/.ssh/id_rsa

    mkdir -p $d/$u/Desktop
    touch $d/$u/$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 10)
    touch $d/$u/$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 10)
    touch $d/$u/$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 10)
    touch $d/$u/Desktop/$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 10)
    touch $d/$u/Desktop/$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 10)
    touch $d/$u/Desktop/$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 10)

    chmod 774 $d/$u
    chmod 774 $d/$u/.ssh
    chmod 774 $d/$u/.ssh/id_rsa
    chmod 774 $d/$u/Desktop
done

chmod 600 $d/isa/.ssh/id_rsa
chmod 600 $d/jose/.ssh/id_rsa
chmod 700 $d/maria
chmod 700 $d/victor/.ssh