"""
This module prodvides the plotRoute function which can be used
to plot customers and the route between them, based on a route
and a instance dictionary.
"""

import matplotlib.pyplot as plt


def plot_route(route, instance, show=True):
    coords = []
    sub = [instance["depot"]]
    capacity = instance["capacity"]
    for c_id in route:
        if capacity < instance["customers"][c_id]["demand"]:
            coords.append(sub + [instance["depot"]])
            sub = [instance["depot"]]
            capacity = instance["capacity"]

        sub.append(instance["customers"][c_id]["coords"])
        capacity -= instance["customers"][c_id]["demand"]

    coords.append(sub + [instance["depot"]])

    plt.figure()
    for sub in coords:
        plt.plot(*list(zip(*sub)))

    if show:
        plt.show()
