# `SIMDVector` (concept)

## Implementations

* `sseb`, `ssef`, `sseu`, `sses`
* `avxb`, `avxf`, `avxu`, `avxs`
* `dumb`, `dumf`, `dumu`, `dums`
* `dual<T>`
* `vec4b`, `vec4f`, `vec4u`, `vec4s`
* `vec8b`, `vec8f`, `vec8u`, `vec8s`

## Requirements

### Member values

Type that satisfies `SIMDVector` must provide the following member values:

value   | description
--------|---------------------------------
`width` | number of scalars in the vector

### Member types

Type that satisfies `SIMDVector` must provide the following member types:

type           | description                                  | additional requirements
---------------|----------------------------------------------|-------------------------
`vec_b`        | related boolean SIMD vector                  | satisfies `SIMDVectorB`
`vec_f`        | related floating-point SIMD vector           | satisfies `SIMDVectorF`
`vec_u`        | related unsigned integral SIMD vector        | satisfies `SIMDVectorU`
`vec_s`        | related signed integral SIMD vector          | satisfies `SIMDVectorS`
`vector_t`     | low-level underlying vector type             |
`scalar_t`     | scalar type, as represented in memory        |
`log_scalar_t` | scalar type, as represented in program logic |
`storage_t`    | memory storage type                          |

### Construction and assignment

Type `T` that satisfies `SIMDVector` must be implicitly constructible and assignable from:
* `T`
* `vector_t`, `scalar_t`, `log_scalar_t`, `storage_t`
* result of `sd::zero()`, `sd::all_bits()`, `sd::sign_bit()`, `sd::abs_mask()`
* result of `sd::aligned()`, `sd::unaligned()`, `sd::interleaved()`

Additionally, `T` must be assignable to:
* `storage_t`
* result of `sd::aligned()`, `sd::unaligned()`, `sd::interleaved()`

### Operations

For a type `T` that satisfies `SIMDVector`, the following operations must be provided:

syntax                           | description
---------------------------------|-----------------------------------------------------------------------------
`x.aligned_load(ptr)`            | load vector from a memory location aligned to `alignof(T)` bytes
`x.aligned_store(ptr)`           | store vector to a memory location aligned to `alignof(T)` bytes
`x.unaligned_load(ptr)`          | load vector from an arbitrary memory location
`x.unaligned_store(ptr)`         | store vector to an arbitrary memory location
`x.interleaved_load(ptr, step)`  | load vector, `i`-th scalar is loaded from `ptr + i*step`
`x.interleaved_store(ptr, step)` | store vector, `i`-th scalar is stored `ptr + i*step`
`cond(b, x, y)`                  | based on values in `b`, select scalars from `x` (if true) or `y` (if false)
`reduce(x, f)`                   | apply reduction `f` to `x`, storing the result in each scalar

where:
* `x`, `y` are values of type `T`
* `ptr` is a value of type `scalar_t*`
* `step` is a value of type `int`
* `b` is a value of type `vec_b`
* `f` is a function template or function object with a templated `operator()` that has a signature equivalent to `S(const S&, const S&)`, where `S` is a template parameter.
