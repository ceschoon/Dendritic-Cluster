# DLA Dentritic Cluster Growth Simulation
Simulates the formation of a dendritic cluster dy diffusion limited aggregation (DLA). 

![alt text](Screenshots/Screenshot_2018-03-02_12-36-52.png?raw=true "Screenshot")

The algorithm works as follows:
- Walkers are added on the boundaries of the window as long as their number is under a certain limit.
- They are randomly moved in the window.
- We check if the walkers have a crystal in one of their neighbour cells. If they do, they are removed from the walkers list and a new crystal is added at their position. Else, they continue their walk.

A video of a cluster growing at 4x speed can be found in the "Videos" folder.
