# Algorithms for Chordal Graphs

## Description
***Graphs*** are one of the most used data structures in real-world applications. The speciality of graphs is that they can modelled to represent relationships between things which can be useful to solve different problems. Many real-world problems can be reduced to known graph problems which makes it very important to solve these problems in the most efficient way possible.

*Graphs* are used in social network applications to model relationships between two people, determine the information flow, etc. They are also used in navigation applications to represent roads and stations in form of graphs and finding the shortest path between any two stations. They are also used in the internet connectivity, studying protein interactions, neural networks for deep learning, network packet traffic, quantum field theory and so on.

## Aim

Its application in a variety of fields and technologies makes the *graph* an important data structure to study and solve problems in most optimal way possible for its real-time use. 

Various problems related to graphs are **NP-hard** which makes it very difficult to solve these problems on real-time data which consists of very large data as it takes a lot of time to execute these problems on large data.

The whole idea of this project is to take few problems concerned with graphs which are NP-hard and solving those problems in linear time on a special class of graphs called ***Chordal Graphs***. The problems that are going to be discussed are as follows:
- Recognition of Chordal Graph
- Maximum Clique Problem
- Minimum Vertex Coloring Problem
- Maximum Independent Set Problem
- Minimum Clique Cover Problem

## Methodology
Thorough Literature survey has been done before implementing the above named problems in linear time. Many different data structures have been used to implement certain function to achieve a linear time complexity. 

The implementation code has been tested on many different graphs which are generated using a random chordal graph generator. The random chordal graph generated has been built using C++ which takes the number of vertices as input as output a graph in its adjacency list representation. Everything other than the number of vertices is chosen in random to make sure that a more randomized graph is being generated. 

## How to Run

There are 2 c++ code files in the `Code` directory in this repository:

1. `project.cpp`: This file contains all the implementations of the above mentioned problems in linear time.

2. `generate_random.cpp`: This file contains the functions to build a random chordal graph and print its adjacency list representation.

Firstly, the `project.cpp` takes a custom graph as input to the functions upon. The input can be provided through console or through a text file. To provide a custom graph input through console, the `freopen("input.txt","r",stdin)` line in the main function of the code should be commented. 
Please use the below steps to run the file:

- To Compile: `g++ project.cpp -o project`
- To Run (In Windows): `.\project.exe`
- To Run (Mac/Linux): `./project.out`

Secondly, the `generate_random.cpp` takes only the number of vertices as input and generate a chordal graph with randomly generated number of edges. The input should be provided through console. The output can be generated to a console or a text file. I generally prefer the output to be in a text file as the generated graph may be to large to copy and test upon. Please comment the `freopen ("input.txt","w",stdout)` line in the main function to generate output into the console if you need to. The number of graphs to be generated as output can be changed via the variable `t` in the main function. Please use the below steps to run the file:

- To Compile: `g++ generate_random.cpp -o generate_random`
- To Run (In Windows): `.\generate_random.exe`
- To Run (Mac/Linux): `./generate_random.out`

## Authors
* **Kalyan Chirla**

