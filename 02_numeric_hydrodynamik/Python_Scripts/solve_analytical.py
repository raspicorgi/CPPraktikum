#!/usr/bin/env python
# Import the Riemann solver library. Note that this will only work if the file
# 'riemannsolver.py' is in the same directory as this script.
import riemannsolver
# Import the Python numerical libraries, as we need them for arange.
import numpy as np
# Import Matplotlib, which we will use to plot the results.
import matplotlib.pyplot as plt

rho = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/rho_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
u = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/u_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
p = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/p_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
epsilon = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/epsilon_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
T = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/T_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
xb = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/xb_t0.228s_N100.000_dt0.001.txt",delimiter = ";")


################################################################################
# some global definitions
################################################################################

# the constant adiabatic index
GAMMA = 1.4

# the Riemann solver
solver = riemannsolver.RiemannSolver(GAMMA)

# the constant time step
timestep = 0.001

# number of steps
numstep = 228

# number of cells
numcell = 100

################################################################################
# the actual program
################################################################################

# reference solution: as the Sod shock problem is in fact a Riemann problem,
# this is just the actual solution of the Riemann problem, evaluated at the
# final time of the simulation.
xref = np.arange(-0.5, 0.5, 0.001)
# rhoref = [solver.solve(1., 0., 1.0, 0.1, 0., 0.1, (x) / (timestep * numstep))[0]  for x in xref]
rhoref = np.array([solver.solve(1., 0., 1., 0.125, 0., 0.1, x / (timestep * numstep))[0] for x in xref])
uref = np.array([solver.solve(1., 0., 1., 0.125, 0., 0.1, x / (timestep * numstep))[1] for x in xref])
pref = np.array([solver.solve(1., 0., 1., 0.125, 0., 0.1, x / (timestep * numstep))[2] for x in xref])
epsilon_ref = pref / ((GAMMA - 1) * rhoref)
Tref = (GAMMA - 1) * epsilon_ref
xref = xref + 0.5

fig, ax = plt.subplots(4)
fig.figsize=(15,8)
fig.tight_layout(h_pad=2)
fig.subplots_adjust(top=0.9,left = 0.1, right = 0.9, bottom = 0.1)

# plot the reference solution and the actual solution
ax[0].plot(xref, rhoref, label='Analytische Lösung',color = 'blue')
ax[0].plot(xb[2:102], rho[2:102], label='Numerische Lösung', color = 'orange', ls = '--')   
ax[1].plot(xref, uref, label='Analytische Lösung',c = 'blue')
ax[1].plot(xb[2:102], u[2:102], label='Numerische Lösung',c = 'orange', ls = '--')
ax[2].plot(xref, pref, label='Analytische Lösung',c = 'blue')
ax[2].plot(xb[2:102], p[2:102], label='Numerische Lösung',c = 'orange', ls = '--')
ax[3].plot(xref, Tref, label='Analytische Lösung',c = 'blue')
ax[3].plot(xb[2:102], T[2:102], label='Numerische Lösung',c = 'orange', ls = '--')
ax[0].legend()

ax[0].set_title("Shock Tube, Analaytische Lösung vs. Numerische Lösung")
#pl.plot([cell._midpoint for cell in cells], [cell._density for cell in cells], "k.")
ax[3].set_xlabel(r'$x$')
# ax[0].set_ylim(-0.01,1.1)
# ax[2].set_ylim(-0.01,1)
# ax[1].set_ylim(-0.01,1)
ax[0].set_ylabel(r"$\rho(x,t = 0.228s)$",fontsize = 8)
ax[1].set_ylabel(r"u(x,t = 0.228s)",fontsize = 8)
ax[2].set_ylabel(r"p(x,t = 0.228s)",fontsize = 8)
ax[3].set_ylabel(r"T(x,t = 0.228s)",fontsize = 8)
# save the plot as a PNG image
fig.savefig("sodshock_analytical.png",dpi=500)