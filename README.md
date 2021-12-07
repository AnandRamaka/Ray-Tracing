<h1 align="center">
  Ray Tracer in C++
</h1>


<h4 align="center">CS 128 Fall 2021 Final Project</h4>

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
bin/exec <filename> <height> <width> <scene_number>
```
where filename (string), height (pixels), width (pixels), and scene_number (int) are optional parameters. We have provided 4 scenes, with scene numbers 1-4. If you wish to build a different scene, modify the objects and materials in `src/main.cc.` 

We currently have implemented Spheres and Triangle objects. We also provide a Lambertian and Metal material for each object. To define both, see the example below.

```
Metal* center_material = new Metal(Vector3D(0.7, 0.6, 0.5)); //defines a material
Sphere* center_sphere = new Sphere(Vector3D(0, 1, 0), 1.0, center_material); //defines a sphere
hittable_list->Add(center_sphere); //make sure to add the sphere object to the list of hittable objects. Otherwise, it won't be rendered.
```

Here are some more scenes we created with our Ray Tracer:


![simple scene](/scenes/simple_scene.png)
![simple scene zoomed](/scenes/simple_scene_zoomed.png)
![cursed scene](/scenes/cursed.png)

## Test Suite

To run all of our tests:

```
make tests
```

To run an individual test:

```
make <test_name>
```

The individual test names are:

- metal_reflection
- random_tests
- sphere_tests
- vector_ray_tests

## Resources

The following resources served as a guide for the steps we took in this project. They also helped us with a lot of the math in our project.

- [Ray Tracing in One Weekend](https://raytracing.github.io)
- [Ray Tracing: Rendering a Triangle](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution)
