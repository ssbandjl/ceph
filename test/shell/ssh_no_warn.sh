#!/bin/bash

set -e


sed -i '/LogLevel/d' ~/.ssh/config
echo "LogLevel quiet" >> ~/.ssh/config
cat ~/.ssh/config|grep LogLevel
