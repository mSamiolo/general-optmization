// Define the points
Point(1) = {0, 0, 0, 1.0}; // Point 1 at (0,0)
Point(2) = {1, 0, 0, 1.0}; // Point 2 at (1,0)
Point(3) = {1, 1, 0, 1.0}; // Point 3 at (1,1)
Point(4) = {0, 1, 0, 1.0}; // Point 4 at (0,1)

// Define the lines
Line(1) = {1, 2}; // Line from Point 1 to Point 2
Line(2) = {2, 3}; // Line from Point 2 to Point 3
Line(3) = {3, 4}; // Line from Point 3 to Point 4
Line(4) = {4, 1}; // Line from Point 4 to Point 1

// Define the physical entities (edge boundaries)
Physical Line("left") = {4};   // Boundary "left"
Physical Line("down") = {1};   // Boundary "down"
Physical Line("right") = {2};  // Boundary "right"
Physical Line("up") = {3};     // Boundary "up"

// Define the physical entities (point boundaries) 
Physical Point("c1", 5) = {1};
Physical Point("c2", 6) = {2};
Physical Point("c3", 7) = {3};
Physical Point("c4", 8) = {4};

// Define the surface
Line Loop(1) = {1, 2, 3, 4}; // Line loop connecting all lines
Plane Surface(1) = {1};      // Surface bounded by Line Loop 1//+
