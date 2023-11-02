# CoreBSP
OpenGL Quake3 BSP viewer (C++)
================
This is an old version of BSP tree renderer written in C++. Instead of using PVS culling, the BSP geometry data is rearranged into geometry suitable for OpenGL VBOs which are grouped by texture index, so the number of draw call is drastically reduced even when rendering the whole level. This is huge performance boost compared to the original immediate mode implementation. The only drawback of using this approach is that OpenGL 3.3+ is required and older video cards are not supported.

Note: this renderer has basic functionalities and doesn't have support for other Quake3 goodies like Bezier curves, shader loading, etc. The more advanced version of this viewer is [here](https://github.com/JDragan/CoreQ3BSP) where those features are implemented and is actualy being developed.

Dependencies
-------
This project uses following auxilary libraries:
- Window/Input: [GLFW](https://www.glfw.org/)
- 3D Math: [glm](https://github.com/g-truc/glm)
- Extension loader: [glad](https://glad.dav1d.de)
- Texture loader: [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

Running the viewer:
- Depending on your platform, install/compile GLFW (if needed) then modify the provided `build.sh` script for your toolchain
- If on Linux and you already have glfw installed, then run:
`./build.sh`

`./build/CoreBSP maps/Level.bsp` for the default map, or
`./build/CoreBSP path/to/some_q3map.bsp`


Used documentation
- https://www.mralligator.com/q3/

For more maps see
- https://lvlworld.com/
