## General info
This project is a simple Win32 application that implements the first map of Super Mario Bros 3.
It was the final project for course Windows Programming
	
## Technologies
Project is created with:
* Win32 API
* C++

## Video Demonstration

Mario eliminates enemies by jumping on top of them.
The turtle can roll sideways if jumped on twice and eliminate enemies such as other goombas and turtles for Mario

https://user-images.githubusercontent.com/106106584/219587838-6a40e580-6bcd-4e6c-8cba-1e4c3f04c429.mp4

Mario dies when he collides sideways with an enemy.

https://user-images.githubusercontent.com/106106584/219587852-6a1209c4-ba98-435f-9543-12dfe3f10e5f.mp4

When Mario is not on the initial ground the camera follows Mario(centers on Mario).
Why? So if there are any projectiles or enemies coming from underneath Mario he can dodge them.
What constitutes initial ground? A ground under which there's no possibility of a sneak attack be it with a fireball or flying goomba.

https://user-images.githubusercontent.com/106106584/219587874-e2169f7d-f41e-4917-9a80-6f26dae16a97.mp4

Flower enemy shoots fireballs at Mario in 1 of 4 possible quadrants that is unless Mario is hiding nearby the flower enemies pipe in which case the flower enemy waits for Mario to come out of hiding

https://user-images.githubusercontent.com/106106584/219591211-69cbc210-4805-4067-9f6b-7ab3ed6e59f3.mp4

If Mario hits the question box from underneath while in the process of jumping upwards the player receives a coin and the question box becomes empty if that was it's only coin

https://user-images.githubusercontent.com/106106584/219591822-fc1a9af9-1f6d-4181-b36b-fe0c5d2d3383.mp4

