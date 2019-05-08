import random
from route import Route, read_data_file, generate_random_route


def hill_climb(route, steps=100_000):
    """
    Return an optimized solution to the Vehicle Routing Problem using Hill Climbing.

    Takes initial route as starting point, and greedily selects better
    neighbors until we exceed the number of steps allocated.
    """

    evaluations = 0
    while evaluations < steps:
        for neighbor in route.neighbors():
            if evaluations >= steps:
                break

            evaluations += 1

            if neighbor.cost < route.cost:
                route = neighbor
                break
        else:  # No break, local optimum:
            print("Reached local optimum")
            break

    return route


if __name__ == "__main__":
    random.seed(2019)
    instance = read_data_file("data/size50.txt")

    # Some starting point that is "legal", i.e. satisfies constraints.
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

    route = generate_random_route(instance)
    print(f"Initial route: {route}")
    print(f"Initial cost: {route.cost}")
    print("Climbing the hill...")
    route = hill_climb(route, 10000)

    print(f"Final route: {route}")
    print(f"Final cost:  {route.cost}")
