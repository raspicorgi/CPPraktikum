import numpy as np
import scipy.special as sp
import matplotlib.pyplot as plt

# === Definition der analytischen Formeln ===
def analytical_energy(beta, J=1):
    """ Berechnet die mittlere Energie pro Spin mit der Onsager-Formel """
    k = 4 * np.tanh(beta * J)**2
    return 2J -J * (1/np.tanh(2 * beta * J)) * (1 + (2 / np.pi) * (2 * np.tanh(2 * beta * J)**2 - 1) * sp.ellipk(k))

def analytical_magnetization(beta, J=1):
    """ Berechnet die absolute Magnetisierung für T < Tc (beta > beta_c) """
    beta_c = np.log(1 + np.sqrt(2)) / (2 * J)  # Kritische Temperatur
    if beta < beta_c:
        return 0  # In der paramagnetischen Phase ist die Magnetisierung 0
    return (1 - np.sinh(-4 * beta * J)**-4) ** (1 / 8)

# === Wertebereich für Beta ===
beta_values = np.linspace(0.1, 1.0, 10)  # Werte für 1/T

# === Berechnung der analytischen Werte ===
energy_analytical = np.array([analytical_energy(beta) for beta in beta_values])
magnetization_analytical = np.array([analytical_magnetization(beta) for beta in beta_values])

print("Analytische Werte:")
print("Energie:", energy_analytical)
print("Magnetisierung:", magnetization_analytical)

# === Vergleich mit numerischen Daten (Platzhalter: hier deine Simulationswerte einfügen!) ===
# Ersetze diese Arrays mit deinen numerischen Simulationsergebnissen:
energy_numerical = np.array([0.0, -1.8285109168848936, -3.8046133800390773, -5.599786118820443, -6.819152683671692, -7.471417020216961, -7.774425098686427, -7.905787493141993, -7.961012834812352, -7.98392834374676])  # Hier deine berechneten Energien einfügen
magnetization_numerical = np.array([1.5, 2.00482005378279, 2.6201838757774083, 3.20445648070164, 3.6073123761875125, 3.823977431111739, 3.9248385694096433, 3.9686010219399424, 3.987005161726391, 3.9946429309943987])  # Hier deine berechneten |M|-Werte einfügen

# === Plots zur Visualisierung ===
plt.figure(figsize=(12, 5))

# Plot der Energie
plt.subplot(1, 2, 1)
plt.plot(beta_values, energy_analytical, label="Analytisch", linestyle="dashed", color="black")
plt.scatter(beta_values, energy_numerical, label="Numerisch", color="red", marker="o")
plt.xlabel("β (Inverse Temperatur)")
plt.ylabel("⟨E⟩ / L²")
plt.title("Vergleich der Energie")
plt.legend()

# Plot der Magnetisierung
plt.subplot(1, 2, 2)
plt.plot(beta_values, magnetization_analytical, label="Analytisch", linestyle="dashed", color="black")
plt.scatter(beta_values, magnetization_numerical, label="Numerisch", color="blue", marker="o")
plt.xlabel("β (Inverse Temperatur)")
plt.ylabel("⟨|M|⟩")
plt.title("Vergleich der Magnetisierung")
plt.legend()

plt.tight_layout()
plt.show()
