# libcpab
CPAB Transformations [1]: finite-dimensional spaces of simple, fast, and 
highly-expressive diffeomorphisms derived from parametric, 
continuously-defined, velocity fields in **Tensorflow** and **Pytorch**.

The main idea behind this library is to offer a simple way to use diffiomorphic 
transformations and incorporate them into existing software. 
The diffiomorphic transformations are based on the work of 
[Freifeld et al.](https://www.cs.bgu.ac.il/~orenfr/papers/freifeld_etal_PAMI_2017).
The library supports diffiomorphic transformations in 1D (time series), 
2D (images) and 3D (volumetric images).

This code is based on the original implementation CPAB transformations by
Oren Freifeld (Github repo: [cpabDiffeo](https://github.com/freifeld/cpabDiffeo)).

## Author of this software

Nicki Skafte Detlefsen (email: nsde@dtu.dk)

Thanks to Tobias Slott Jensen and Asger Ougaard for suppling the base code 
for the 1D and 3D cases.

This software is released under the MIT License (included with the software). 
Note, however, that using this code (and/or the results of running it) to support
any form of publication (e.g., a book, a journal paper, a conference papar, a patent
application ect.) we request you to cite [1] and [2].

## Requirements

* Generic python packages: numpy, scipy, matplotlib
* Tensorflow or Pytorch

To use the GPU implementation (both backends), you need a nvidia GPU and CUDA + cuDNN installed.
I recommend going through these [installation instructions](https://www.tensorflow.org/install/)
for tensorflow. If you can get tensorflow working on your machine, pytorch should also work.

## Installation

Clone this reposatory to a directory of your choice
```
git clone https://github.com/SkafteNicki/libcpab
```
Add this directory to your PYTHONPATH
```
export PYTHONPATH=$PYTHONPATH:$YOUR_FOLDER_PATH/libcpab
```

## How to use
The interface is simple to use and only have a couple of different methods that should
get you started with diffiomorphic transformations. You have the choice to choose
between a tensorflow or pytorch backend:

```
    # Import library with tensorflow backend
    from libcpab.tensorflow import cpab
    
    # Import library with pytorch backend
    from libcpab.pytorch import cpab
```

Both class share the same the same interface

```
    # Import library
    from libcpab."framework" import cpab
 
    # Define a 2x2 transformation class
    T = cpab(tess_size=[2,2])
    
    # Important methods
    g = T.uniform_meshgrid(...)               # sample uniform grid of points in transformer domain
    theta = T.sample_transformation(...)      # sample random normal transformation vectors
    theta = T.identity(...)                   # get the identity transformation
    dim = T.get_theta_size()                  # get dimensionality of transformation parametrization
    params = T.get_params()                   # get different transformer parameters
    g_t = T.transform_grid(g, theta)          # transform a grid of points using theta
    data_t1 = T.interpolate(data, g_t)        # interpolate some data using the transformed grid
    data_t2 = T.transform_data(data, theta)   # combination of the two last methods 
```

There are small differences between using the two backends. Please see this
[file](libcpab/README.md) for the specific differences.

We supply 3 case scripts for each backend:
* *_demo1.py: simple use of the library to transform data
* *_demo2.py: image registration by incorporating the library in a tensorflow/pytorch optimization rutine
* *_demo3.py: time series alignment by sampling approch

For a specific use of the transformations in a greater context, 
see this [paper](http://www2.compute.dtu.dk/~sohau/papers/cvpr2018/detlefsen_cvpr_2018.pdf)[3] 
and this [github repo](https://github.com/SkafteNicki/ddtn).

## References
```
[1] @article{freifeld2017transformations,
  title={Transformations Based on Continuous Piecewise-Affine Velocity Fields},
  author={Freifeld, Oren and Hauberg, Soren and Batmanghelich, Kayhan and Fisher, John W},
  journal={IEEE Transactions on Pattern Analysis and Machine Intelligence},
  year={2017},
  publisher={IEEE}
}

[2] @misc{detlefsen2018,
  author = {Detlefsen, Nicki S.},
  title = {libcpab},
  year = {2018},
  publisher = {GitHub},
  journal = {GitHub repository},
  howpublished = {\url{https://github.com/SkafteNicki/libcpab}},
}

[3] @article{detlefsen2018transformations,
  title = {Deep Diffeomorphic Transformer Networks},
  author = {Nicki Skafte Detlefsen and Oren Freifeld and S{\o}ren Hauberg},
  journal = {Conference on Computer Vision and Pattern Recognition (CVPR)},
  year={2018},
  publisher={IEEE}
}

```

## Known bugs
* It seems that the identity transformation theta=0, is somewhat degenerate case
  that results in the gradient being `Nan`. This means that most optimization
  procedures will fail in both tensorflow and pytorch. Therefore, if you plan 
  to initialize the transformations to the identity and calculate gradients of 
  this, use T.identity(n_sample, epsilon) and set epsilon to a small number.
  I will look into this at some points in the future.

## Future

Note that the code is currently being updated to version 2.0 (see the branch).
The current state of the reposatory is branched off as version 1.4 and will see
no further development.

## Versions

* 23/08/2018, Version 1.0 - First working version of libcpab
* 28/09/2018, Version 1.1 - Pytorch backend support
* 22/10/2018, Version 1.2 - Various bugfixes
* 30/10/2018, Version 1.3 - Numpy backend support
* 15/11/2018, Version 1.4 - Various bugfixes
