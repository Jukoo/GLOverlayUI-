*************************
GLOverlayUI API DOCSTRING
*************************

.. toctree:: 
   :hidden: 

   Mainframe - The wxWrapper <mainframe>
   Canvasdriver - The wxGLCanvas <canvasdriver>
   Renderer - The OpenGL Renderer Logic <renderer>  

API Documentation
=================

This section provides the full reference for the **GLOverlayUI** source code.
It has been automatically generated from the inline Doxygen-style docstrings.

Introduction
------------

The goal of this API documentation is to make the internal structure of the project transparent and reusable.
The codebase is divided into **decoupled modules** to separate concerns between rendering and user interface:

- **Renderer**
  A lightweight OpenGL-based rendering engine.
  It is **UI-agnostic** and can be reused independently of wxWidgets.
  Provides functions to draw basic 2D primitives (rectangles, triangles, icons) and to apply transformations such as scaling and rotation.

- **CanvasDriver**
  A wrapper around ``wxGLCanvas`` that integrates the rendering logic into the wxWidgets application.
  It manages the OpenGL context, forwards user events (mouse, resize, etc.), and delegates the drawing to ``Renderer2D``.

- **MainFrame**
  The main wxWidgets window that manages the layout of the canvas and the side panel.
  Provides the higher-level UI logic, including the slider, checkbox, and toggle panel button.

Philosophy
----------

- **Separation of Concerns**: OpenGL rendering logic is decoupled from wxWidgets, enabling reuse in other frameworks or contexts.
- **Simplicity**: Minimal dependencies, easy build process, and small learning curve for developers exploring wxWidgets + OpenGL.
- **Extensibility**: New shapes, transformations, or UI widgets can be added with minimal changes to the existing code.

How to Use this Documentation
-----------------------------

- Navigate through the classes  in the sidebar.
- Each class documents:
  - Public methods and attributes
  - Parameters and return values (when relevant)
- Use the **search bar** to quickly find symbols in the codebase.

.. note::
   For an overview of the project structure, refer to `Project Structure <pages/project-structure>` section.


