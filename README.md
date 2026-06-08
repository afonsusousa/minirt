*This project has been created as part of the 42 curriculum by wlucas-f, amagno-r.*

---

# miniRT

---

## Description

**miniRT** is a ray tracer written in C as part of the 42 school curriculum. It renders three-dimensional scenes described in a custom `.rt` scene file, producing computer-generated images displayed in a window via the MiniLibX graphics library.

Unlike rasterization — the dominant technique in real-time engines — ray tracing simulates the physical behaviour of light by casting rays from a virtual camera into the scene and computing intersections with geometric objects. The result is a much higher degree of visual realism at the cost of computational performance.

The project covers the fundamentals of 3D rendering:

- **Scene parsing** from a structured `.rt` text file
- **Geometric primitives**: sphere, plane, cylinder
- **Lighting model**: ambient lighting, diffuse (Lambertian) shading, hard shadows
- **Camera system** with configurable position, orientation, and field of view
- **Window management** via MiniLibX (resize, minimize, clean exit)

---

## Features

| Feature | Details |
|---|---|
| Geometric objects | Sphere (`sp`), Plane (`pl`), Cylinder (`cy`) |
| Lighting | Ambient + diffuse, hard shadows, spot light |
| Camera | Configurable viewpoint, orientation vector, horizontal FOV |
| Scene file | `.rt` format — human-readable, whitespace-tolerant |
| Window events | `ESC` key and red-cross close the program cleanly |
| Error handling | Exits with `Error\n` + descriptive message on bad input |
| Phong specular reflection | Full Phong illumination model (`phong.c`, `phong_components.c`) |

---

## Instructions

### Dependencies

- A C compiler (`cc`) with support for `-Wall -Wextra -Werror`
- MiniLibX (either system-installed or from sources)
- Math library (`-lm`)

### Run

```bash
./miniRT scenes/room.rt
./miniRT scenes/shadows.rt
```

The first (and only) argument must be a path to a `.rt` scene file.

### Controls

| Input | Action |
|---|---|
| `ESC` | Close window and exit |
| Red cross (×) | Close window and exit |

### Scene file format

Each element occupies one line. Fields are separated by one or more spaces. Elements starting with a capital letter (`A`, `C`, `L`) may only appear once.

```
# Ambient light       id  ratio  R,G,B
A                     0.2  255,255,255

# Camera              id  x,y,z        orientation  FOV
C                     -50,0,20  0,0,1  70

# Point light         id  x,y,z          brightness  R,G,B
L                     -40,50,0  0.6  255,255,255

# Plane               id  point          normal       R,G,B
pl                    0,0,0  0,1,0  255,0,225

# Sphere              id  center         diameter  R,G,B
sp                    0,0,20  20  255,0,0

# Cylinder            id  center          axis      diameter  height  R,G,B
cy                    50,0,20.6  0,0,1  14.2  21.42  10,0,255
```

A complete minimal example:

```
A  0.2  255,255,255
C  -50,0,20  0,0,1  70
L  -40,0,30  0.7  255,255,255
pl 0,0,0  0,1.0,0  255,0,225
sp 0,0,20  20  255,0,0
cy 50.0,0.0,20.6  0,0,1.0  14.2  21.42  10,0,255
```

---

## Project Structure

```
src
├── camera.c
├── cylinder.c
├── cylinder_helpers.c
├── hit.c
├── main.c
├── parsing
│   ├── parsing.c
│   ├── parsing_error.c
│   ├── parsing_formats2.c
│   ├── parsing_formats.c
│   ├── parsing_helpers.c
│   ├── parsing_init.c
│   ├── parsing_primitives.c
│   └── parsing_utils.c
├── phong.c
├── phong_components.c
├── pixel.c
├── plane.c
├── sphere.c
├── vec3_2.c
├── vec3_3.c
├── vec3_4.c
├── vec3.c
└── world.c
includes
├── camera.h
├── color.h
├── intersection.h
├── interval.h
├── mlx_mitm.h
├── obj.h
├── parsing.h
├── ray.h
├── render.h
├── vec3.h
└── world.h
```

---

## Resources

### Ray Tracing Theory

- [_The Ray Tracer Challenge_](http://raytracerchallenge.com/) — Jamis Buck — a test-driven approach to building a ray tracer from scratch
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) — Peter Shirley — the canonical starting point
- [_Scratchapixel_](https://www.scratchapixel.com/) — in-depth articles on ray-sphere, ray-plane, and ray-cylinder intersections, as well as the Phong shading model
- [Wikipedia — Ray tracing (graphics)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
- [Wikipedia — Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

### Mathematics

- [3Blue1Brown — Essence of Linear Algebra](https://www.youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab) — vectors, dot product, cross product

### 42-Specific

- [MiniLibX Linux sources](https://github.com/42Paris/minilibx-linux)

---

### AI Usage

- **Understanding mathematical derivations**: asking for step-by-step explanations of the quadratic equations used for ray-sphere and ray-cylinder intersections, then re-deriving them independently to ensure full comprehension.
- **Debugging assistance**: describing unexpected visual artefacts (e.g. shadow acne, incorrect normals on cylinder caps) and discussing possible causes — all suggested fixes were reviewed, tested, and understood before integration.
- **README drafting**: the initial structure of this document was generated with AI.
