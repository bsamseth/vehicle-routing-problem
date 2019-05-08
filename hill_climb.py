import random
from route import random_route, distance, reversed_sections
from tqdm import tqdm
import numpy as np


def hill_climb(instance, max_evaluations=50000):
    best_perm = random_route(instance)
    best_dist = distance(best_perm, instance)
    evaluations = 1

    while evaluations < max_evaluations:
        for neighbor in reversed_sections(best_perm):
            if evaluations >= max_evaluations:
                break

            new_dist = distance(neighbor, instance)
            evaluations += 1
            if new_dist < best_dist:
                best_dist = new_dist
                best_perm = neighbor
                break
        else:
            # no break == local optima
            break

    return best_perm, best_dist, evaluations >= max_evaluations


if __name__ == "__main__":
    from route import read_data_file
    from plot_route import plot_route
    import matplotlib.pyplot as plt

    samples = 10  # number of times to run hill_climb
    best_tour = []

    for input_file in ("data/size50.txt", "data/size199.txt"):
        instance = read_data_file(input_file)
        dists = []
        routes = []
        for _ in tqdm(range(samples)):
            route, dist, _ = hill_climb(instance)
            dists.append(dist)
            routes.append(route)
        worst = max(dists)
        best = min(dists)
        average = sum(dists) / samples
        std = np.std(dists)

        print("\n#customers = {}".format(instance["n_nodes"]))
        print("\tBest: {0:6.2f}".format(best))
        print("\tWorst: {0:5.2f}".format(worst))
        print("\tAverage: {0:3.2f}".format(average))
        print("\tStd: {0:7.2f}".format(std))

        best_tour.append((routes[dists.index(min(dists))], instance))

    plot_route(*best_tour[0], show=False)
    plot_route(*best_tour[1])
