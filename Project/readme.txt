# Parallel Sorting Animals by Taxonomic Levels
This github contains a main.cpp and animal.hpp file.

## Running the Code
g++ -pthread main.cpp -o output

## main.cpp
This file is in charge of running the sorting algorithms and printing the time it takes to run them. This is how you call this function:

g++ -pthread main.cpp -o output
./output 100000animals.txt

## animal.hpp
This file holds all of the information about the animals class, and its sorting functions.

## tree.cpp
This file is in charge of running the graphical representation aspect of the project. It creates a dot file and then a png. This is how to run it:

source myenv/bin/activate
make sure pip is updated...
sudo apt-get update && sudo apt-get install -y graphviz

g++ -std=c++11 -pthread tree.cpp -o output
./taxonomy_tree 10animals.txt
dot -Tpng taxonomy_tree.dot -o taxonomy_tree.pngpip install graphviz