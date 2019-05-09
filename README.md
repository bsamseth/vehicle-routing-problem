# Vehicle Routing Problem

This is some very crude and simple code related to the Vehicle Routing Problem. Not much to see.

The version of the VRP that is tackled here is as follows:

- One central depot at a given location
- An infinite number of trucks with a given product capacity, all starting at the depot
- A set of customers located around the world, each with a demand for a specific number of products.

The task is to find an optimal (or more realistically, a good) route. A route is defined by a set of sub-routes, each taken by one truck. The trucks can only deliver to as many customers as they have capacity (given customers demands), and must return to the depot when they cannot fulfill more orders in the same drive.

The objective to minimize here is the total Euclidean distance driven by all trucks in total.

## Structure

- `route.py`: Lots of utilities
- `hill_climb.py`/`ea.py`: Code for hill climbing/evolutionary algorithm
  - Both files can be run, which will produce some statistics/plots.
- `plot_route.py`: Utility to plot a route


## Setup

Requires Python 3.6.

``` bash
> pip install pipenv  # If not installed before (may need to use pip3 instead)
> pipenv install
> pipenv shell
> python filename_of_file_to_run.py
```

