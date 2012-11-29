#!/bin/sh

autoreconf --install -v

cd leveldb-1.7.0
./build_detect_platform build_config.mk ./
cd -

automake -v --add-missing --copy >/dev/null 2>&1
