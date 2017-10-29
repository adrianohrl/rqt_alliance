rqt_alliance
=========

This is a C++ Plugin for visualization of the motivation of each robot's behaviour sets in a running ALLIANCE architecture.


## Overview

**Author(s):** Adriano Henrique Rossette Leite

**Maintainer:** UNIFEI Exppertinos <expertinos DOT unifei AT gmail DOT com>

**License:** GNU Lesser General Public License (LGPL)

**Operating system(s):** Debian-based Linux

## Content

This is a C++ Plugin for visualization of the motivation of each robot's behaviour sets in a running ALLIANCE architecture.

## Installation
### Dependencies

- [rqt](http://wiki.ros.org/rqt)

    ```shell
    sudo apt-get install ros-indigo-rqt
    ```

    ```shell
    sudo apt-get install libqwt-dev
    ```

## Usage

To launch the standalone rqt plugin, run

```shell
rosrun rqt_alliance rqt_alliance
```

To launch the rqt GUI without a perspective, run

```shell
rqt --force-discover
```

This will discover all plugins, which can then be loaded manually.

To delete the default configuration files (in case of problems):

```shell
rqt --clear-config
```
