# Programming
In this markdown i'm going to describe some lessons i've learned while coding this project. 
## Cpp specifics
#### When to use & and when not to use it.
So basically, whenever we create something new, we are not supposed to use a pass by reference. 
Simply cause if there is no memory address allocated for it, we can't pass it.
On the other hand if we have an object already created, always pass by reference cause we don't need to copy which is better for memory and performance.
#### When to use protected access type for Inheritance
In general, we want to use protected whenever we want to access variables or functions from a class that we derive from, but without making them public. 
Simple example: Let's say we have a base class EquationSolvers with a member variable tolerance. Now we create a derived class CG. Now for CG to be able to access that tolerance,
we need to make tolerance protected, otherwise we can't get to it without making it public(terrible idea) (one would not programm it like this, but it still makes sense)

## General programming


