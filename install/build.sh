#!/bin/bash

cd ./../php-src
git checkout php-7.2.10
./buildconf --force && ./configure --prefix=/home/etouraille/src/php/bin --enable-debug && make -j2 && make install
