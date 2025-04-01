#!/bin/bash

while [ ! -f /logs/tests.log ]; do
    sleep 1
done

cp /logs/tests.log /usr/share/nginx/html/index.html

nginx -g 'daemon off;'