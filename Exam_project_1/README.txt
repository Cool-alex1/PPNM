This is my solution for project 1.

In the file "newton.cc/h" you can see my attempt to mostly make the what the project asked for.
In that file you will see the main method "newton" that takes the function defined for R, the matrix H,
the vector v, and an accuracy, (And whether or not it sould print anything). If the gradient for v is bigger than
the accuracy the loop will end, but otherwise it will find by which α f(v-αΔv) is smallest.
To find this α i made my own local minimum finder, which is discribed in more detale in the code (read my comments).
Due to the way f(v-αΔv) always behaves i could make a fast and precise function that always will find the minimum for 
f(v-αΔv).

The newton method was tested on multiple symmetric matrices of varying sizes and a matrix made for the hydrogen atom.
For the hydrogen atom both the smallest eigen-vector and eigen-value was found as well as the secound smallest 
eigen-vector and eigen-value. Since i could'nt se if you meant "find the secound smallest for all matrices" or just for
the hydrogen atom i will describe the method to do so here:
1) Find the smallest v_min for a given H.
2) Use that v_min to construct a startguess for v (v0) so that v0 and v_min is orthogonal.
3) Use the Newton method with the new v0. The accuracy here cannot be to great. (This is described in Out.txt)
4) The new v_min and λ_min will be the secound smallest eigen-components for H.

The speed at which this method finds the smallest eigen-value have also been looked at. The result from this is
further explained in Out.txt and the resulting plot can be seen in Plots/Plot.speed.svg.


I see this solution to the project as furrow as possible and therefore will be rated 10 on a scale of 1-10 by me.
