# Creatures

An environment where simulated creatures are living, reproducing and evolving.

**[work in progress]**

## Plan

#### World
 - procedurally generated
 - randomly distributed creatures
 - contains non living items and obstacles

####  Creature
 - different types with varying properties
 - generated based on genes (rules)
 - made up of cells
 - lays eggs or clones itself to reproduce
 - must consume other cells
 - dies if malnourished or damaged
 - leaves cells after dying

#### Evolutionary system
 - shape and behaviour
 - sensory organs
 - weapons and defense mechanisms
 
 ---
 
 ### Utilized libraries
[Sokol](https://github.com/floooh/sokol) (OpenGL wrapper)  
[Chipmunk2D](https://github.com/slembcke/Chipmunk2D) (Physics engine)
