import numpy as np
import scipy.integrate as integrate
import matplotlib.pyplot as plt

def energy_density_analytical(beta):
    """Berechnet die Energiedichte für das 2D-Ising-Modell analytisch."""
    tanh_beta = np.tanh(2 * beta)
    cosh_beta = np.cosh(2 * beta)
    xi = 2 * tanh_beta / cosh_beta
    
    def integrand(theta, xi):
        return 1 / np.sqrt(1 - xi**2 * np.sin(theta)**2)
    
    K_xi, _ = integrate.quad(integrand, 0, np.pi/2, args=(xi,))
    
    energy_density = - cosh_beta / (1 / tanh_beta) * (1 + (2 * tanh_beta**2 - 1) * 2 / np.pi * K_xi)
    return energy_density

def magnetization_analytical(beta):
    """Berechnet die Magnetisierung für das 2D-Ising-Modell analytisch."""
    if beta <= 0.440687:
        return 0  # Magnetisierung ist null oberhalb der kritischen Temperatur
    else:
        return (1 - np.sinh(2 * beta)**(-4))**(1/8)

# Parameter
betas = np.linspace(0, 1, 20)
energies = np.array([])
magnetizations = np.array([])

# Berechnung und Ausgabe
print("Analytische Vorhersagen für das 2D-Ising-Modell:")
for beta in betas:
    energy = energy_density_analytical(beta)
    magnetization = magnetization_analytical(beta)
    energies = np.append(energies, energy)
    magnetizations = np.append(magnetizations, magnetization)
    print(f"  beta = {beta:.2f}, Energie = {energy:.4f}, Magnetisierung = {magnetization:.4f}")

plt.plot(betas, energies, label="Energiedichte")
plt.plot(betas, magnetizations, label="Magnetisierung")
plt.xlabel(r"$\beta$")
plt.legend()
plt.show()