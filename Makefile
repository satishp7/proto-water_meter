# Author: Satish Patel
# Copyright (C) 2019-2020 HiveBriq Software Consultancy
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#/

LIBS = PubSubClient 
BOARD_FQBN = esp8266:esp8266:nodemcuv2

.PHONY: default clean

default: build

build: libdep
	arduino-cli compile --fqbn $(BOARD_FQBN) $(PWD)

# check if arudio-cli is available
config:
	arduino-cli	version || (echo Make sure dir containing \'arduino-cli\' available under \"PATH\" env && exit 1)

# check in libraries are present, if not create softlink for the same
libdep:
	for lib in $(LIBS) ; do \
		ls -l ~/Arduino/libraries/$$lib || \
		ln -s $(PWD)/libs/$$lib ~/Arduino/libraries/$$lib ; \
		ls -l ~/Arduino/libraries/$$lib || exit 1 ;\
	done

clean:
	rm *.bin 
	rm *.elf
