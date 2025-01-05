#!/bin/bash
cd ../web-client
npx webpack serve
envoy -c envoy.yaml
