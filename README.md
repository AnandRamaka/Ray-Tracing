# Ray Tracer in C++
## CS 128 Fall 2021 Final Project

![best ray traced scene](/scenes/many_spheres_1920x1080.png)

Our project is a Raytracer written in modern C++. Our motivation for this project is to demonstrate our ability to integrate complex math while creating something that is visually appealing. We want to explore graphics, a topic that we are relatively unfamiliar with. Also, raytracers have numerous applications in game development, film, and other industries. This project would be a great intro into this industry.

## Building

To build the project:

```
make exec
```

## Usage

To run the project with the pre-existing scenes, you can run,

```
bin/exec <filename> <height> <width>
```
where filename (string), height (pixels), and width (pixels) are optional parameters.

If you wish to build a different scene, modify the objects and materials in `src/main.cc.`

## Test Suite

To run all of our tests:

```
make tests
```

To run an individual test:

```
make <test_name>
```
