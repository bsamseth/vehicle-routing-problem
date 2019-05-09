import random
import numpy as np

DEPOT_ID = 0  # Assumption: Customer IDs are strictly larger than DEPOT ID.


def pairwise(iterable):
    "x -> (x0,x1), (x1,x2), (x2, x3), ..."
    a, b = tee(iterable)
    return zip(a, islice(b, 1, None))


def distance(route, instance):
    """Return total distance of route."""
    cost = 0
    capacity = instance["capacity"]  # Initial capacity.
    last_x, last_y = instance["depot"]  # Start at depot.
    for c_id in route:
        customer = instance["customers"][c_id]
        if capacity < customer["demand"]:
            x, y = instance["depot"]
            cost += (x - last_x) ** 2 + (y - last_y) ** 2
            last_x, last_y = x, y
            capacity = instance["capacity"]

        # Subtract of the demand for this customer, and compute travel cost.
        capacity -= customer["demand"]
        x, y = customer["coords"]
        cost += (x - last_x) ** 2 + (y - last_y) ** 2
        last_x, last_y = x, y

    # Adding cost of returning home to depot.
    x, y = instance["depot"]
    cost += (x - last_x) ** 2 + (y - last_y) ** 2
    return cost


def reversed_sections(route):
    """
    Return all vaiations of route based on reversed sections, in random order.
    For every possible customer pair, reverse the section between them.
    Example: reversed_sections([1, 2, 3]) -> [1, 3, 2]
                                             [3, 1, 2]
                                             [3, 2, 1]
                                             [2, 1, 3]
                                             [2, 3, 1]
    Lightly adapted from here:
    http://www.psychicorigami.com/2007/05/12/tackling-the-travelling-salesman-problem-hill-climbing/
    """
    r1 = list(range(len(route)))
    r2 = list(range(len(route)))
    random.shuffle(r1)
    random.shuffle(r2)

    for i in r1:
        for j in r2:
            if i != j:
                copy = route[:]
                if i < j:
                    copy[i : j + 1] = reversed(route[i : j + 1])
                else:
                    copy[i + 1 :] = reversed(route[:j])
                    copy[:j] = reversed(route[i + 1 :])
                if copy != route:
                    yield copy


def random_route(instance):
    """Return a random route."""
    route = list(instance["customers"])
    random.shuffle(route)
    return route


def select_parents(pop, distances, group_size=5):
    """Return the two best routes out of a random group."""
    return [
        pop[distances.index(d)]
        for d in sorted(
            map(lambda i: distances[i], np.random.randint(len(pop), size=group_size))
        )[:2]
    ]


def pmx(p1, p2):
    """Perform Partially Mapped Crossover on p1 and p2."""
    return pmx_1(p1, p2), pmx_1(p2, p1)


def pmx_1(p1, p2):
    """Perform Partially Mapped Crossover on p1 and p2, yielding one child."""
    cut1 = random.randint(0, len(p1) - 2)
    cut2 = random.randint(cut1, len(p1) - 1)

    c1 = [None] * len(p1)
    c1[cut1:cut2] = p1[cut1:cut2]

    # fill in parts of p2[cut1:cut2] not in child c1
    for i in [i for i in p2[cut1:cut2] if i not in c1]:
        k = p2.index(p1[p2.index(i)])
        while True:
            if c1[k] is None:
                c1[k] = i
                break
            else:
                k = p2.index(p1[k])

    # Fill in remaining from p2
    for i in range(len(p2)):
        if c1[i] is None:
            c1[i] = p2[i]

    assert len(set(c1)) == len(p1), "Crossover lost something."
    return c1


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
