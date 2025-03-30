from geneticalgorithm import geneticalgorithm as ga
import numpy as np
import matplotlib.pyplot as plt

n = 9 
sigma_sq = 0.15

def f_1(X):
    x,y = X
    r_sq = (x-0.5)**2 + (y-0.5)**2
    return -np.cos(n*np.pi*np.sqrt(r_sq))**2 * np.exp(-r_sq/sigma_sq)
def f_2(X):
    x,y = X
    r_1_sq = (x-0.5)**2 + (y-0.5)**2
    r_2_sq = (x-0.6)**2 + (y-0.1)**2
    return -0.8 * np.exp(-r_1_sq/(0.3)**2) + 0.879008 * np.exp(-r_2_sq/(0.03)**2)

def f_lin(x,a,b):
    return a*x + b
def chi_sq_lin(X):
    a,b = X
    chi_sq = np.sum((data[:,1] - f_lin(data[:,0],a,b))**2 / sigma**2)
    return chi_sq
# f(x) = a*x + b + c*sin(d*x + e)
def lin_sin(x, X):
    a, b = X[0], X[1]
    num_sin = (len(X) - 2) // 3
    if num_sin > 0:
        X = np.array(X)
        c, d, e = X[2::3], X[3::3], X[4::3]
        sin_sum = np.sum(c[:, None] * np.sin(2*np.pi*(x/d[:, None] + e[:, None])), axis=0)
    else:
        sin_sum = 0
    return a * x + b + sin_sum
def chi_sq_lin_sin(X):
    chi_sq = np.sum((data[:,1] - lin_sin(data[:,0],X))**2 / sigma**2)
    return chi_sq

data = np.loadtxt(r'/home/sasch/Studium/CPPraktikum/05_algorithms_monte_carlo/Genetische_Algorithmen/lichtkurve.dat')
sigma = 5
# varbound = np.array([[-10, 10]] * 2)
# model_1 = ga(function = f_1, dimension = 2,variable_type='real', variable_boundaries=varbound)
# model_2 = ga(function = f_2, dimension = 2, variable_type='real', variable_boundaries=varbound)
# model_1.run()
# model_2.run()

x_fit = np.linspace(0,100,200)

# a,b =  1.14920004, 9.99595039

# # plt.figure("Genetic Algorithm Lichtkurve",figsize=(10,8))
# # plt.scatter(data[:,0],data[:,1],label="Datenpunkte",marker= 'x')
# # plt.plot(x_fit,f_lin(x_fit,a,b),label=fr'Linearer Fit, $a = {a:.3f}$, $b = {b:.3f}$, $\chi^2 = {chi_sq_lin([a,b]):.2f} $',c = 'r')  
# # plt.xlabel("Zeit [s]")
# # plt.ylabel("Intensität")
# # plt.title("Lichtkurve mit linearem Fit")
# # plt.grid()
# # plt.legend()

#Parametergrenzen für linearen Teil
varbound = np.array([[0, 5], [15, 25]])

# # Parametergrenzen für Sinusmoden
# c_range = np.array([0, 100])   # Amplitude
# d_range = np.array([data[1,0] - data[0,0], 50])
# e_range = np.array([0, 1])     # Phase

# # # Systematische Erhöhung der Modenanzahl und Speicherung der Ergebnisse
# results = []
# max_moden = 5  # Maximale Anzahl an Sinusmoden
# for i in range(1, max_moden + 1):
#     # Update der Parametergrenzen
#     varbound = np.vstack((varbound, c_range, d_range, e_range))
    
#     # Genetischer Algorithmus
#     if i == 5:
#         model = ga(function=chi_sq_lin_sin, dimension=2 + 3*i, variable_type='real', variable_boundaries=varbound, algorithm_parameters=
#                    {'max_num_iteration': 1000,
#                     'population_size': 1000,
#                     'mutation_probability': 0.2,
#                     'elit_ratio': 0.02,
#                     'crossover_probability': 0.5,
#                     'parents_portion': 0.4,
#                     'crossover_type': 'uniform',
#                     'max_iteration_without_improv': None})
#         model.run()
 


X_1sin = [1.00963359, 18.79318002, 11.34300977, 20.03832368,  0.51449311]
X_2sin = [ 0.99135294, 19.84934812,  9.87683351,  8.97366663,  0.7871053,  11.58957547,
 20.14426935,  0.52373691]
X_3sin = [1.01978175, 18.36768982, 11.42296198, 19.99810808,  0.50760155,  9.60072084,
  9.07119906,  0.83905339,  6.64060967,  7.41712608,  0.75174273]
X_4sin =  [ 1.00950322, 18.77453823,  9.90205769,  8.94873526,  0.77065814, 14.82776493,
 23.33125876,  0.54346275, 16.7564999,  22.86087334,  0.97110897,  9.45867654,
 19.59463538,  0.42551372]
X_5sin =  [ 0.98337042, 21.64374471,  7.74813858, 20.69747164,  0.60976188,  5.09328977,
  7.50151191,  0.8442321,   2.45216667, 19.13749685,  0.43750673,  7.44782555,
  9.07244151,  0.89500437,  1.72220806,  9.27894447,  0.83202333]


plt.figure("GA_plot_1sin",figsize=(10,8))
plt.scatter(data[:,0],data[:,1],label="Datenpunkte",marker= 'x')
plt.plot(x_fit,lin_sin(x_fit,X_1sin),label=fr'Linearer Fit mit 1 Sinusmode, $\chi^2 = {chi_sq_lin_sin(X_1sin):.2f} $',c = 'r')
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Lichtkurve mit linearem Fit und 1 Sinusmode")
plt.grid()
plt.legend()

plt.figure("GA_plot_2sin",figsize=(10,8))
plt.scatter(data[:,0],data[:,1],label="Datenpunkte",marker= 'x')
plt.plot(x_fit,lin_sin(x_fit,X_2sin),label=fr'Linearer Fit mit 2 Sinusmoden, $\chi^2 = {chi_sq_lin_sin(X_2sin):.2f} $',c = 'r')
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Lichtkurve mit linearem Fit und 2 Sinusmoden")
plt.grid()
plt.legend()

plt.figure("GA_plot_3sin",figsize=(10,8))
plt.scatter(data[:,0],data[:,1],label="Datenpunkte",marker= 'x')
plt.plot(x_fit,lin_sin(x_fit,X_3sin),label=fr'Linearer Fit mit 3 Sinusmoden, $\chi^2 = {chi_sq_lin_sin(X_3sin):.2f} $',c = 'r')
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Lichtkurve mit linearem Fit und 3 Sinusmoden")
plt.grid()
plt.legend()

plt.figure("GA_plot_4sin",figsize=(10,8))
plt.scatter(data[:,0],data[:,1],label="Datenpunkte",marker= 'x')
plt.plot(x_fit,lin_sin(x_fit,X_4sin),label=fr'Linearer Fit mit 4 Sinusmoden, $\chi^2 = {chi_sq_lin_sin(X_4sin):.2f} $',c = 'r')
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Lichtkurve mit linearem Fit und 4 Sinusmoden")
plt.grid()
plt.legend()

plt.figure("GA_plot_5sin",figsize=(10,8))
plt.scatter(data[:,0],data[:,1],label="Datenpunkte",marker= 'x')
plt.plot(x_fit,lin_sin(x_fit,X_5sin),label=fr'Linearer Fit mit 5 Sinusmoden, $\chi^2 = {chi_sq_lin_sin(X_5sin):.2f} $',c = 'r')
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Lichtkurve mit linearem Fit und 5 Sinusmoden")
plt.grid()
plt.legend()

plt.show()