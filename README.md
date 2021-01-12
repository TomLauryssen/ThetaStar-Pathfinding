# ThetaStar-Pathfinding
## What is Theta*?

As you all know a lot of pathfinding algorithms exist already. The most common of them are Dijkstra and A*. Even now researchers are still looking for even faster algorithms.  Sometimes this research points to already existing algorithms. An older algorithm could be improved with a little modification. Theta* is such a modification of A*.

In Theta* we check the same nodes as in A*, but we go one step further. When we consider our next Node to add to our path, we check if there is a neighbour that is closer to our goal and that has a line of sight of the node we are coming from. If this is the case, that would allow our path to go directly from one node to the next node’s neighbour. On a grid this will mean it will shorten the distance the player has to travel.

--picture


## Implementation

The project is grid-based. This means there is a list of nodes, every node has a connection with its neighbour. The neighbours can be in the horizontal, vertical and diagonal directions. The map also has walls. These walls affect the nodes and their connections. If a wall is a neighbour for a node, the node cannot have a connection with the wall. This means that when we calculate the Theta* path, the path will evade the walls.

--picture

### A*
In order to understand Theta* knowledge about A* is required. In A* star we calculate a path with knowing the startnode and the endnode.

We define a noderecord that keeps track of the node, its connection with the previous node, an accumulated cost of the distance travelled so far and a heuristic cost. The heuristic cost is the estimated cost we must travel form the node to the endnode. We then create 2 lists: an open list and a closed list. These lists will contain the noderecords. The open list contains noderecords we will check in order to create a path. The closed list contains those we need to form our path.

--picture

To start off, we create a noderecord with the startnode and the heuristic cost form the startnode to the endnode. We add this noderecord to the open list. This means we can do a loop while the openlist is not empty. In this loop we select a noderecord with smallest heuristic cost from the open list.

Next up, we loop over all the neighbours of this noderecord. We check if the neighbour is in the closed list. If it is, we will check if its accumulated cost is less than the accumulated cost of the node in the list. If this cost is smaller than we remove the node from the closed list, this allows to later add the node again with a shorter travel distance. If it’s bigger the node is declared invalid.

Then we check if the neighbour is in the open list. Here we repeat the same actions as with the closed list. If the neighbour is valid, we add it to the open list.

After we have looped over all the neighbours, we add the current noderecord to the closed list. This we do until on of the node equals the endnode. If this is the case then our closed list contains all the nodes we need for the path, which we now can reconstruct and visualize.

### Where does Theta* come into play?

The theta* modification comes when we check if our neighbour is in the open and closed list. When the node is declared valid, we can check if this neighbour doesn’t have any neighbours that have a connection with the noderecord’s node. If it’s not the case, then we follow basic A* and add the neighbour to the open list.

Yet when we do have a neighbour we can check if our accumulated cost to our Nneighbour* is smaller then the accumulated cost would we have gone through the neighbour. If the distance is smaller, we can look and see if our Nneighbour isn’t in the open list. If that’s the case, we will rermove it from the open list and add our new noderecord with the Nneighbour.

Yet when we do have a neighbour we can check if our accumulated cost to our Nneighbour* is smaller then the accumulated cost would we have gone through the neighbour. If the distance is smaller, we can look and see if our Nneighbour isn’t in the open list. If that’s the case, we will rermove it from the open list and add our new noderecord with the Nneighbour.

_*Nneighbour = neighbour’s neighbour_

## Results

Theta* is designed to be better version of A*. It does this by trying to find shorter path’s between nodes, but that means that sometimes it could take longer to calculate that path. This I saw in a test I set up. I calculated the path 10 times for both A* and Theta*

--picture

In my test, A* proved to be the fastest of the two. Visually there was no difference since the grid is so small, and there aren’t many connections which Theta* can take advantage of.

## Conclusion
While A* star might not always be the shortest path, it will give you good results combined with good speed. If you really need the shortest path use Theta*. It might be slower than A* in some cases it will give the best results.
