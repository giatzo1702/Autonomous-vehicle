# Autonomous-vehicle
Development of a simple autonomous vehicle using Arduino

The basic idea

The autonomous rc car (1:12 scale) starts from a specific point and autonomously navigates itself to reach the target point, by avoiding static obstacles. A* algorithm was used for the optimal path design.

Because of memory issues, the A* algorithm could not be executed in Arduino to produce the directions for the optimal path. Thus, the A* algorithm was compiled and executed in a linux environment and the results were manually passed into the arduino code.

The project consists of two folders. 

  -- The "astar" folder containing the implementation of A* algorithm in C programming language.
  
  -- The "arduino" folder containing the Arduino code and an auxiliary library.

In the following image, the autonomous vehicle is presented.

![the vehicle](https://cloud.githubusercontent.com/assets/13044530/11782519/23517878-a27a-11e5-8563-4e7fd03df50d.jpg)



The following image depicts the visual map that is handled by the vehicle.

![static map](https://cloud.githubusercontent.com/assets/13044530/11788495/0573a57c-a29a-11e5-9a15-632a15a64fd6.png)



The results from the A* algorithm for given start and target points. The weight of each point is presented in the map.

![a star algorithm](https://cloud.githubusercontent.com/assets/13044530/11788499/09d693a4-a29a-11e5-8e2b-cca34e4ef0ae.png)


Demonstration video link:

https://www.youtube.com/watch?v=aSWnoYFdYM8
