# CarND-PID-Control-Project
Self-Driving Car Engineer Nanodegree Program

---
## Overview

In this C++ project, I implemented a Proportional-Integral-Derivative Controller(PID) in order to drive a simulated car around a virtual track. In order keep car on track, first I mannually tune P,I,D parameters to (0.03,0.004,0.5),and then I use twiddle to find better through about 100 rounds running. Also, I use fomula `(1- |steer_value|)*0.3+0.2` to give a throttle value.

## Basic Build Instructions

1. Clone this repo.
2. Compile: `cmake . && make`
3. Run it: `./pid`. 

## Project Instructions and Rubric




