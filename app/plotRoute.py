"""
Run as follows:

    ./main | python plotRoute.py

Assuming ./main outputs something from exportPlotData.
"""

import matplotlib.pyplot as plt
import numpy as np
import sys

route = eval(sys.stdin.read())

for sub in route:
    plt.plot(*np.asarray(sub).T)
plt.show()
