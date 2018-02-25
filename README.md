# CarND-PID-Control-Project
Self-Driving Car Engineer Nanodegree Program

---
## Overview

In this C++ project, I implemented a Proportional-Integral-Derivative Controller(PID) in order to drive a simulated car around a virtual track. In order keep car on track, first I mannually tune P,I,D parameters to (0.03,0.004,0.5),and then I use twiddle to find better through about 100 rounds running. Also, I use fomula `(1- |steer_value|)*0.3+0.2` to give a throttle value.

## Basic Build Instructions

1. Clone this repo.
2. Compile: `cmake . && make`
3. Run it: `./pid`. 

## Components of PID

Knowning the knowledge of each part of "PID" is very important:
### P:
The "P" for proportional means that the car will steer in proportion to the cross-track error, or CTE. 

### I:
The "I" for integral sums up all CTEs up to that point, such that too many negative CTEs (in this case, meaning the car has been to the left of the middle of the lane for awhile) will drive up this value, causing the car to turn back toward the middle, preventing the car from driving on one side of the lane the whole time.

### D:
The "D" for derivate is the change in CTE from one value to the next. This means that 1) if the derivative is quickly changing, the car will correct itself (i.e. higher steering angle) faster, such as in the case of a curve, and 2) if the car is moving outward from the middle, this will cause the steering to get larger (as the derivative sign will match the proportional sign), but if the car is moving toward the center (meaning the derivative value will be negative), the car's steering angle will get smoothed out, leading to a more smoother driving experience. 

## Mannual tune P.I.D parameters
In order to speed up,I use  fomula `(1- |steer_value|)*0.3+0.2` to set throttole, which means when CTE is high,the throttle will be changed to small to slow down car's speed.I test P.I.D parameters tuning via the following steps:
`
  //pid_steer.Init(0.1,0.0001,1.0); //40mph  throttle=0.3
  //pid_steer.Init(0.1,0.0001,2.0); //33mph
  //pid_steer.Init(0.1,0.001,2.0);
  //pid_steer.Init(0.1,0.0001,0.1);
  //pid_steer.Init(0.01,0.0005,1.0);
  //pid_steer.Init(0.01,0.001,2.0);
  //pid_steer.Init(0.1,0.001,1.0);
  //pid_steer.Init(0.1,0.00005,0.8); //43mph  throttle=0.5
  //pid_steer.Init(0.1,0.00005,3.0); //28mph  throttle=0.5
  //pid_steer.Init(0.05,0.00005,3.0); //33mph  throttle=0.5
  //pid_steer.Init(0.05,0.00005,0.5); //43mph smoothly,  throttle = (1- fabs(steer_value))*0.3+0.1;
  //pid_steer.Init(0.04,0.0004,0.4); //50mph smoothly,big turn failed,  throttle = (1- fabs(steer_value))*0.3+0.2;
  //pid_steer.Init(0.04,0.003,0.4); //53mph smoothly,big turn success, occasionly failed, throttle = (1- fabs(steer_value))*0.3+0.2;
  pid_steer.Init(0.03,0.004,0.5); //55mph smoothly,big turn success,robust ,throttle = (1- fabs(steer_value))*0.3+0.2;
`
and found (Kp,Ki,Kd) (0.03,0.004,0.5) with `throttle = (1- fabs(steer_value))*0.3+0.2` setting making car running smoothly and robust.

## Tuning P.I.D parameters via twiddle
Because my  starting parameters point (0.03,0.004,0.5) is small, so I set `dp = {0.01*Kp,0.01*Kd,0.01*Ki}` for twiddle to update PID parameters. But I found that the twiddle may found the local optimized PID parameters.  

## Rubic
### The PID procedure follows what was taught in the lessons.
Yes,my project include basic PID controler and parameters' mannual tuning and twiddle tuning.

### Describe the effect each of the P, I, D components had in your implementation.
My final setting PID demo video is here: ![Alt text](https://github.com/wuqianliang/CarND-PID-Control-Project/blob/master/final.mp4 "here")
### Describe how the final hyperparameters were chosen.

First I mannual tune to get a (0.03,0.004,0.5), then I run several time via the following loop :
1. twiddle tuning
2. set tuned parameters into  initial param for the next twiddle tune
and get a final parameer: (0.028215, 0.0042378, 0.4545)

The twiddle tuning step:

P: 0.0297, I: 0.004036, D: 0.505

P: 0.0294327, I: 0.00406869, D: 0.504546

P: 0.028215, I: 0.0042378, D: 0.4545
