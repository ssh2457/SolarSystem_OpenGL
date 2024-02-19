# Solar system simulation using OpenGL

This is a personal project to learn OpenGL.  
Given eccentricity, the trajectory for each planet is calculated from the Kepler's Equation so that Newton's method is used to get their numerical positions. The distances and scale for all celestial objects are disorted in order to illustrate all planets in a camera scene, while their revolution and rotation periods are proportional to the Earth's rotation period.

In order to visualize its 3D simulation more stereoscopically, a cube box and shadow effect is applied.

<p align="center">
    <img src="./images/demonstration1.png" title="demonstration1">    
    image1: general view1
</p>

<p align="center">
    <img src="./images/demonstration2.gif" title="demonstration2">    
    image2: general view2
</p>

To illustrate the eclipse effect, the omnidirectional shadow map is used in this project. The example images are below:

<p align="center">
    <img src="./images/clipse1.png" title="eclipse effect1">    
    image3: eclipse effect1 (The Moon is hidden bebind the Earth.)
</p>

<p align="center">
    <img src="./images/eclipse2.png" title="eclipse effect2">    
    image4: eclipse effect2 (The Moon's shadow is expressed on the Earth's surface.)
</p>


<p align="center">
    <img src="./images/eclipse3.gif" title="eclipse effect3">    
    image5: shadows on planets' surface.
</p>