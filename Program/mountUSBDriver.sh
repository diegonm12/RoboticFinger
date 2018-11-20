#!/bin/sh
sudo rmmod cdc_acm
sudo rmmod Driver/USBDriver.ko
sudo insmod Driver/USBDriver.ko
sudo chown -R diego /dev/RoboticFinger0




