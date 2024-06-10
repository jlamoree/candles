#!/usr/bin/env bash

programmer=avrisp2
chip=t25

script_dir="$(dirname "$(readlink -f "$0")")"
cd "${script_dir}/flash"

for mem in calibration eeprom efuse flash hfuse lfuse; do
  avrdude -c $programmer -p $chip -U ${mem}:w:${mem}.hex:i
done

