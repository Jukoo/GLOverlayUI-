******************************
Build Instructions (GNU/Linux)
******************************

.. toctree:: 
   :maxdepth: 4
   :caption: Contents:


Build Instructions 
------------------

**Prerequisites**

Install required system packages:

.. code-block:: bash

   >  cmake build-essential libwxgtk3.0-gtk3-dev libgl1-mesa-dev libglu1-mesa-dev

**Build the Project**

From the root of the repository:

.. code-block:: bash

   cmake -B build
   cmake --build build

The final executable will be located in the ``bin/`` directory.

Run the Application
-------------------

.. code-block:: bash

   ./bin/GLOverlayUI 



Build Instructions
==================

This project requires a few dependencies to be installed beforehand.

Dependencies or Prerequisites
-----------------------------

On Linux, ensure the following packages are available:

.. code-block:: bash

   sudo <your package-manager-install> cmake build-essential libwxgtk3.0-gtk3-dev \
        libgl1-mesa-dev libglu1-mesa-dev

.. warning:: 

   To find out the names of the packages, please search using your package manager. 
   The names may vary depending on the Linux distribution.


**Optional (for documentation build):**

- Python 3 (recommended via `pyenv` or `venv`)
- Doxygen

A ``requirements.txt`` file is already provided in the ``docs/`` folder.

----------------------------

Basic Build
-----------

The project can be built with the classic CMake commands:

.. code-block:: bash

   cmake -B build
   cmake --build build

After compilation, the executable will be generated in the ``./bin`` directory
at the root of the project.

To run the application:

.. code-block:: bash

   ./bin/GLOverlayUI

----------------------------

Extended Build: Documentation
-----------------------------

The build system has been extended to also generate documentation from source
code. For this, you need both **Python** and **Doxygen** installed.

It is recommended to create a Python virtual environment:

.. code-block:: bash

   python3 -m venv dist
   source dist/bin/activate
   pip install -r docs/requirements.txt

Then enable documentation build when running CMake:

.. code-block:: bash

   cmake -B build -DBUILD_DOC=ON
   cmake --build build

----------------------------

Viewing Documentation
---------------------

After a successful build, documentation can be viewed in two forms:

- **Sphinx** HTML docs: ``docs/_build/html``
- **Doxygen** HTML docs: ``docs/_doxy/html``

To preview locally, you can serve them with Python:

.. code-block:: bash

   # Sphinx
   python3 -m http.server -d ./docs/_build/html

   # Doxygen
   python3 -m http.server -d ./docs/_doxy/html

Public Documentation
--------------------

The documentation is also published online:

- https://gloverlayui.readthedocs.io/en/latest

----------------------------

Issues & Bug Reports
--------------------

If you encounter problems building the project or discover bugs,
please open an issue on the `GitHub repository <https://github.com/Jukoo/GLOverlayUI->`_.

Happy hacking Folks! 🚀
