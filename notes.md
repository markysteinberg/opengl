# PERSONAL ACCESS TOKEN 
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

# TODO LIST 
 - Maybe implement hot re-loading when you feel like it 
 - Implement a physics system and collider (rigid body, box collider)
 - Implement a map maker
 - Experiment with some shading 
 - Switch to CMake
 - Add a HUD with debug stats (fps, position)
 - Implement entity system
 - Tie everything together with engine.h (not urgent)
  
# PROJECT NOTES 
  - entity.h/.cpp and game.h/.cpp are incomplete

# KNOWLEDGE NOTES 
 - View matrix and Projection matrix applies to all objects, whereas the Model matrix is unique to the object 


# PIPELINE 
Startup: 
    1. Load assets via Asset Manager
    2. Create entitites 

Loop: 
    1. Handle input
    2. Update world (change state of everything)
    3. Render scene 
    4. Swap buffers 
    

