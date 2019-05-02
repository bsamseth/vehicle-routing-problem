# Vehicle Routing Problem

This is some very crude and simple code related to the Vehicle Routing Problem. Not much to see.

The version of the VRP that is tackled here is as follows:

- One central depot at a given location
- An infinite number of trucks with a given product capacity, all starting at the depot
- A set of customers located around the world, each with a demand for a specific number of products.

The task is to find an optimal (or more realistically, a good) route. A route is defined by a set of sub-routes, each taken by one truck. The trucks can only deliver to as many customers as they have capacity (given customers demands), and must return to the depot when they cannot fulfill more orders in the same drive.

The objective to minimize here is the total Euclidean distance driven by all trucks in total.

## Structure

- `route.py` contains the code for the representation of a route
  + A `Route` object is a Python-list with some extra functionallity.
  + The elements of the `Route` are `SubRoute`s
    - A `SubRoute` is a Python-list of customer IDs, indicating the sequence of customers to serve in order. 
    - It also contains the cost of the sub-route, and the excess capacity on the truck (the amount of product left over when the sub-route would be completed).
- `optimize.py` contains the code for optimizing routes.
  - Currently only a simple hill climbing strategy.
