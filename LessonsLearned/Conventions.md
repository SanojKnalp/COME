# Conventions

## Naming Conventions
### Variables
Whenever a variable is member variable, we use an underscore to indicate that. If it's a global variable, we don't

### Functions
For functions, we either use the StandardApproach or the_other_approach. Both are fine. 
### Files
Start with COME_ and then the respective name you want to give it.

## What we add/not add (for now)
### Linear Algebra
We assume non-complex matrices for now. No real advantage in allowing for complex linear algebra when we likely won't use it anytime in the near future.
### Mesh
Regarding meshes, we assume that meshes lower-dimensional than 3D are either x or xy, not x,z,xz or yz. That has mainly something do with easy of input-parsing.
That should definitely be adjusted some time later.