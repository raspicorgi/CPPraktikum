import numpy as np
import matplotlib.pyplot as plt
def I(U,a,b):
    return a*U + b # a = 1/R, b = I_0
def chi_squared(x,y,a,b,sigma):
    num = ((y - a - b*x)/sigma)**2
    return np.sum(num)
def linear_fit(x,y,y_err,choice):
    S = np.sum(1/y_err**2)
    S_x = np.sum(x/y_err**2)
    S_y = np.sum(y/y_err**2)
    S_xx = np.sum(x**2/y_err**2)
    S_xy = np.sum(x*y/y_err**2)
    D = S*S_xx - S_x**2
    if choice == 'offset':
        a = (S_xx*S_y - S_x*S_xy)/(D)
        b = (S*S_xy - S_x*S_y)/(D)
        sigma_a = np.sqrt(S_xx/D)
        sigma_b = np.sqrt(S/D)
        chi = chi_squared(x,y,a,b,y_err)
        nom_chi_squared = chi/(x.size-2)
        return a,b,sigma_a,sigma_b,nom_chi_squared
    else:
        b = S_xy/S_xx
        sigma_b = np.sqrt(S_x/S_xx)
        a=0
        nom_chi_squared = chi_squared(x,y,0,b,y_err)/(x.size-1)
        return b,sigma_b,nom_chi_squared


data = np.array([np.linspace(0.5,6,12),
                 [0.065,0.206,0.405,0.492,0.606,0.782,0.865,1.018,1.199,1.327,1.408,1.627],
                 [0.01,0.01,0.02,0.02,0.02,0.02,0.02,0.03,0.03,0.03,0.03,0.04]])

a,b,sigma_a,sigma_b,nom_chi_squared = linear_fit(data[0,:],data[1,:],data[2,:],'offset')
c,sigma_c,nom_chi_squared_c = linear_fit(data[0,:],data[1,:],data[2,:],'no_offset')
with open(r"/home/sasch/Studium/CPPraktikum/05_algorithms_monte_carlo/Aufgabe_2/results_a2.txt", "w") as file:
    file.write(f'I_0: {a} +- {sigma_a}\n')
    file.write(f'R: {1/b} +- {sigma_b/b**2}\n')
    file.write(f'nom_chi_squared: {nom_chi_squared}\n')
    file.write(f'R_no_offset: {1/c} +- {sigma_c/c**2}\n')
    file.write(f'nom_chi_squared: {nom_chi_squared_c}\n')
    file.close()
# Print results
print(f'I_0: {a} +- {sigma_a}')
print(f'R: {b} +- {sigma_b/b**2}')
print(f'nom_chi_squared: {nom_chi_squared}')
print(f'R_no_offset: {1/c} +- {sigma_c/c**2}')
print(f'nom_chi_squared: {nom_chi_squared_c}')
U_fit = np.linspace(0.5,6,100)
offset_fit = I(U_fit,b,a)
np_offset_fit = I(U_fit,c,0)
# Plot
plt.figure('Aufgabe 2', figsize=(10,8))
plt.errorbar(data[0,:],data[1,:],yerr = data[2,:],label='Messwerte',fmt='x',capsize=5)
plt.plot(U_fit,offset_fit,label='Offset Fit')
plt.plot(U_fit,np_offset_fit,label='No Offset Fit')
plt.legend()
plt.xlabel('U [V]')
plt.ylabel('I [A]')
plt.title('I = U/R + I_0 Messdaten vs Fit mit offset vs Fit ohne offset')
plt.grid()
plt.show()