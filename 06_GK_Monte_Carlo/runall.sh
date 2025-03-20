#!/bin/bash
for z in 0.05, 0.125, 0.25, 1.15, 1.5; do
    # run all z in parallel
    ./gcmc $z & 
    sleep 1
done