# TWC Equations
I felt there was a need to explain certain equations in this project, mainly the resistivity, because I noticed some sources use the values wrong.

## Resistance
Resistance is calculated with the `calc_restance()` function which uses the equation below,

$R = R_{ref} \times (1 + a(T_{rise} + T_{ambient} - T_{ref}))$

where,
- Temperature coefficient $a$.
- Temperature rise $T_{rise}$ is the rise in temperature from the ambient temperature $T_{ambient}$, which in turn is used to find the difference from the reference temperature $T_{ref}$. Due to the resistivity value being found in $20 C\degree$ conditions, $T_{ref}$ is therefore $20 C \degree$.
- $R_{ref}$ is the resistance of the material at $T_{ref}$ found by using, $R_{ref} = \rho \frac{l}{A}$.

### Sources
- [Resistivity and Temperature coefficients at 20C](https://en.wikipedia.org/wiki/Electrical_resistivity_and_conductivity#Resistivity_and_conductivity_of_various_materials)
- [AllAboutCircuits](https://www.allaboutcircuits.com/textbook/direct-current/chpt-12/temperature-coefficient-resistance/)
- [LibreTexts](https://phys.libretexts.org/Bookshelves/University_Physics/University_Physics_(OpenStax)/University_Physics_II_-_Thermodynamics_Electricity_and_Magnetism_(OpenStax)/09%3A_Current_and_Resistance/9.04%3A_Resistivity_and_Resistance)
- [Electrical Information](https://electrical-information.com/temperature-coefficient-of-resistance/)
