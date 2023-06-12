# F2L

Always orient white face down

1. Cubes in position
    1. Edge in position
        1. White face right
        2. White face left

    2. Edge not in position
        1. White face right
        2. White face left
        3. White face down

2. Corner in position (always position edge in correct face)
    1. Corner white down
        1. Edge right
        2. Edge left
    2. Corner white right
        1. Edge right
        2. Edge left
    3. Corner white left
        1. Edge right
        2. Edge left

3. Edge in position (always position corner on top of edge)
    1. Edge in correct position
        1. Corner white up
        2. Corner white right
        3. Corner white left
    2. Edge not in correct position
        1. Corner white up
        2. Corner white right
        3. Corner white left

4. Cubes joined (always position corner on top)
    1. Cubes on the right
        1. Edge in correct face
            1. Corner white face up
            2. Corner white face left
            3. Corner white face right
        2. Edge not in correct face
            1. Corner white face up
            2. Corner white face left
            3. Corner white face right

    2. Cubes on the left
        1. Edge in correct face
            1. Corner white face up
            2. Corner white face left
            3. Corner white face right
        2. Edge not in correct face
            1. Corner white face up
            2. Corner white face left
            3. Corner white face right

5. Cubes separated (always position corner on top)
    1. Corner white face up
        1. Edge right
            1. Edge correct face right
            2. Edge correct face left
        2. Edge left
            1. Edge correct face right
            2. Edge correct face left
    2. Corner white face right
        1. Edge right
            1. Edge correct face right
            2. Edge correct face left
        2. Edge left
            1. Edge correct face right
            2. Edge correct face left
    3. Corner white face left
        1. Edge right
            1. Edge correct face right
            2. Edge correct face left
        2. Edge left
            1. Edge correct face right
            2. Edge correct face left

# OLL

Yellow face always up

If only yellow center, do what you know

1. Cross
    1. All corner set face each other
    2. One corner set face each other

2. Cross with one corner (always position corner on top and no egde facing up)
    1. Corner left
    2. Corner right

3. Cross with two corners same line
    1. Corner face each other
    2. Corner not face each other

4. Cross with two corners not same line (single algorithm)

# PLL

1. Orient edges
    1. Edges face each other (position them on left and right)
    2. Edges do not face each other (position one edge on correct face)
        1. Left to Right
        2. Right to Left

2. Orient corners
    1. All corners in correct face
    2. Corner face each other (position them on left and right)
    3. Single correct corner (place it on the bottom left)
        1. Upper left corner go bottom
        2. Upper left corner go right
