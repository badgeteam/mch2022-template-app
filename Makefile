PORT ?= /dev/ttyACM0
BUILDDIR ?= build
IDF_PATH ?= $(shell pwd)/esp-idf
IDF_EXPORT_QUIET ?= 0
SHELL := /usr/bin/env bash

.PHONY: prepare clean build flash monitor menuconfig

all: build install

prepare:
	git submodule update --init --recursive
	rm -rf "$(IDF_PATH)"
	git clone --recursive --branch v4.4.4 https://github.com/espressif/esp-idf.git
	cd "$(IDF_PATH)"; bash install.sh

clean:
	rm -rf "$(BUILDDIR)"

fullclean:
	source "$(IDF_PATH)/export.sh" && idf.py fullclean

build:
	source "$(IDF_PATH)/export.sh" && idf.py build

install: build
	python3 tools/app_push.py build/main.bin "template_app" "Template App" 1 --run

monitor:
	source "$(IDF_PATH)/export.sh" && idf.py monitor -p $(PORT)

menuconfig:
	source "$(IDF_PATH)/export.sh" && idf.py menuconfig
