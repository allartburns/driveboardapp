Challenge: the lasersaur software converts input files (DXF, SVG) to
an interpreted format, then uses external controls in the UI to
<<<<<<< HEAD
generate g-code.

How do we use a g-code file as input?   This will be an issue with
other laser cutters, but I think the efficient solution is to just
operate the g-code as submitted.

This also means that third-party software will have to generate
lasersaur-compliant g-code, but that seems a reasonable request.
=======
generate G-code.

When we input G-code, how do we generate those enternal controls for a
lasersaur?  Do we make the abstract version (same as parsed DXR, SVG)
and return that to the UI for post-processing?
>>>>>>> edef688919f91e02d92c617ffd9b839deda9fd34
