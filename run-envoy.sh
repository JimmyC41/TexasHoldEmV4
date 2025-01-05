#!/bin/bash
cd web-client
npx webpack
envoy -c envoy.yaml
