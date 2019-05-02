import itertools
import math
import copy
import random

DEPOT_ID = -1  # No customer id in data files should have id = DEPOT_ID.


class SubRoute(list):
    def __init__(self, sub_route, instance):
        super().__init__(sub_route)

        # Compute cost of route and leftover capacity.
        self.cost = 0
        self.capacity = instance["capacity"]  # Initial capacity. 
        last_x, last_y = instance["depot"]  # Start at depot.
        for customer in (instance["customers"][c_id] for c_id in self):

            # Subtract of the demand for this customer, and compute travel cost.
            self.capacity -= customer["demand"]
            x, y = customer["coords"]
            self.cost += math.sqrt((x - last_x) ** 2 + (y - last_y) ** 2)
            last_x, last_y = x, y

        # Adding cost of returning home to depot.
        x, y = instance["depot"]
        self.cost += math.sqrt((x - last_x) ** 2 + (y - last_y) ** 2)

        if self.capacity < 0:
            raise ValueError("The sub route exceeds the capacity of the trucks.")


class Route(list):
    def __init__(self, route, instance):
        super().__init__([SubRoute(sub, instance) for sub in route])
        self._instance = instance

    @property
    def cost(self):
        return sum(sub.cost for sub in self)

    def neighbors(self):
        """
        Yield successive neighbors of this route.

        A neighbor is currently defined simply as a interchange of customers
        between any pair of sub routes, including within the same sub route.
        Note that this will yield neighbors forever, and might return the same
        one more than once.
        """
        neighbor = copy.deepcopy(self)
        while True:
            i, j = [
                random.randrange(0, len(self)) for _ in range(2)
            ]  # Random sub routes i and j.
            k, l = (
                random.randrange(0, len(self[i])),
                random.randrange(0, len(self[j])),
            )  # Random pair of customers within each sub route.

            # Swap the two:
            sub_i, sub_j = list(self[i]), list(self[j])
            tmp = sub_i[k]
            sub_i[k] = sub_j[l]
            sub_j[l] = tmp

            try:
                # Convert plain lists to SubRoute, which raises error if routes are impossible.
                sub_i, sub_j = SubRoute(sub_i, self._instance), SubRoute(sub_j, self._instance)
            except ValueError:
                continue  # Try another pair.

            neighbor[i], neighbor[j] = sub_i, sub_j
            yield neighbor
            neighbor[i], neighbor[j] = self[i], self[j]


def read_data_file(filename):
    """
    Read an instance of the Vehicle Routing Problem

    Expects data formatted as follows (type of whitespace does not matter, i.e.
    newline == space):

        number-of-nodes
        capacity-of-trucks
        depot-x-coordinate depot-y-coordinate
        customer-id customer-x customer y customer-demand

    where the last line (4 numbers) should be repeated exactly number-of-nodes times.

    Return data as Python dictionary:

    {
        'n_nodes': X,
        'capacity': X,
        'depot': X,
        'customers': {
            X: {'coords': [X, X], 'demand': X},
            ...
        l}
    }
    """

    with open(filename, "r") as f:
        data = iter(int(c) for c in f.read().strip().split())

    instance = {
        "n_nodes": next(data),
        "capacity": next(data),
        "depot": (next(data), next(data)),
        "customers": {
            i: {"coords": (x, y), "demand": d} for i, x, y, d in zip(*[data] * 4)
        },
    }

    assert instance["n_nodes"] == len(instance["customers"])

    return instance


if __name__ == "__main__":
    instance = read_data_file("data/size50.txt")

    route = Route(
        [
            [14, 25, 13, 41, 40, 19, 42, 17],
            [27, 48, 8, 26, 7, 43, 24, 23, 6],
            [38, 9, 30, 34, 50, 21, 29, 16, 11, 32],
            [2, 20, 35, 36, 3, 28, 31, 22, 1],
            [5, 49, 10, 39, 33, 45, 15, 44, 37, 12],
            [46, 47, 4, 18],
        ],
        instance,
    )

    print("Initial route:", route)
    print("Initial cost:", route.cost)
    print(
        "Minimum of 1000 neighbors:",
        min([n.cost for _, n in zip(range(1000), route.neighbors())]),
    )
