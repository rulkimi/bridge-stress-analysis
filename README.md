## Background

The Three Hinged Arch Bridge Calculator is a C++ program designed for structural analysis of three-hinged arch bridges. This program provides a manual calculation approach to analyze such bridges, offering engineers and enthusiasts valuable insights into axial forces, shear forces, and bending moments at different sections along the span. By employing efficient data organization using vectors and control structures like loops and switches, this tool ensures accurate analysis for various bridge configurations.

## Features

- Input bridge span data and load data for analysis.
- Utilizes a three-hinged arch analysis method.
- Efficiently organizes data using vectors.
- Supports multiple spans and loads for comprehensive bridge analysis.

## Sample Inputs

To illustrate the program's functionality, consider the following example problem with sample inputs:

| Parameter                     | Value        |
| ----------------------------- | ------------ |
| Length of span (m)            | 40           |
| Number of spans               | 1            |
| Height of the arch (m)        | 10           |
| Number of sections            | 4            |
| Number of loads               | 2            |

### Load No. 1

| Parameter                     | Value        |
| ----------------------------- | ------------ |
| Type                          | Point load   |
| Magnitude (kN)                | 150          |
| Position from left support (m)| 15           |

### Load No. 2

| Parameter                     | Value        |
| ----------------------------- | ------------ |
| Type                          | Distributed load |
| Magnitude (kN/m)              | 120          |
| Position from left (m)        | 0            |
| Position to right (m)         | 40           |


## Sample Output

You can find the sample output in the [code section](https://github.com/rulkimi/bridge-stress-analysis/raw/main/sample-output.jpg) of this repository. These output files will showcase the calculated axial forces, shear forces, and bending moments for the provided sample inputs.

Contributions and improvements are welcome.

Happy bridge analysis!
