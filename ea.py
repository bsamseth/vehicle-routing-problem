from route import random_route, distance, select_parents, pmx, reversed_sections
from hill_climb import hill_climb
import numpy as np
import random
from tqdm import tqdm


def EA(
    instance,
    pop_size=100,
    max_generations=100,
    group_size=5,
    mutation_prob=0.05,
    verbose_output=False,
):
    """
    Solve VRP using an evolutionary algorithm.
    Return the best route, along with the cost of said route.

    Parent selection: Best out of randomly selected group.
    Recombination: PMX
    Mutation: Reversed Sections
    Survior selection: Generational elitism

    If verbose_output is True, a list of the best dist in each
    generation will be returned along with the usual output.
    """
    # Initialize population at random
    population = [random_route(instance) for _ in range(pop_size)]

    gen_best = []
    for generation in tqdm(range(max_generations)):
        # Calculate distances for each tour and
        # save the best tour for next gen.
        distances = [distance(route, instance) for route in population]
        best_index = np.argmin(distances)
        new_population = [population[best_index]]
        gen_best.append(distances[best_index])

        # Select parents and make children with recombination
        # Do this until we have pop_size in new generation.
        while len(new_population) < pop_size:
            parent1, parent2 = select_parents(
                population, distances, group_size=group_size
            )
            new_population += pmx(parent1, parent2)

        # Give each child the chance to mutate, given mutation_prob.
        for i in range(1, pop_size):
            if random.random() < mutation_prob:
                new_population[i] = next(reversed_sections(new_population[i]))

        population = new_population

    # Chose if the list of best dists in each gen should be returned.
    if verbose_output:
        return population[0], distance(population[0], instance), gen_best
    else:
        return population[0], distance(population[0], instance)


if __name__ == "__main__":
    from route import read_data_file
    from plot_route import plot_route
    import matplotlib.pyplot as plt

    samples = 2  # number of times to run EA
    max_generations = 500
    sizes = [100, 400, 1000]
    instance = read_data_file("data/size50.txt")

    gen_dists = np.zeros((len(sizes), max_generations))

    for size_nr, size in enumerate(sizes):
        dists = np.zeros(samples)
        for i in tqdm(range(samples)):
            route, dist, gen_dist = EA(
                instance,
                pop_size=size,
                max_generations=max_generations,
                verbose_output=True,
            )
            dists[i] = dist
            gen_dists[size_nr, :] += np.array(gen_dist)

        gen_dists[size_nr] /= samples
        worst = max(dists)
        best = min(dists)
        average = sum(dists) / samples
        std = np.std(dists)

        print("\nPopulation Size = {}".format(size))
        print("\tBest: {0:6.2f}".format(best))
        print("\tWorst: {0:5.2f}".format(worst))
        print("\tAverage: {0:3.2f}".format(average))
        print("\tStd: {0:7.2f}".format(std))

    fig, ax = plt.subplots()
    for size_nr, size in enumerate(sizes):
        ax.plot(
            list(range(max_generations)),
            gen_dists[size_nr, :],
            label="Size = {0}".format(size),
        )
    ax.set_xlabel("Number of generations", size=16)
    ax.set_ylabel("Route cost", size=16)
    ax.set_title("(Average) Best tour in each generation", size=20)
    ax.legend()
    plt.show()
