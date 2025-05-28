import numpy as np
import matplotlib.pyplot as plt

# Fungsi untuk membuat plot periodik
def plot_periodic_function(f, title, period=2*np.pi, x_range=(-3*np.pi, 3*np.pi)):
    x = np.linspace(x_range[0], x_range[1], 1000)
    y = f(x)
    
    plt.figure(figsize=(10, 4))
    plt.plot(x, y)
    plt.title(title)
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.grid(True)
    plt.axhline(0, color='black', linewidth=0.5)
    plt.axvline(0, color='black', linewidth=0.5)
    plt.show()

# 4a. f(x) = 2x (periodik 2π)
def f_a(x):
    return 2 * ((x + np.pi) % (2*np.pi) - np.pi)

plot_periodic_function(f_a, "4a. f(x) = 2x (Periodik 2π)")

# 4b. g(x) = |sin x| (periodik π)
def f_b(x):
    return np.abs(np.sin(x))

plot_periodic_function(f_b, "4b. g(x) = |sin x| (Periodik π)", period=np.pi)

# 4c. h(x) = e^{-|x|} (periodik 2π)
def f_c(x):
    x_mod = (x + np.pi) % (2*np.pi) - np.pi
    return np.exp(-np.abs(x_mod))

plot_periodic_function(f_c, "4c. h(x) = e^{-|x|} (Periodik 2π)")

# 4d. f(t) piecewise (periodik 2π)
def f_d(x):
    x_mod = (x + np.pi) % (2*np.pi) - np.pi
    return np.where(x_mod < 0, -x_mod**2, x_mod**2)

plot_periodic_function(f_d, "4d. f(t) = -t² (-π<t<0), t² (0<t<π)")

# 4e. g(t) piecewise (periodik 2π)
def f_e(x):
    x_mod = (x + np.pi) % (2*np.pi) - np.pi
    return np.where(x_mod < 0, 1, np.cos(2*x_mod))

plot_periodic_function(f_e, "4e. g(t) = 1 (-π<t<0), cos(2t) (0<t<π)")