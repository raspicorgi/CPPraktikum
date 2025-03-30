import numpy as np

light_speed_mes = np.array([299793, 299792, 299782])
light_speed_mes_error = np.array([2.0,4.5,25])
 
def weighted_mean(c,c_err):
    return np.sum(c/c_err**2)/np.sum(1/c_err**2)
def chi_squared(c,c_err):
    return np.sum((c-weighted_mean(c,c_err))**2/c_err**2)
def internal_variance(c_err):
    return  1/(np.sum(1 /((c_err)**2)))
def external_variance(c,c_err):
    return np.sum((c - weighted_mean(c,c_err))**2 / c_err**2)/((np.size(c)-1)*np.sum(1/c_err**2))
# Print results into file
with open(r"/home/sasch/Studium/CPPraktikum/05_algorithms_monte_carlo/Aufgabe_1/results_a1.txt", "w") as file:
    file.write(f"Weighted Mean: {weighted_mean(light_speed_mes,light_speed_mes_error)}\n")
    file.write(f"Chi Squared: {chi_squared(light_speed_mes,light_speed_mes_error)}\n")
    file.write(f"Internal error: {np.sqrt(internal_variance(light_speed_mes_error))}\n")
    file.write(f"External error: {np.sqrt(external_variance(light_speed_mes,light_speed_mes_error))}\n")
    file.write(f"Control 1/N-M: {(external_variance(light_speed_mes,light_speed_mes_error) / internal_variance(light_speed_mes_error)) / chi_squared(light_speed_mes,light_speed_mes_error)}\n")
    file.close()