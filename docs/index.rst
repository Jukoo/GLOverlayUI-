.. GLOverlayUI documentation master file, created by
   sphinx-quickstart on Wed Aug  6 13:26:24 2025.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.


.. figure:: 
  ../assets/logo/gloverui.ico

GLOverlayUI documentation
=========================


.. toctree::
   :maxdepth: 4
   :caption: Contents:

   Project OverViews <pages/project-structure> 
   API Reference <api-references/index>
   Build Instruction <pages/build>
   ScreenShots       <pages/screenshots> 
   Changelogs        <pages/changes>
   License           <pages/license>
   Ressources        <pages/ressources> 


GLOverlayUI
===========

**GLOverlayUI** is a desktop application that demonstrates the integration of a real-time OpenGL rendering pipeline with a native wxWidgets GUI.

It features an interactive 2D scene rendered on a ``wxGLCanvas``, including a clickable OpenGL overlay and a dynamic control panel using native UI widgets.

Features
--------

- ✅ OpenGL-powered 2D scene rendered on ``wxGLCanvas``
- 🎯 Clickable UI overlay (PNG icon) rendered directly in OpenGL
- 📌 Toggleable right-side control panel with:
  -  + using Mouse motion to control object  rotation [Feature] 

  - ``wxSlider`` to control object rotation or scale
  - ``wxCheckBox`` to toggle visibility of scene objects

- 🧼 Clean separation between rendering engine and UI logic
- 🔁 Real-time interaction between OpenGL scene and native UI


Dependencies
------------

- wxWidgets (GUI framework)
- OpenGL (GL/GLU for 2D rendering)
- CMake ≥ 3.11

.. note::

   PNG loading is handled via ``wxImage`` – no external image library is required.


License
-------

This project is released under the GPLv3 License. See ``LICENSE`` for details.


Author
------

Created  by   **Umar Ba** 

Contact  : *jUmarB@protonmail.com*

Github link: *https://github.com/Jukoo*

