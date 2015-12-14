# Autonomous-vehicle
Development of a simple autonomous car using arduino

The basic idea of the project was the building and the programming of a scale 1:12 rc car that starts from a specific point of a map and tries to autonomously reach the target point by avoiding obstacles. The static map of the environment is saved in car's memory and the algorithm A* is running to find an optimal path that connects the source with the target point.

Because of memory issues, arduino could not successfully run the A* algorithm to produce the directions for the optimal path. So the A* algorithm compiled and run on a linux environment and results manually passed into the arduino code.

You will find two folders in the project. 

  -- The astar folder contains the .c file that implements the A* algorithm. Also there is a makedile that compliles that file.
  
  -- The arduino folder contains the .ino file for the arduino and an auxiliary library .h.

In the following image you can see the autonomous vehicle.
![the vehicle](https://cloud.githubusercontent.com/assets/13044530/11782519/23517878-a27a-11e5-8563-4e7fd03df50d.jpg)


The following image depicts the visual map that the car has to handle.
![static map](https://cloud.githubusercontent.com/assets/13044530/11782372/54a452e8-a279-11e5-95c9-70c8036d0616.png)

Below you can see the results from the A* algorithm for given start and target points and also the weights of every point in the map.
![a star algorithm](https://cloud.githubusercontent.com/assets/13044530/11782376/5b4ef9b8-a279-11e5-80e6-fadc69fb64eb.png)


